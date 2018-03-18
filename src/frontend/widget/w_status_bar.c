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
#include <string.h>
#include <gtk/gtk.h>
#include "f_fichas.h"
#include "f_game.h"
#include "f_error.h"
#include "headers/w_status_bar.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_STATUSBAR_LABEL_WIDGET	"statusbar_info"
#define UI_STATUSBAR_T_TURNO		"Turno: "
#define UI_STATUSBAR_T_FBC			"Fichas Blancas Capturadas: "
#define UI_STATUSBAR_T_FNC			"Fichas Negras Capturadas: "
#define UI_STATUSBAR_T_ENDGAME		"El juego termino el ganador es: "

/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static const char * const player_tag[3] =
{
	"J1",
	"PC",
	"Empate"
};

static GtkWidget *g_label_statusbar_widget;

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	:	w_statusbar_load_from_builder()
// @UTILIDAD	:	obtiene y almacena la direccion de memoria
//					del statusbar de la ventana principal.
// @PARAMETROS	: 	builder > manipulador de archivos .glade.
// @RETORNO		:	ninguno.
void w_statusbar_load_from_builder(GtkBuilder *builder)
{
	g_label_statusbar_widget = GTK_WIDGET(gtk_builder_get_object(builder, UI_STATUSBAR_LABEL_WIDGET));
	F_ERROR_LOG_CHECK_PTR(g_label_statusbar_widget);
}

// @SUB-RUTINA 	:	w_statusbar_change_value()
// @UTILIDAD	:	establecer y actualizar los valores
//					de la barra de estado de acuerdo al turno
//					y los datos de los jugadores actuales.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	niguno.
void w_statusbar_change_value(void)
{
	char buffer[128];
	snprintf
	(
		buffer, 
		sizeof(buffer), 
		"\t%s%s\t\t%s%hu\t%7s%s%hu", 
		UI_STATUSBAR_T_TURNO,
		player_tag[f_game_get_turno()],  
		UI_STATUSBAR_T_FBC, 
		f_get_player_fichas_robadas(0),
		"", 
		UI_STATUSBAR_T_FNC, 
		f_get_player_fichas_robadas(1)
	);

	gtk_label_set_text(GTK_LABEL(g_label_statusbar_widget), buffer);
}

// @SUB-RUTINA 	:	w_statusbar_update_endgame()
// @UTILIDAD 	:	mostrar el resultado final del juego.
// @PARAMETROS	:	r  		> 	razón de fin de juego.
//					winner  >	el jugador ganador.
// @RETORNO		:	ninguno.
void w_statusbar_update_endgame(guint8 winner, guint8 r)
{
	char buffer[128];
	snprintf(buffer, sizeof(buffer), UI_STATUSBAR_T_ENDGAME);

	if (r == 1)
	{
		strncat(buffer, player_tag[2], sizeof(buffer));
		return;
	}

	strncat(buffer, player_tag[winner], sizeof(buffer));
	gtk_label_set_text(GTK_LABEL(g_label_statusbar_widget), buffer);
}

// @SUB-RUTINA 	:	w_status_bar_hide()
// @UTILIDAD 	:	ocultar la barra de estado.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_status_bar_hide(void)
{
	gtk_widget_hide(g_label_statusbar_widget);
}

// @SUB-RUTINA 	:	w_status_bar_show()
// @UTILIDAD 	:	mostrar la barra de estado.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_status_bar_show(void)
{
	gtk_widget_show(g_label_statusbar_widget);
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_STATUSBAR_LABEL_WIDGET
#undef UI_STATUSBAR_T_TURNO
#undef UI_STATUSBAR_T_FBC
#undef UI_STATUSBAR_T_FNC
#undef UI_STATUSBAR_T_ENDGAME