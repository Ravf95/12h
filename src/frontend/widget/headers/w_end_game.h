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

#if !defined _H_END_GAME_
#define _H_END_GAME_

// @SUB-RUTINA 	:	w_end_game_load_from_builder(GtkBuilder * )
// @UTILIDAD	:	obtiene las direcciones de memoria de los
//					elementos de la ventana de fin de juego.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		:	ninguno.
void w_end_game_load_from_builder(GtkBuilder *builder);

// @SUB-RUTINA 	:	w_end_game_signal_connect()
// @UTILIDAD	:	captar las señales de los elementos
//					de la ventana de inicio de fin de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_end_game_signal_connect(void);

// @SUB-RUTINA 	:	w_end_game_show()
// @UTILIDAD	:	mostrar la ventana de inicio de fin de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_end_game_show(guint8 id_winner, guint8 id_loser, guint8 id_msg);

// @SUB-RUTINA 	:	w_end_game_destroy()
// @UTILIDAD	:	elimina todos los widget y referencias
//					asociados al contenedor principal.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_end_game_destroy(void);

#endif // _H_END_GAME_