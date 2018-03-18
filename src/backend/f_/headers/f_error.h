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

#if !defined _H_F_ERROR_
#define _H_F_ERROR_

// @SUB-RUTINA 	:	f_error_log_ptr_null(void *, const char *, const char *, unsigned short int )
// @UTILIDAD	:	evaluar la dirección almacenada por un puntero,
//					si esta es null, reportar y finalizar la ejecución del programa.
// @PARAMETROS	:	ptr 	> puntero a evaluar.
//					msg		> nombre de la variable a evaluar.
//					file 	> archivo de origen.
//					line    > linea actual donde se encuentra la variable a evaluar.
// @RETORNO		:	ninguno.
void f_error_log_ptr_null(void *ptr, const char *msg, const char *file, unsigned short int line);

// @SUB-RUTINA 	:	f_error_log_value(const char *, const char *, unsigned short int )
// @UTILIDAD	:	repotar y finalizar la ejecución del programa si la variable
//					tiene un valor no válido.
// @PARAMETROS	:	msg		> nombre de la variable a evaluar.
//					file 	> archivo de origen.
//					line 	> linea actual donde se encuentra la variable a evaluar.
// @RETORNO		:	ninguno.
void f_error_log_value(const char *msg, const char *file, unsigned short int line);

// todo:
// enumerar errores + mensaje de error

#define F_ERROR_VAR_NAME(VAR) 			#VAR
#define F_ERROR_LOG_CHECK_PTR(VAR)		f_error_log_ptr_null(VAR, F_ERROR_VAR_NAME(VAR), __FILE__, __LINE__);
#define F_ERROR_LOG_VALUE(VAR)			f_error_log_value(F_ERROR_VAR_NAME(VAR), __FILE__, __LINE__);

#endif	// _H_F_ERROR_