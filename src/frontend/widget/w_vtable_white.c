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
#include "callback_vtable_white.h"
#include "headers/w_vtable_white.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_VTABLE_WHITE_FICHA_N			12
#define UI_VTABLE_WHITE_FICHA_WIDGET_S	"eventbox_vtable_ficha_blanca_"

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static gulong g_handler_id[UI_VTABLE_WHITE_FICHA_N];
static GtkWidget *g_vtable_white_widget[UI_VTABLE_WHITE_FICHA_N];

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	:	w_vtable_white_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene y almacena la dirección de memoria de las 
//					casillas del tablero 0 de la gui.
// @PARAMETROS	:	builder > manipulador de archivos .glade.
// @RETORNO		:	ninguno.
void w_vtable_white_load_from_builder(GtkBuilder *builder)
{
	char buffer[256];

	for (unsigned short int i = 0; i < UI_VTABLE_WHITE_FICHA_N; i++)
	{
		snprintf(buffer, sizeof(buffer), "%s%d", UI_VTABLE_WHITE_FICHA_WIDGET_S, i + 1);
		g_vtable_white_widget[i] = GTK_WIDGET(gtk_builder_get_object(builder, buffer));
		F_ERROR_LOG_CHECK_PTR(g_vtable_white_widget[i]);
	}
}

// @SUB-RUTINA 	:	w_vtable_get_white_widget(unsigned short int )
// @UTILIDAD	:	retorna la dirección del hijo de una casilla
//					determinada del tablero 0.
// @PARAMETROS	: 	i > id de la casilla.
// @RETORNO		:	dirección del hijo de la casilla.
GtkWidget *w_vtable_get_white_widget(unsigned short int i)
{
	if (i < 0 || i >= UI_VTABLE_WHITE_FICHA_N)
		F_ERROR_LOG_VALUE(i);

	GtkWidget *child;
	child = gtk_bin_get_child(GTK_BIN(g_vtable_white_widget[i]));

	return child;
}

// @SUB-RUTINA 	:	w_vtable_white_widget_signal_connect()
// @UTILIDAD	:	establer la señal de presionar botón
//					para las casillas del tablero 0 y 
//					asignar a cada casilla las propiedades
//					- ID 	(identificador único)
//					- SRC 	(origen de la casilla)
//					también asigna a cada hijo de la casilla
//					la propiedad
//					- OWNER (dueño de la ficha correspondiente)
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_vtable_white_widget_signal_connect(void)
{
	GtkWidget *child;

	for (unsigned short int i = 0; i < UI_VTABLE_WHITE_FICHA_N; i++)
	{
		child = w_vtable_get_white_widget(i);
		F_ERROR_LOG_CHECK_PTR(child);

		W_WIDGET_SET_DATA(child, "owner", 0);
		W_WIDGET_SET_DATA(g_vtable_white_widget[i], "id", i);
		W_WIDGET_SET_DATA(g_vtable_white_widget[i], "src", UI_VTABLE_WHITE_SRC);

		g_handler_id[i] = g_signal_connect
		(
			G_OBJECT(g_vtable_white_widget[i]),
           	"button_press_event",
           	G_CALLBACK(callback_vtable_white),
           	GUINT_TO_POINTER(i)
		);

		if (!g_handler_id[i])
			F_ERROR_LOG_VALUE(g_handler_id[i])
	}
}

// @SUB-RUTINA 	:	w_vtable_remove_white_widget(unsigned short int )
// @UTILIDAD	:	remover de una casilla determinada el hijo actual.
// @PARAMETROS	:	i > id de la casilla.
// @RETORNO		:	ninguno.
void w_vtable_remove_white_widget(unsigned short int i)
{
	GtkWidget *child;
	child = w_vtable_get_white_widget(i);
	F_ERROR_LOG_CHECK_PTR(child);
	
	g_object_ref(G_OBJECT(child));
	g_signal_handler_disconnect(g_vtable_white_widget[i], g_handler_id[i]);
	gtk_container_remove(GTK_CONTAINER(g_vtable_white_widget[i]), child);
}

// @SUB-RUTINA 	:	w_vtable_white_hide()
// @UTILIDAD 	:	ocultar las casillas del tablero 0.
// @PAREMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_vtable_white_hide(void)
{
	for (unsigned short int i = 0; i < UI_VTABLE_WHITE_FICHA_N; i++)
		gtk_widget_hide(g_vtable_white_widget[i]);
}

// @SUB-RUTINA 	:	w_table_white_show()
// @UTILIDAD 	:	mostrar las casillas del tablero 0.
// @PAREMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_table_white_show(void)
{
	for (unsigned short int i = 0; i < UI_VTABLE_WHITE_FICHA_N; i++)
		gtk_widget_show(g_vtable_white_widget[i]);	
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_VTABLE_WHITE_FICHA_N
#undef UI_VTABLE_WHITE_FICHA_WIDGET_S