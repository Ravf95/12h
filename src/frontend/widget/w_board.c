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
#include "w_macros.h"
#include "f_error.h"
#include "callback_board.h"
#include "headers/w_board.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_BOARD_WIDGET_N	24
#define UI_BOARD_WIDGET_S	"eventbox_board_ficha_"

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static gulong g_handler_id[UI_BOARD_WIDGET_N];
static GtkWidget *g_board_widget[UI_BOARD_WIDGET_N];

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	: 	w_board_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene las direcciones de memoria de las
//					casillas del tablero 1 de la gui para 
//					su correspondiente manipulación.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		: 	ninguno.
void w_board_load_from_builder(GtkBuilder *builder)
{
	char buffer[256];

	for (unsigned short int i = 0; i < UI_BOARD_WIDGET_N; i++)
	{
		snprintf(buffer, sizeof(buffer), "%s%d", UI_BOARD_WIDGET_S, i + 1);
		g_board_widget[i] = GTK_WIDGET(gtk_builder_get_object(builder, buffer));
		F_ERROR_LOG_CHECK_PTR(g_board_widget[i]);
	}
}

// @SUB-RUTINA	: 	w_board_get_parent(unsigned short int )
// @UTILIDAD	:	obtiene la dirección de memoria de
//					la casilla a partir del ID.
// @PARAMETROS	:	i > id de la casilla
// @RETORNO		: 	dirección del widget en la memoria.
GtkWidget *w_board_get_parent(unsigned short int i)
{
	if (i < 0 || i >= UI_BOARD_WIDGET_N)
		F_ERROR_LOG_VALUE(i);

	return g_board_widget[i];
}

// @SUB-RUTINA	: 	w_board_get_parent(unsigned short int )
// @UTILIDAD	:	obtiene la dirección de memoria del hijo
//					de una casilla determinada a partir del ID.
// @PARAMETROS	:	i > id de la casilla
// @RETORNO		: 	dirección del widget hijo en la memoria.
GtkWidget *w_board_get_widget(unsigned short int i)
{
	if (i < 0 || i >= UI_BOARD_WIDGET_N)
		F_ERROR_LOG_VALUE(i);

	GtkWidget *child;
	child = gtk_bin_get_child(GTK_BIN(g_board_widget[i]));

	return child;
}

// @SUB-RUTINA	:	w_board_set_widget(unsigned short int , GtkWidget *)
// @UTILIDAD	:	asigna a una casilla determinada del tablero 1
//					un widget hijo.
// @PARAMETROS	:	i 		> id de la casilla
//					widget 	> widget hijo a asignar al padre
// @RETORNO		: 	ninguno.
void w_board_set_widget(unsigned short int i, GtkWidget *widget)
{
	if (i < 0 || i >= UI_BOARD_WIDGET_N)
		F_ERROR_LOG_VALUE(i);

	gtk_container_add(GTK_CONTAINER(g_board_widget[i]), widget);
}

// @SUB-RUTINA	: 	w_board_remove_widget(unsigned short int )
// @UTILIDAD	:	remueve el contenido de una casilla
//					determinada del tablero 1.
// @PARAMETROS	:	i > id de la casilla
// @RETORNO		:	niguno.
void w_board_remove_widget(unsigned short int i)
{
	GtkWidget *child;
	child = w_board_get_widget(i);
	F_ERROR_LOG_CHECK_PTR(child);
	
	g_object_ref(G_OBJECT(child));
	gtk_container_remove(GTK_CONTAINER(g_board_widget[i]), child);
}

// @SUB-RUTINA	:	w_board_signal_connect()
// @UTILIDAD	:	establecer la señal del evento presionar botón,
//					asigna a cada casilla las propiedades
//					- ID  (identificador único)
//					- SRC (origen de la casilla)
// @PARAMETROS	: 	ninguno.
// @RETORNO		:	ninguno.
void w_board_signal_connect(void)
{
	for (unsigned short int i = 0; i < UI_BOARD_WIDGET_N; i++)
	{
		W_WIDGET_SET_DATA(g_board_widget[i], "id", i);
		W_WIDGET_SET_DATA(g_board_widget[i], "src", UI_BOARD_SRC);

		g_handler_id[i] = g_signal_connect
		(
			G_OBJECT(g_board_widget[i]),
           	"button_press_event",
           	G_CALLBACK(callback_board),
           	GUINT_TO_POINTER(i)
		);

		if (!g_handler_id[i])
			F_ERROR_LOG_VALUE(g_handler_id[i]);
	}
}

// @SUB-RUTINA 	:	w_board_signal_disconnect()
// @UTILIDAD	:	desconectar la señal del evento presionar botón
//					de todas las casillas del tablero.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_board_signal_disconnect(void)
{
	for (unsigned short int i = 0; i < UI_BOARD_WIDGET_N; i++)
		g_signal_handler_disconnect(g_board_widget[i], g_handler_id[i]);
}

gulong w_board_get_signal_handler(guint8 i)
{
	if (i < 0 || i >= UI_BOARD_WIDGET_N)
		F_ERROR_LOG_VALUE(i);

	return g_handler_id[i];
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_BOARD_WIDGET_N
#undef UI_BOARD_WIDGET_S