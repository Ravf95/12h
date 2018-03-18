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

#if !defined _H_CALLBACK_BOARD_
#define _H_CALLBACK_BOARD_

// @SUB-RUTINA	:	callback_board(GtkWidget *, GdkEvent *, gpointer )
// @UTILIDAD	:	captar y manipular las fichas que son colocadas
//					en el tablero 1 mediante la señal press button.
// @PARAMETROS	:	target 			>	widget event box asociado al tablero (la casilla)
//					target_event 	>	evento por el cual es llamado
//					target_data		>	apuntador a un tipo de dato externo asociado al widget
// @RETORNO		:	TRUE	> las operaciones a realizar con la casilla finalizaron
//					FALSE	> las operaciones a realizar con la casilla no finalizaron
gboolean callback_board(GtkWidget *widget, GdkEvent *event, gpointer user_data);

#endif	// _H_CALLBACK_BOARD_