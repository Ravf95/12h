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

#if !defined _H_CALLBACK_NEW_GAME_
#define _H_CALLBACK_NEW_GAME_

#include <gtk/gtk.h>

// @SUB-RUTINA	:	callback_new_game_ok(GtkWidget *, GdkEvent *, gpointer )
// @UTILIDAD	:	establecer el inicio del juego.
// @PARAMETROS	:	widget 		>	elemento de la gui asociado.
//					event 		>	evento por el cual es llamado.
//					data		>	apuntador a un tipo de dato externo asociado al widget.
// @RETORNO		:	TRUE		> 	no hay operaciones pendientes.
gboolean callback_new_game_ok(GtkWidget *widget, GdkEvent *event, gpointer data);

#endif // _H_CALLBACK_NEW_GAME_