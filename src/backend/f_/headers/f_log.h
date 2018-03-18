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

#if !defined _H_F_LOG_
#define _H_F_LOG_
#include <stdio.h>

#define F_LOG_USE_FILE

#ifdef F_LOG_USE_FILE
#define F_LOG_FILE_NAME_T_FORMAT	"_%d_%m_%Y__%H_%M_%S"
#endif
#define F_LOG_DATA_T_FORMAT			"%d/%m/%Y - %H_%M_%S"
#define F_LOG_T_START				"Start Register"
#define F_LOG_T_END					"End Register"

// @SUB-RUTINA	:	f_new_log()
// @UTILIDAD	:	primer reporte en el registro del juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_new_log(void);

// @SUB-RUTINA	:	f_log_exit()
// @UTILIDAD	:	último reporte en el registro del juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_log_exit(void);
#ifdef F_LOG_USE_FILE

// @SUB-RUTINA	:	f_open_log(FILE **, const char *)
// @UTILIDAD	:	acceso al archivo registro del juego.
// @PARAMETROS	:	file 	>	dirección del puntero simple a manipular el archivo.
//					mode	>	modo de acceso al archivo.
// @RETORNO		:	ninguno.
void f_open_log(FILE **file, const char *mode);
#endif

// @SUB-RUTINA	:	f_log_get_formated_time(const char *)
// @UTILIDAD	:	genera un forma de tiempo.
// @PARAMETROS	:	format 	> formato del tiempo.
// @RETORNO		:	string con formato.
char *f_log_get_formated_time(const char *format);

#endif