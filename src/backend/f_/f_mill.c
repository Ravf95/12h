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
#include "w_macros.h"
#include "w_board.h"
#include "f_fichas.h"
#include "headers/f_mill.h"

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

// posiciones de los contenedores horizontales
static const char H1[3]	 	= { 0, 9, 21 };
static const char H2[3]	 	= { 3, 10, 18 };
static const char H3[3]	 	= { 6, 11, 15 };
static const char H4_1[3] 	= { 1, 4, 7 };
static const char H4_2[3] 	= { 16, 19, 22 };
static const char H5[3] 	= { 8, 12, 17 };
static const char H6[3] 	= { 5, 13, 20 };
static const char H7[3] 	= { 2, 14, 23 };

// posiciones de los contenedores verticales
static const char V1[3] 	= { 0, 1, 2 };
static const char V2[3] 	= { 3, 4, 5 };
static const char V3[3] 	= { 6, 7, 8 };
static const char V4_1[3] 	= { 9, 10, 11 };
static const char V4_2[3] 	= { 12, 13, 14 };
static const char V5[3] 	= { 15, 16, 17 };
static const char V6[3] 	= { 18, 19, 20 };
static const char V7[3] 	= { 21, 22, 23 };

// posiciones de los contenedores diagonales
static const char D1[3] 	= { 0, 3, 6 };
static const char D2[3] 	= { 2, 5, 8 };
static const char D3[3] 	= { 15, 18, 21 };
static const char D4[3] 	= { 17, 20, 23 };

// matriz de apuntadores a vectores
static const char * const MCHK[24][4] = 
{
	{ V1, 	H1, 	D1,		NULL },
	{ V1, 	H4_1,	NULL },
	{ V1, 	H7, 	D2,		NULL },
	{ V2, 	H2, 	D1, 	NULL },
	{ V2, 	H4_1,	NULL },
	{ V2, 	H6, 	D2, 	NULL },
	{ V3, 	H3, 	D1, 	NULL },
	{ V3, 	H4_1,	NULL },
	{ V3, 	H5,		D2,		NULL },
	{ V4_1, H1, 	NULL },
	{ V4_1, H2, 	NULL },
	{ V4_1, H3, 	NULL },
	{ V4_2, H5, 	NULL },
	{ V4_2, H6, 	NULL },
	{ V4_2, H7, 	NULL },
	{ V5, 	H3, 	D3, 	NULL },
	{ V5, 	H4_2, 	NULL },
	{ V5, 	H5, 	D4, 	NULL },
	{ V6, 	H2, 	D3, 	NULL },
	{ V6, 	H4_2, 	NULL },
	{ V6, 	H6, 	D4, 	NULL },
	{ V7, 	H1, 	D3, 	NULL },
	{ V7, 	H4_2, 	NULL },
	{ V7, 	H7, 	D4, 	NULL }
};

static gboolean g_mill = FALSE;

/* ================================================================================
	DEFINICIÓN DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	:	f_mill_valid_mchk_col(guint , guint8 )
// @UTILIDAD	:	verifica si la columna de la matriz de vectores
//					MCHK es válida.
// @PARAMETROS	:	id 	> 	identificador de casilla.
//					c 	> 	columna de la matriz de vectores.
// @RETORNO		:	TRUE	> 	es válida
//					FALSE	> 	no es válida. 
gboolean f_mill_valid_mchk_col(guint8 id, guint8 col)
{
	if (id >= 24 || col >= 3)
		return FALSE;
	
	if (!MCHK[id][col])
		return FALSE;

	return TRUE;
}

// @SUB-RUTINA	:	f_mill_get_mchk_value(guint8 , guint8 , guint8 )
// @UTILIDAD	:	obtiene el elemento del vector apuntado por 
//					la matriz de vectores MCHK.
// @PARAMETROS	:	id 		>	identificador de casilla.
//					col 	>	vector.
//					i 		>	elemento del vector.
// @RETORNO		:	elemento del vector.
char f_mill_get_mchk_value(guint8 id, guint8 col, guint8 i)
{
	return MCHK[id][col][i];
}

// @SUB-RUTINA	:	f_mill(guint8 , guint8 )
// @UTILIDAD	:	verifica si una ficha determinada esta
//					formando mill en el tablero del juego.
// @PARAMETROS	:	id 			>	identificador de casilla.
//					id_owner	>	jugador.
// @RETORNO		:	TRUE	>	forma mill.
//					FALSE	>	no forma mill.
gboolean f_mill(guint8 id, guint8 id_owner)
{
	guint8 i;
	guint8 k;
	guint8 count;
	guint8 owner;
	guint8 widget_id;
	const GtkWidget *child;

	// se accede a la dirección alamacenada en
	// la matriz de vectores.
	for (i = 0, count = 1; f_mill_valid_mchk_col(id, i); i++, count = 1)
	{
		// se accede al elemente de la
		// dirección actual de la matriz de vectores.
		for (k = 0; k < 3; k++)
		{
			widget_id = f_mill_get_mchk_value(id, i, k);

			// el contador de mill por defecto es 1
			// entonces si el id de la casilla
			// a verificar coincide con el id de mill
			// ignoramos esté, entonces solo necesita
			// 2 fichas consecutivas con esta para hacer
			// mill.
			if (id == widget_id)
				continue;

			child = w_board_get_widget(widget_id);

			if (!child)
				break;

			owner = W_FICHA_GET_OWNER(child);

			if (owner != id_owner)
				break;

			count++;
		}

		// ¿hay tres fichas alineadas?
		if (count == 3)
			// entonces forman mill.
			return TRUE;
	}

	return FALSE;
}

// @SUB-RUTINA	:	f_mill_check_all(guint )
// @UTILIDAD	:	verifica si todas las fichas colocadas 
//					en el tablero de un jugador determinado 
//					estan formando mill.
// @PARAMETROS	:	player 	> 	identificador del jugador.
// @RETORNO		:	TRUE	>	todas sus fichas forman mill.
//					FALSE	>	no todas sus fichas forman mill.
gboolean f_mill_check_all(guint player)
{
	gint8 i;
	gint8 id_ficha;
	gint8 n_fichas;
	gint8 mill_count;

	mill_count = 0;
	n_fichas = f_get_player_fichas(player);

	for (i = 0; i < n_fichas; i++)
	{
		id_ficha = f_fichas_dequeue(player);
		f_fichas_enqueue(id_ficha, player);

		if (!f_mill(id_ficha, player))
			return FALSE;

		mill_count++;
	}

	// ¿la cantidad de fichas que forman mill coinciden
	// con el total de fichas colocadas en el tablero por el
	// jugador?
	if (n_fichas == mill_count)
		// entonces todas forman mill.
		return TRUE;

	return FALSE;
}

// @SUB-RUTINA	:	f_mill_toggle_status(gboolean )
// @UTILIDAD	:	manejar el evento mill del juego.
// @PARAMETROS	:	toggle 	>	activado/desactivado.
// @RETORNO		:	ninguno.
void f_mill_toggle_status(gboolean toggle)
{
	g_mill = toggle;
}

// @SUB-RUTINA	:	f_mill_status()
// @UTILIDAD	:	verificar si hay algun mill activo.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	TRUE	>	hay un mill activo.
//					FALSE	>	no hay un mill activo.
gboolean f_mill_status(void)
{
	return g_mill;
}