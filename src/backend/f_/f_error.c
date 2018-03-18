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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/f_log.h"
#include "headers/f_error.h"

#ifndef F_LOG_USE_FILE
#include <glib.h>
#include <glib/gprintf.h>
#endif

/* ================================================================================
	SUB-RUTINAS LOCALES
   ================================================================================*/

static void f_error_log_exit_failure(const char *msg);
static void f_error_log(const char *msg);

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	:	f_error_log_ptr_null(void *, const char *, const char *, unsigned short int )
// @UTILIDAD	:	evaluar la dirección almacenada por un puntero,
//					si esta es null, reportar y finalizar la ejecución del programa.
// @PARAMETROS	:	ptr 	> puntero a evaluar.
//					msg		> nombre de la variable a evaluar.
//					file 	> archivo de origen.
//					line    > linea actual donde se encuentra la variable a evaluar.
// @RETORNO		:	ninguno.
void f_error_log_ptr_null(void *ptr, const char *msg, const char *file, unsigned short int line)
{
	char buffer[128];

	if (!ptr)
	{
		snprintf(buffer, sizeof(buffer), "%s - null pointer %s - line: %hu\n", file, msg, line);
		f_error_log_exit_failure(buffer);
	}
}

// @SUB-RUTINA 	:	f_error_log_value(const char *, const char *, unsigned short int )
// @UTILIDAD	:	repotar y finalizar la ejecución del programa si la variable
//					tiene un valor no válido.
// @PARAMETROS	:	msg		> nombre de la variable a evaluar.
//					file 	> archivo de origen.
//					line 	> linea actual donde se encuentra la variable a evaluar.
// @RETORNO		:	ninguno.
void f_error_log_value(const char *msg, const char *file, unsigned short int line)
{
	char buffer[128];
	snprintf(buffer, sizeof(buffer), "%s - value error %s - line: %hu\n", file, msg, line);
	f_error_log_exit_failure(buffer);
}

// @SUB-RUTINA 	: 	f_error_log_exit_failure(const char *)
// @UTILIDAD	: 	finaliza el programa reportando la causa.
// @PARAMETROS	: 	msg > causa de la finalización.
// @RETORNO		:	ninguno.
static void f_error_log_exit_failure(const char *msg)
{
	f_error_log(msg);
	exit(EXIT_FAILURE);
}

// @SUB-RUTINA 	:	f_error_log(const char *)
// @UTILIDAD	:	genera el reporte.
// @PARAMETROS	:	msg > contenido del reporte.
// @RETORNO		:	ninguno.
static void f_error_log(const char *msg)
{
	char *buffer;
#ifdef F_LOG_USE_FILE
	FILE *log;
	f_open_log(&log, "a");
	buffer = f_log_get_formated_time(F_LOG_DATA_T_FORMAT);
	fprintf(log, "%s: %s\n", buffer, msg);
	fclose(log);
#else
	buffer = f_log_get_formated_time(F_LOG_DATA_T_FORMAT);
	g_printf("%s: %s\n", buffer, msg);
#endif	
}