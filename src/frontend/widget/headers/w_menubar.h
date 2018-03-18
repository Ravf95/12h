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

#if !defined _H_W_BARMENU_
#define _H_W_BARMENU_

// @SUB-RUTINA	: 	w_menubar_load_from_builder(GtkBuilder *)
// @UTILIDAD	:	obtiene las direcciones de memoria de los
//					items de la barra de menu.
// @PARAMETROS	:	builder > dirección del manipulador de archivos .glade
// @RETORNO		: 	ninguno.
void w_menubar_load_from_builder(GtkBuilder *builder);

// @SUB-RUTINA 	:	w_barmenu_signal_connect()
// @UTILIDAD	:	captar la señal press button de los
//					items del barmenu.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void w_menubar_signal_connect(void);

#endif // _H_W_BARMENU_