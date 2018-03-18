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
#include "w_vtable_white.h"
#include "w_vtable_black.h"
#include "w_macros.h"
#include "f_board.h"
#include "f_game.h"
#include "f_fichas.h"
#include "f_mill.h"

/* ================================================================================
	SUB-RUTINAS	LOCALES
   ================================================================================*/

static void tablero_agregar_modificar_ficha_jugador(guint8 , guint8 , guint8 , guint8 , GtkWidget *);

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	:	event_board_double_click(GtkWidget *, guint8 )
// @UTILIDAD	:	realizar cambios en el juego cuando el jugador
//					selecciona dos fichas del tablero.
// @PARAMETROS	:	target 		>	widget event box asociado al tablero (la casilla).
//					target_id 	>	id de la última casilla seleccionada por el jugador.
// @RETORNO		:	TRUE	> las operaciones a realizar con la casilla finalizaron
//					FALSE	> las operaciones a realizar con la casilla no finalizaron
gboolean event_board_double_click(GtkWidget *target, guint8 target_id)
{
	GtkWidget *widget;
	GtkWidget *widget_child;
	GtkWidget *target_child;

	unsigned short int i;
	unsigned short int player;
	unsigned short int widget_id;
	unsigned short int widget_src;
	unsigned short int widget_owner;

	// vector de punteros a funciones,
	// contiene la función para eliminar una
	// ficha dependiendo del tablero de origen.
	void (* const w_remove[3])(unsigned short int) = 
	{
		&w_vtable_remove_white_widget,
		&w_board_remove_widget,
		&w_vtable_remove_black_widget
	};

	// vector de punteros a funciones,
	// contiene la función para obtener el widget
	// de la casilla padre, esta retorna 
	// la direccion del hijo (la ficha del juego).
	GtkWidget * (* const w_get_child[3])(unsigned short int) = 
	{
		&w_vtable_get_white_widget,
		&w_board_get_widget,
		&w_vtable_get_black_widget
	};

	target_child = w_board_get_widget(target_id);

	// la casilla en donde
	// se va a mover la ficha seleccionada
	// ya contiene una ficha.
	if (target_child)
		return FALSE;

	// se obtiene el id del jugador
	// de acuerdo al turno.
	player = f_game_get_turno();

	// pop F_BOARD_STACK_MAX_TOP veces
	// se analiza las fichas seleccionadas.
	for (i = 0; i < F_BOARD_STACK_MAX_TOP; i++)
	{
		widget = f_board_stack_pop();

		// el jugador selecciono
		// la misma casilla dos veces o 
		// la casilla seleccionada coincide con el target.
		if (target == widget)
			continue;

		widget_id  = W_CASILLA_GET_ID(widget);
		widget_src = W_CASILLA_GET_SRC(widget);
		widget_child = (*w_get_child[widget_src])(widget_id);

		// la casilla seleccionada (origen) no tiene fichas
		// correspondiente al id del tablero actual.
		if (!widget_child)
			continue;

		widget_owner = W_FICHA_GET_OWNER(widget_child);

		// la ficha seleccionada no es del jugador actual.
		if (widget_owner != player)
			continue;

		// ficha seleccionada desde el tablero 1
		if (widget_src == UI_BOARD_SRC)
			// ¿ el destino de la ficha a mover es
			// de posición consecutiva con la posición
			// de la ficha seleccionada ?
			if (!f_board_check_move(player, widget_id, target_id))
				continue;

		// se remueve la ficha del tablero de origen,
		// la misma pasa a colocarse en el tablero central
		// cuya posicion es la casilla target.
		(*w_remove[widget_src])(widget_id);
		tablero_agregar_modificar_ficha_jugador(player, target_id, widget_id, widget_src, widget_child);

		// como la jugada es valida, se verifica si
		// el jugador realizo algun mill en esta ronda,
		// a partir de la ultima ficha jugada (target).
		if (f_mill(target_id, player))
		{
			f_mill_toggle_status(TRUE);
			return TRUE;
		}

		f_game_terminar_turno();
	}

	return TRUE;
}

static void tablero_agregar_modificar_ficha_jugador(guint8 player, guint8 casilla_new_id, guint8 casilla_id, guint8 casilla_src, GtkWidget *ficha)
{
	w_board_set_widget(casilla_new_id, ficha);

	if (casilla_src == UI_BOARD_SRC)
		f_fichas_queue_remove_item(player, casilla_id);

	f_fichas_enqueue(casilla_new_id, player);
}