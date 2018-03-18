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

#if !defined _H_W_BOARD_
#define _H_W_BOARD_

#include <gtk/gtk.h>

// id de origen de las fichas que 
// provienen de este tablero
#define UI_BOARD_SRC	1

// @SUB-RUTINA	: 	w_board_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene las direcciones de memoria de las
//					casillas del tablero 1 de la gui para 
//					su correspondiente manipulación.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		: 	ninguno.
void w_board_load_from_builder(GtkBuilder *builder);

// @SUB-RUTINA	:	w_board_set_widget(unsigned short int , GtkWidget *)
// @UTILIDAD	:	asigna a una casilla determinada del tablero 1
//					un widget hijo.
// @PARAMETROS	:	i 		> id de la casilla
//					widget 	> widget hijo a asignar al padre
// @RETORNO		: 	ninguno.
void w_board_set_widget(unsigned short int i, GtkWidget *widget);

// @SUB-RUTINA	: 	w_board_remove_widget(unsigned short int )
// @UTILIDAD	:	remueve el contenido de una casilla
//					determinada del tablero 1.
// @PARAMETROS	:	i > id de la casilla
// @RETORNO		:	niguno.
void w_board_remove_widget(unsigned short int i);

// @SUB-RUTINA	:	w_board_signal_connect()
// @UTILIDAD	:	establecer la señal del evento presionar botón,
//					asigna a cada casilla las propiedades
//					- ID  (identificador único)
//					- SRC (origen de la casilla)
// @PARAMETROS	: 	ninguno.
// @RETORNO		:	ninguno.
void w_board_signal_connect(void);

// @SUB-RUTINA 	:	w_board_signal_disconnect()
// @UTILIDAD	:	desconectar la señal del evento presionar botón
//					de todas las casillas del tablero.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_board_signal_disconnect(void);

// @SUB-RUTINA	: 	w_board_get_parent(unsigned short int )
// @UTILIDAD	:	obtiene la dirección de memoria del hijo
//					de una casilla determinada a partir del ID.
// @PARAMETROS	:	i > id de la casilla
// @RETORNO		: 	dirección del widget hijo en la memoria.
GtkWidget *w_board_get_widget(unsigned short int i);

// @SUB-RUTINA	: 	w_board_get_parent(unsigned short int )
// @UTILIDAD	:	obtiene la dirección de memoria de
//					la casilla a partir del ID.
// @PARAMETROS	:	i > id de la casilla
// @RETORNO		: 	dirección del widget en la memoria.
GtkWidget *w_board_get_parent(unsigned short int i);

#endif	// _H_W_BOARD_