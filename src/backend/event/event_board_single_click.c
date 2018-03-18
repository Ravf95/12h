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
#include "w_macros.h"
#include "f_game.h"
#include "f_fichas.h"
#include "f_mill.h"

// @SUB-RUTINA	: 	event_board_single_click(guint8 )
// @UTILIDAD	:	gestionar los mill del tablero.
// @PARAMETROS	:	target_id 	> id de la casilla seleccionada.
/// @RETORNO	:	TRUE	> las operaciones a realizar con la casilla finalizaron
//					FALSE	> las operaciones a realizar con la casilla no finalizaron
gboolean event_board_single_click(guint8 target_id)
{
	void f_gamerules_check(void);

	GtkWidget *target_child;
	unsigned short int enemy;
	unsigned short int player;
	unsigned short int widget_owner;

	target_child = w_board_get_widget(target_id);

	// la casilla seleccionada 
	// no tiene ficha
	if (!target_child)
		return FALSE;		

	player = f_game_get_turno();
	widget_owner = W_FICHA_GET_OWNER(target_child);

	// si la ficha seleccionada a eliminar
	// es del jugador actual, entonces no es válida.
	if (widget_owner == player)
		return FALSE;

	enemy = f_game_get_adv();

	// ¿todas las fichas del adversario forman mill?
	if (!f_mill_check_all(enemy))
	{
		// sino se comprueba que la ficha seleccionada
		// no este formando mill.
		if (f_mill(target_id, enemy))
			return FALSE;
	}

	// se remueve la ficha seleccionada del tablero.
	w_board_remove_widget(target_id);
	g_object_unref(G_OBJECT(target_child));

	// se remueve la ficha de la cola de fichas del adversario.
	// se disminuye la cantidad de fichas del adversario.
	f_fichas_queue_remove_item(enemy, target_id);

	// se actualiza el contador de mill para el jugador actual.
	// no hay mill pendientes a gestionar en el juego.
	// se actualizan los datos del juego.
	f_fichas_player_mill_count(player);
	f_mill_toggle_status(FALSE);
	f_game_terminar_turno();

	return TRUE;
}