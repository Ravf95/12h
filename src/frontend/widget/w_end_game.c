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

#include <stdio.h>
#include <gtk/gtk.h>
#include "f_error.h"
#include "headers/w_end_game.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_END_GAME_WIDGET_N			5

#define UI_END_GAME_W 					g_widget[0]
#define UI_END_GAME_W_LABEL_WINNER		g_widget[1]
#define UI_END_GAME_W_LABEL_INFO		g_widget[2]
#define UI_END_GAME_W_MSG				g_widget[3]	
#define UI_END_GAME_W_BUTTON_OK			g_widget[4]	

#define S_SIGNAL_CONNECT_SWAPPED(HANDLER_ID, WIDGET, EVENT, CALLBACK, HANDLER)\
HANDLER_ID = g_signal_connect_swapped(G_OBJECT(WIDGET), EVENT, G_CALLBACK(CALLBACK), HANDLER);\
if (!HANDLER_ID)\
	F_ERROR_LOG_VALUE(handle_id);

#define CHECK_VAR_VALUE(VAR, MAXVALUE)\
	if (VAR > MAXVALUE)\
		F_ERROR_LOG_VALUE(VAR);

#define S_(VAR, MSG)\
	(MSG != 1 && VAR == 0) ? "El " :\
	(MSG != 1 && VAR == 1) ? "La " :\
	""

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static const char * const g_widget_s[UI_END_GAME_WIDGET_N] =
{
	"window_dialog_endgame",
	"label_winner_dialog_endgame",
	"label_winner_info_dialog_endgame",
	"label_msg_winner_dialog_endgame",
	"button_ok_dialog_endgame"
};

static const char * const g_msg[3] =
{
	" tiene solo dos fichas en el tablero.",														// f2
	"Luego de varias jugadas ambos jugadores\nsiguen teniendo tres fichas en el tablero.",			// f3
	" ya no puede mover sus fichas."																// f1
};

static const char * const g_player_name[3] = 
{
	"Jugador 1",
	"Computadora",
	"Empate"
};

static GtkWidget *g_widget[UI_END_GAME_WIDGET_N];

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	:	w_end_game_load_from_builder(GtkBuilder * )
// @UTILIDAD	:	obtiene las direcciones de memoria de los
//					elementos de la ventana de fin de juego.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		:	ninguno.
void w_end_game_load_from_builder(GtkBuilder *builder)
{
	guint i;

	for (i = 0; i < UI_END_GAME_WIDGET_N; i++)
	{
		g_widget[i] = GTK_WIDGET(gtk_builder_get_object(builder, g_widget_s[i]));
		F_ERROR_LOG_CHECK_PTR(g_widget[i]);
	}
}

// @SUB-RUTINA 	:	w_end_game_signal_connect()
// @UTILIDAD	:	captar las señales de los elementos
//					de la ventana de inicio de fin de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_end_game_signal_connect(void)
{
	gulong handler_id;
	S_SIGNAL_CONNECT_SWAPPED(handler_id, UI_END_GAME_W , "delete_event", gtk_widget_hide, UI_END_GAME_W);
	S_SIGNAL_CONNECT_SWAPPED(handler_id, UI_END_GAME_W_BUTTON_OK, "button_press_event", gtk_widget_hide, UI_END_GAME_W);
}

// @SUB-RUTINA 	:	w_end_game_show()
// @UTILIDAD	:	mostrar la ventana de inicio de fin de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_end_game_show(guint8 id_winner, guint8 id_loser, guint8 id_msg)
{
	CHECK_VAR_VALUE(id_winner, 2);
	CHECK_VAR_VALUE(id_loser, 2);
	CHECK_VAR_VALUE(id_msg, 2);

	char temp[256];
	snprintf
	(
		temp, 
		sizeof(temp), 
		"%s%s%s", 
		S_(id_loser, id_msg), 
		(id_msg == 1) ? "" : g_player_name[id_loser], 
		g_msg[id_msg]
	);

	if (id_msg == 1)
	{
		id_winner = 2;
		gtk_widget_hide(UI_END_GAME_W_MSG);
	}

	gtk_label_set_text(GTK_LABEL(UI_END_GAME_W_LABEL_WINNER), g_player_name[id_winner]);
	gtk_label_set_text(GTK_LABEL(UI_END_GAME_W_LABEL_INFO), temp);
	gtk_widget_show_all(UI_END_GAME_W);
}

// @SUB-RUTINA 	:	w_end_game_destroy()
// @UTILIDAD	:	elimina todos los widget y referencias
//					asociados al contenedor principal.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_end_game_destroy(void)
{
	gtk_widget_destroy(UI_END_GAME_W);
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_END_GAME_WIDGET_N
#undef UI_END_GAME_W 
#undef UI_END_GAME_W_LABEL_WINNER
#undef UI_END_GAME_W_LABEL_INFO
#undef UI_END_GAME_W_MSG	
#undef UI_END_GAME_W_BUTTON_OK
#undef S_SIGNAL_CONNECT_SWAPPED
#undef S_