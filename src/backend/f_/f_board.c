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
#include "f_game.h"
#include "f_fichas.h"
#include "headers/f_board.h"

/* ================================================================================
	TIPOS DE DATOS DEFINIDOS
   ================================================================================*/

struct pos
{
	unsigned short int x;
	unsigned short int y;
};

typedef struct pos pos_t;

/* ================================================================================
	VARIABLES GLOBALES DEL ARCHIVO
   ================================================================================*/

static GtkWidget *g_stack[F_BOARD_STACK_MAX_TOP];
static unsigned short int g_stack_top = 0;

// posición relativa de cada casilla
// del tablero del juego.
static const pos_t g_board_widget_pos[24] =
{
	{ 0, 0 },
	{ 0, 1 },
	{ 0, 2 },
	{ 0, 1 },
	{ 0, 2 },
	{ 0, 3 },
	{ 0, 2 },
	{ 0, 3 },
	{ 0, 4 },
	{ 1, 0 },
	{ 1, 1 },
	{ 1, 2 },
	{ 1, 4 },
	{ 1, 3 },
	{ 1, 2 },
	{ 2, 2 },
	{ 2, 3 },
	{ 2, 4 },
	{ 2, 1 },
	{ 2, 2 },
	{ 2, 3 },
	{ 2, 0 },
	{ 2, 1 },
	{ 2, 2 }
};

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	: 	f_board_stack_push(GtkWidget *)
// @UTILIDAD	: 	almacenar en el stack la dirección
//					del widget casilla seleccionado por
//					el jugador.	
// @PARAMETROS	:	widget > casilla del tablero del juego.
// @RETORNO		:	ninguno.
void f_board_stack_push(GtkWidget *widget)
{
	GtkWidget *temp;

	if (g_stack_top >= F_BOARD_STACK_MAX_TOP)
	{
		// Si la pila esta llena, el último
		// elemento pasa a ser el primero.
		temp = f_board_stack_pop();
		g_stack[0] = temp;
	}

	g_stack[g_stack_top++] = widget;
}

// @SUB-RUTINA 	:	f_board_stack_pop()
// @UTILIDAD	:	obtener la dirección del widget casilla.
// @PARAMETROS	:	ninguno
// @RETORNO		:	dirección de la casilla.
GtkWidget *f_board_stack_pop(void)
{
	if (g_stack_top <= 0)
		return NULL;

	return g_stack[--g_stack_top];
}

// @SUB-RUTINA 	:	f_board_stack_top()
// @UTILIDAD	:	obtener el tope del stack.
// @PARAMETROS	: 	ninguno.
// @RETORNO		:	tope.
unsigned short int f_board_stack_top(void)
{
	return g_stack_top;
}

// @SUB-RUTINA 	:	f_board_check_move(unsigned short int , unsigned short int )
// @UTILIDAD	:	verificar a partir de la posición base y la nueva posición
//					de una ficha a ser movida, si el movimiento es válido.
// @PARAMETROS	:	base_id		> posición actual de la ficha.
//					target_id	> nueva posición de la ficha.
//					player 		> jugador a verificar.
// @RETORNO		:	TRUE		> la nueva posición es válida.
//					FALSE		> la nueva posición no es válida.
gboolean f_board_check_move(unsigned short int player, unsigned short int base_id, unsigned short int target_id)
{
	pos_t base;
	pos_t target;

	// si el jugador intenta mover una ficha del tablero
	// sin haber colocado primero todas sus fichas, la
	// jugada actual no es válida.
	if (GAME_VTABLE_NOT_EMPTY)
		return FALSE;

	// ¿el jugador tiene 3 fichas en el tablero?
	if (FICHAS_MOV_NO_ADYACENTE(player))
		return TRUE;

	base = g_board_widget_pos[base_id];
	target = g_board_widget_pos[target_id];

	// movimientos consecutivos entre cuadros (externos e internos)
	// diagonales, arriba, abajo, izquierda y derecha.
	
	if ((base.x == target.x) && ((base.y + 1) == target.y))
		return TRUE;

	if ((base.x == target.x) && (base.y - 1 == target.y))
		return TRUE;

	// movimientos consecutivos entre cuadros internos
	// izquierda y derecha.

	if ((base.x + 1 == target.x) && (base.y == target.y))
		return TRUE;

	if ((base.x - 1 == target.x) && (base.y == target.y))
		return TRUE;

	return FALSE;
}