/*
The MIT License (MIT)

Copyright (c) 2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Author: Rodrigo <Ravf> Villalba
*/

#include <gtk/gtk.h>
#include "w_board.h"
#include "f_fichas.h"
#include "f_game.h"
#include "f_mill.h"
#include "headers/f_rules.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define BOARD_GET_FICHA(ID, COL, POS)	w_board_get_widget(f_mill_get_mchk_value(ID, COL, POS))
#define ADV(PLAYER)						((PLAYER == 0) ? 1 : 0)

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static guint8 g_movidas_tres_fichas_count[2] = { 0, 0 };

/* ================================================================================
	PROTOTIPOS DE SUB-RUTINAS LOCALES
   ================================================================================*/

static gboolean f1(guint8 player);
static gboolean f2(guint8 player);
static gboolean f3(guint8 player);

/* ================================================================================
	DEFINICIÓN DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	:	f_gamerules_check()
// @UTILIDAD	:	verifica las reglas de fin del juego.
// @PARAMETROS	:	ninguno
// @RETORNO		:	ninguno.
void f_rules(void)
{
	guint8 i;
	guint8 player;

	if (GAME_VTABLE_NOT_EMPTY)
		return;

	gboolean (* const rules[3])(guint8 ) =
	{
		&f2,
		&f3,
		&f1
	};

	for (i = 0; i < 3; i++)
	{
		for (player = 0; player < 2; player++)
		{
			if ((*rules[i])(player))
			{
				f_game_over(ADV(player), player, i);
				return;
			}
		}
	}
}

/*
	Regla 1:
	cuando un jugador no puede realizar movida
	alguna con ninguna de sus fichas en el tablero, 
	pierde el juego.
*/

// @SUB-RUTINA	:	f1(guint8 )
// @UTILIDAD	:	verificar la regla 1.
// @PARAMETROS	:	player 	>	identificador del jugador.
// @RETORNO		:	TRUE	>	se cumple la regla 1.
//					FALSE	> 	no se cumple la regla 1.
static gboolean f1(guint8 player)
{
	guint8 i;
	guint8 j;
	guint8 n;
	guint8 id;
	guint8 col;
	guint8 value;
	guint8 ficha_bloqueada;

	// el jugador tiene 3 fichas en el tablero
	// entonces sus fichas pueden moverse en
	// cualquier dirección disponible.
	if (FICHAS_MOV_NO_ADYACENTE(player))
		return FALSE;

	// se verifica ficha por ficha si esta
	// tiene movimiento válido alguno
	// en las direcciones: arriba, abajo
	// izquierda, derecha, diagonal: 1, 2, 3 y 4.

	// para que sea un movimiento válido la
	// casilla tiene que estar vacia.

	for (n = f_get_player_fichas(player), i = 0; i < n; i++)
	{
		id = f_fichas_dequeue(player);
		f_fichas_enqueue(id, player);

		for (col = 0; f_mill_valid_mchk_col(id, col); col++)
		{
			ficha_bloqueada = FALSE;

			for (j = 0; j < 3; j++)
			{
				value = f_mill_get_mchk_value(id, col, j);

				if (id != value)
					continue;

				// la ficha esta en el medio
				if ( (j - 1) >= 0 && (j + 1) < 3)
				{
					// si no puede realizar ningun movimiento en los extremos
					if (BOARD_GET_FICHA(id, col, j - 1) && BOARD_GET_FICHA(id, col, j + 1))
					{
						ficha_bloqueada = TRUE;
						break;
					}

					// la ficha se puede mover.
					break;
				}

				// una ficha antes
				if ( (j - 1) >= 0)
				{
					// si no se puede mover hacia atras.
					if (BOARD_GET_FICHA(id, col, j - 1))
					{
						ficha_bloqueada = TRUE;
						break;
					}

					// la ficha se puede mover.
					break;
				}

				// una ficha despues
				if ( (j + 1) < 3)
				{
					// si no se puede mover hacia adelante.
					if (BOARD_GET_FICHA(id, col, j + 1))
					{
						ficha_bloqueada = TRUE;
						break;
					}

					// la ficha se puede mover.
					break;
				}			
			}

			// si alguna ficha no esta bloqueda entonces
			// el jugador tiene al menos un movimiento
			// válido.
			if (!ficha_bloqueada)
				return FALSE;
		}
	}

	// el jugador no tiene
	// movimientos válidos.
	return TRUE;
}

/*
	Regla 2:
	el jugador que se queda con 2 fichas en el
	tablero, pierde el juego.
*/

// @SUB-RUTINA	:	f2(guint8 )
// @UTILIDAD	:	verificar la regla 2.
// @PARAMETROS	:	player 	>	identificador del jugador.
// @RETORNO		:	TRUE	>	se cumple la regla 2.
//					FALSE	> 	no se cumple la regla 2.
static gboolean f2(guint8 player)
{
	if (f_get_player_fichas(player) <= 2)
		return TRUE;

	return FALSE;
}

/*
	Regla 3:
	si ambos jugadores se han quedado con 3 fichas
	cada uno en el tablero y después de 10 movidas
	de esta configuración nadie ha obtenido la
	victoria, se declara empate.
*/

// @SUB-RUTINA	:	f3(guint8 )
// @UTILIDAD	:	verificar la regla 3.
// @PARAMETROS	:	player 	>	identificador del jugador.
// @RETORNO		:	TRUE	>	se cumple la regla 3.
//					FALSE	> 	no se cumple la regla 3.
static gboolean f3(guint8 player)
{
	if (!FICHAS_MOV_NO_ADYACENTE(0) && !FICHAS_MOV_NO_ADYACENTE(1))
		return FALSE;

	if (g_movidas_tres_fichas_count[player] >= 10)
		return TRUE;

	if (FICHAS_MOV_NO_ADYACENTE(player))
	{
		g_movidas_tres_fichas_count[player]++;
		return FALSE;
	}

	g_movidas_tres_fichas_count[player] = 0;
	return FALSE;
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef BOARD_GET_FICHA
#undef ADV