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

#if !defined _H_W_V_TABLE_BLACK_
#define _H_W_V_TABLE_BLACK

#include <gtk/gtk.h>

// id de origen de las fichas que 
// provienen de este tablero
#define UI_VTABLE_BLACK_SRC	2

// @SUB-RUTINA 	:	w_vtable_black_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene y almacena la dirección de memoria de las 
//					casillas del tablero 2 de la gui.
// @PARAMETROS	:	builder > manipulador de archivos .glade.
// @RETORNO		:	ninguno.
void w_vtable_black_load_from_builder(GtkBuilder *builder);

// @SUB-RUTINA 	:	w_vtable_black_widget_signal_connect()
// @UTILIDAD	:	establer la señal de presionar botón
//					para las casillas del tablero 2 y 
//					asignar a cada casilla las propiedades
//					- ID 	(identificador único)
//					- SRC 	(origen de la casilla)
//					también asigna a cada hijo de la casilla
//					la propiedad
//					- OWNER (dueño de la ficha correspondiente)
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_vtable_black_widget_signal_connect(void);

// @SUB-RUTINA 	:	w_vtable_remove_black_widget(unsigned short int )
// @UTILIDAD	:	remover de una casilla determinada el hijo actual.
// @PARAMETROS	:	i > id de la casilla.
// @RETORNO		:	ninguno.
void w_vtable_remove_black_widget(unsigned short int i);

// @SUB-RUTINA 	:	w_vtable_black_hide()
// @UTILIDAD	:	ocultar las casillas del tablero 2.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_vtable_black_hide(void);

// @SUB-RUTINA 	:	w_vtable_black_show()
// @UTILIDAD	:	mostar las casillas del tablero 2.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_vtable_black_show(void);

// @SUB-RUTINA 	:	w_vtable_get_black_widget(unsigned short int )
// @UTILIDAD	:	retorna la dirección del hijo de una casilla
//					determinada del tablero 2.
// @PARAMETROS	: 	i > id de la casilla.
// @RETORNO		:	dirección del hijo de la casilla.
GtkWidget *w_vtable_get_black_widget(unsigned short int i);

GtkWidget *w_vtable_black_get_parent(guint8 i);

#endif	//  _H_W_V_TABLE_BLACK_
