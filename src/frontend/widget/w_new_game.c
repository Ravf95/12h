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
#include "f_error.h"
#include "callback_new_game.h"
#include "headers/w_new_game.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_NEW_GAME_WIDGET_N			5

#define UI_NEW_GAME_W					g_widget[0]
#define UI_NEW_GAME_W_RB_HC				g_widget[1]
#define UI_NEW_GAME_W_RB_CH 			g_widget[2]
#define UI_NEW_GAME_W_BUTTON_OK			g_widget[3]
#define UI_NEW_GAME_W_BUTTON_CANCEL		g_widget[4]

#define TOGGLED(WIDGET)					gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(WIDGET))

#define S_SIGNAL_CONNECT(HANDLER_ID, WIDGET, EVENT, CALLBACK)\
HANDLER_ID = g_signal_connect(G_OBJECT(WIDGET), EVENT, G_CALLBACK(CALLBACK), NULL);\
if (!HANDLER_ID)\
	F_ERROR_LOG_VALUE(handle_id);

#define S_SIGNAL_CONNECT_SWAPPED(HANDLER_ID, WIDGET, EVENT, CALLBACK, HANDLER)\
HANDLER_ID = g_signal_connect_swapped(G_OBJECT(WIDGET), EVENT, G_CALLBACK(CALLBACK), HANDLER);\
if (!HANDLER_ID)\
	F_ERROR_LOG_VALUE(handle_id);

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static const char * const g_widget_s[UI_NEW_GAME_WIDGET_N] =
{
	"window_new_game",
	"radiobutton_hc",
	"radiobutton_ch",
	"button_ok_game",
	"button_cancel_game"
};

static GtkWidget *g_widget[UI_NEW_GAME_WIDGET_N];

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	:	w_new_game_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene las direcciones de memoria de los
//					elementos de la ventana de inicio de juego.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		:	ninguno.
void w_new_game_load_from_builder(GtkBuilder *builder)
{
	guint i;

	for (i = 0; i < UI_NEW_GAME_WIDGET_N; i++)
	{
		g_widget[i] = GTK_WIDGET(gtk_builder_get_object(builder, g_widget_s[i]));
		F_ERROR_LOG_CHECK_PTR(g_widget[i]);
	}
}

// @SUB-RUTINA 	:	w_new_game_signal_connect()
// @UTILIDAD	:	captar las señales de los elementos
//					de la ventana de inicio de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_new_game_signal_connect(void)
{
	gulong handler_id;
	S_SIGNAL_CONNECT_SWAPPED(handler_id, UI_NEW_GAME_W, "delete_event", gtk_widget_hide, UI_NEW_GAME_W);
	S_SIGNAL_CONNECT(handler_id, UI_NEW_GAME_W_BUTTON_OK, "button_press_event", callback_new_game_ok);
	S_SIGNAL_CONNECT_SWAPPED(handler_id, UI_NEW_GAME_W_BUTTON_CANCEL, "button_press_event", gtk_widget_hide, UI_NEW_GAME_W);
}

// @SUB-RUTINA 	:	w_new_game_show()
// @UTILIDAD	:	mostrar la ventana de inicio de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_new_game_show(void)
{
	gtk_widget_show_all(UI_NEW_GAME_W);
}

// @SUB-RUTINA 	:	w_new_game_quick_exit()
// @UTILIDAD	:	ocultar la ventana de inicio de juego
//					para su posterior uso.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_new_game_quick_exit(void)
{
	gtk_widget_hide(UI_NEW_GAME_W);
}

// @SUB-RUTINA 	:	w_new_game_get_mode()
// @UTILIDAD	:	obtener el rb seleccionado.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	identificador del rb seleccionado.
guint8 w_new_game_get_mode(void)
{
	if (TOGGLED(UI_NEW_GAME_W_RB_HC))
		return 0;

	return 1;
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_NEW_GAME_WIDGET_N
#undef UI_NEW_GAME_W
#undef UI_NEW_GAME_W_RB_HC	
#undef UI_NEW_GAME_W_RB_CH
#undef UI_NEW_GAME_W_BUTTON_OK
#undef UI_NEW_GAME_W_BUTTON_CANCEL
#undef TOGGLED
#undef S_SIGNAL_CONNECT
#undef S_SIGNAL_CONNECT_SWAPPED