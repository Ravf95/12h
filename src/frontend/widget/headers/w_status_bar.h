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

#if !defined _H_W_STATUS_BAR_
#define _H_W_STATUS_BAR_

#include <gtk/gtk.h>

// @SUB-RUTINA 	:	w_statusbar_load_from_builder()
// @UTILIDAD	:	obtiene y almacena la direccion de memoria
//					del statusbar de la ventana principal.
// @PARAMETROS	: 	builder > manipulador de archivos .glade.
// @RETORNO		:	ninguno.
void w_statusbar_load_from_builder(GtkBuilder *builder);

// @SUB-RUTINA 	:	w_statusbar_change_value()
// @UTILIDAD	:	establecer y actualizar los valores
//					de la barra de estado de acuerdo al turno
//					y los datos de los jugadores actuales.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	niguno.
void w_statusbar_change_value(void);

// @SUB-RUTINA 	:	w_statusbar_update_endgame()
// @UTILIDAD 	:	mostrar el resultado final del juego.
// @PARAMETROS	:	r  		> 	razón de fin de juego.
//					winner  >	el jugador ganador.
// @RETORNO		:	ninguno.
void w_statusbar_update_endgame(guint8 winner, guint8 r);

// @SUB-RUTINA 	:	w_status_bar_hide()
// @UTILIDAD 	:	ocultar la barra de estado.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_status_bar_hide(void);

// @SUB-RUTINA 	:	w_status_bar_show()
// @UTILIDAD 	:	mostrar la barra de estado.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_status_bar_show(void);

#endif	// _H_W_STATUS_BAR_