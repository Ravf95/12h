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
#include "w_new_game.h"
#include "w_status_bar.h"
#include "w_vtable_white.h"
#include "w_vtable_black.h"
#include "f_game.h"
#include "ia.h"
#include "headers/callback_new_game.h"

#define ADV(X) 					((X == 0) ? 1 : 0)

// @SUB-RUTINA	:	callback_new_game_ok(GtkWidget *, GdkEvent *, gpointer )
// @UTILIDAD	:	establecer el inicio del juego.
// @PARAMETROS	:	widget 		>	elemento de la gui asociado.
//					event 		>	evento por el cual es llamado.
//					data		>	apuntador a un tipo de dato externo asociado al widget.
// @RETORNO		:	TRUE		> 	no hay operaciones pendientes.
gboolean callback_new_game_ok(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	guint8 mode;
	mode = w_new_game_get_mode();
	ia_set_turno(ADV(mode));
	f_game_set_turno(mode);

	w_status_bar_show();
	w_table_white_show();
	w_vtable_black_show();
	w_statusbar_change_value();
	
	w_board_signal_connect();
	w_vtable_white_widget_signal_connect();
	w_vtable_black_widget_signal_connect();

	f_game_set_config(TRUE);
	w_new_game_quick_exit();

	if (mode == 1)
		ia();

	return TRUE;
}

#undef ADV