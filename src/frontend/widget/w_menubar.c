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
#include "w_about.h"
#include "f_error.h"
#include "callback_menubar.h"
#include "headers/w_menubar.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_BARMENU_WIDGET_N				3

#define UI_BARMENU_W_ITEM_NEW_GAME		g_widget[0]
#define UI_BARMENU_W_ITEM_QUIT			g_widget[1]
#define UI_BARMENU_W_ITEM_ABOUT			g_widget[2]

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

static const char * const g_widget_s[UI_BARMENU_WIDGET_N] = 
{
	"menubar_file_newgame",
	"menubar_file_quit",
	"menubar_help_about"
};

static GtkWidget *g_widget[UI_BARMENU_WIDGET_N];

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	: 	w_menubar_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene las direcciones de memoria de los
//					items de la barra de menu.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		: 	ninguno.
void w_menubar_load_from_builder(GtkBuilder *builder)
{
	guint8 i;

	for (i = 0; i < UI_BARMENU_WIDGET_N; i++)
	{
		g_widget[i] = GTK_WIDGET(gtk_builder_get_object(builder, g_widget_s[i]));
		F_ERROR_LOG_CHECK_PTR(g_widget[i]);
	}
}

// @SUB-RUTINA 	:	w_menubar_signal_connect()
// @UTILIDAD	:	captar la señal press button de los
//					items del barmenu.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_menubar_signal_connect(void)
{
	gulong handler_id;

	S_SIGNAL_CONNECT(handler_id, UI_BARMENU_W_ITEM_NEW_GAME, "activate", callback_barmenu_newgame);
	S_SIGNAL_CONNECT_SWAPPED(handler_id, UI_BARMENU_W_ITEM_QUIT, "activate", gtk_main_quit, NULL);
	S_SIGNAL_CONNECT_SWAPPED(handler_id, UI_BARMENU_W_ITEM_ABOUT, "activate", w_about_show, NULL);
}


/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_BARMENU_WIDGET_N
#undef UI_BARMENU_W_ITEM_NEW_GAME
#undef UI_BARMENU_W_ITEM_QUIT
#undef UI_BARMENU_W_ITEM_ABOUT
#undef S_SIGNAL_CONNECT
#undef S_SIGNAL_CONNECT_SWAPPED