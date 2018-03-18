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
#include "w_end_game.h"
#include "w_status_bar.h"
#include "f_rules.h"
#include "ia.h"
#include "headers/f_game.h"

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static guint16 g_turno = 0;
static guint16 g_njugadas = 0;
static gboolean g_config = FALSE;

/* ================================================================================
	DEFINICIÓN DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	:	f_game_get_turno()
// @UTILIDAD	:	obtiene el turno actual.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	el turno.
guint8 f_game_get_turno(void)
{
	return g_turno;
}

// @SUB-RUTINA	:	f_game_get_adv()
// @UTILIDAD	:	obtiene el adversario a partir del turno actual.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	el adversario.
guint8 f_game_get_adv(void)
{
	if (g_turno == 0)
		return 1;

	return 0;
}

// @SUB-RUTINA	:	f_game_set_turno()
// @UTILIDAD	:	asigna el turno actual.
// @PARAMETROS	:	i > el turno.
// @RETORNO		:	ninguno.
void f_game_set_turno(guint16 i)
{
	g_turno = i;
}

// @SUB-RUTINA	:	f_game_next_turno()
// @UTILIDAD	:	asigna el siguiente turno.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_game_next_turno(void)
{
	/*
		inicia la partida aquel que no haya comenzado
		colocando primero sus fichas.
	*/
	if (g_njugadas == (F_FICHAS_N * 2))
	// como los turno se alternan, cuando sea el
	// turno del adversario y si ya no quedan fichas
	// para mover de los tableros verticales, entonces
	// se bloquea el cambio de turno.
		return;

	if (++g_turno >= 2)
		g_turno = 0; 
}

// @SUB-RUTINA	:	f_game_count_jugadas()
// @UTILIDAD	:	cuenta la cantidad de jugadas en el tablero.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_game_count_jugadas(void)
{
	g_njugadas++;
}

// @SUB-RUTINA	:	f_game_get_jugadas()
// @UTILIDAD	:	obtiene el número de jugadas en el tablero.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
guint16 f_game_get_jugadas(void)
{
	return g_njugadas;
}

// @SUB-RUTINA	:	f_game_terminar_turno()
// @UTILIDAD	:	llamar a subrutinas que son necesarias
//					para finalizar correctamente el turno
//					de un jugador.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_game_terminar_turno(void)
{
	// se actualiza el número de jugadadas,
	// turno siguiente y barra de estado.
	// se verifican las reglas del juego.
	f_game_count_jugadas();
	f_game_next_turno();
	w_statusbar_change_value();
	f_rules();

	if (ia_get_turno() == g_turno)
		ia();
}

// @SUB-RUTINA 	:	f_game_get_config()
// @UTILIDAD	:	verifica si existe una
//					configuración de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	TRUE	> no existe una configuracíon.
//					FALSE 	> existe una configuración.
gboolean f_game_get_config(void)
{
	return g_config;
}

// @SUB-RUTINA 	:	f_game_set_config()
// @UTILIDAD	:	establer o no, que existe una configuración
//					de juego.
// @PARAMETROS	:	status > estado de la configuración del juego.
// @RETORNO		:	ninguno.
void f_game_set_config(gboolean status)
{
	g_config = status;
}

// @SUB-RUTINA 	:	f_game_over(guint8 )
// @UTILIDAD	:	establecer el fin de juego.
// @PARAMETROS	:	r 		> 	razón de fin de juego.
//					winner  >	el jugador ganador.
//					loser	> 	el jugador perdedor.
// @RETORNO		:	ninguno.
void f_game_over(guint8 winner, guint8 loser, guint8 r)
{
	w_end_game_signal_connect();
	w_board_signal_disconnect();
	w_statusbar_update_endgame(winner, r);
	w_end_game_show(winner, loser, r);
}