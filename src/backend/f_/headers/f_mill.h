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

#if !defined _H_F_MILL_
#define _H_F_MILL_

#include <gtk/gtk.h>

// @SUB-RUTINA	:	f_mill_valid_mchk_col(guint , guint8 )
// @UTILIDAD	:	verifica si la columna de la matriz de vectores
//					MCHK es válida.
// @PARAMETROS	:	id 	> 	identificador de casilla.
//					c 	> 	columna de la matriz de vectores.
// @RETORNO		:	TRUE	> 	es válida
//					FALSE	> 	no es válida. 
gboolean f_mill_valid_mchk_col(guint8 id, guint8 col);

// @SUB-RUTINA	:	f_mill_get_mchk_value(guint8 , guint8 , guint8 )
// @UTILIDAD	:	obtiene el elemento del vector apuntado por 
//					la matriz de vectores MCHK.
// @PARAMETROS	:	id 		>	identificador de casilla.
//					col 	>	vector.
//					i 		>	elemento del vector.
// @RETORNO		:	elemento del vector.
char f_mill_get_mchk_value(guint8 id, guint8 col, guint8 i);

// @SUB-RUTINA	:	f_mill(guint8 , guint8 )
// @UTILIDAD	:	verifica si una ficha determinada esta
//					formando mill en el tablero del juego.
// @PARAMETROS	:	id 			>	identificador de casilla.
//					id_owner	>	jugador.
// @RETORNO		:	TRUE	>	forma mill.
//					FALSE	>	no forma mill.
gboolean f_mill(guint8 id, guint8 id_owner);

// @SUB-RUTINA	:	f_mill_check_all(guint )
// @UTILIDAD	:	verifica si todas las fichas colocadas 
//					en el tablero de un jugador determinado 
//					estan formando mill.
// @PARAMETROS	:	player 	> 	identificador del jugador.
// @RETORNO		:	TRUE	>	todas sus fichas forman mill.
//					FALSE	>	no todas sus fichas forman mill.
gboolean f_mill_check_all(guint player);

// @SUB-RUTINA	:	f_mill_toggle_status(gboolean )
// @UTILIDAD	:	manejar el evento mill del juego.
// @PARAMETROS	:	toggle 	>	activado/desactivado.
// @RETORNO		:	ninguno.
void f_mill_toggle_status(gboolean toggle);

// @SUB-RUTINA	:	f_mill_status()
// @UTILIDAD	:	verificar si hay algun mill activo.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	TRUE	>	hay un mill activo.
//					FALSE	>	no hay un mill activo.
gboolean f_mill_status(void);

#endif // _H_F_MILL_