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
#include "f_board.h"
#include "f_game.h"
#include "f_mill.h"
#include "headers/callback_board.h"

// @SUB-RUTINA	:	callback_board(GtkWidget *, GdkEvent *, gpointer )
// @UTILIDAD	:	captar y manipular las fichas que son colocadas
//					en el tablero 1 mediante la señal press button.
// @PARAMETROS	:	target 			>	widget event box asociado al tablero (la casilla)
//					target_event 	>	evento por el cual es llamado
//					target_data		>	apuntador a un tipo de dato externo asociado al widget
// @RETORNO		:	TRUE	> las operaciones a realizar con la casilla finalizaron.
//					FALSE	> las operaciones a realizar con la casilla no finalizaron.
gboolean callback_board(GtkWidget *target, GdkEvent *target_event, gpointer target_data)
{
	// prototipos de sub-rutinas externas al archivo
	gboolean event_board_double_click(GtkWidget *, guint8 );
	gboolean event_board_single_click(guint8 );

	// ¿en la jugada actual hay algún mill activo?
	if (f_mill_status())
	{
		event_board_single_click(GPOINTER_TO_UINT(target_data));
		return TRUE;
	}

	// push de casillas
	f_board_stack_push(target);

	// ¿el jugador actual selecciono dos fichas?
	if (f_board_stack_top() == F_BOARD_STACK_MAX_TOP)
		event_board_double_click(target, GPOINTER_TO_UINT(target_data));

	return TRUE;
}