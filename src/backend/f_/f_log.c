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

#ifndef F_LOG_USE_FILE
#include <glib.h>
#include <glib/gprintf.h>
#endif

/* ================================================================================
	MACROS
   ================================================================================*/

#ifdef F_LOG_USE_FILE
#define F_LOG_FILE_F				"log%s.txt"
#define F_LOG_DIR					"..\\log\\"
#define F_LOG_FILE      			F_LOG_DIR F_LOG_FILE_F
/* ================================================================================
	VARIABLES LOCALES DEL ARCHIVO
   ================================================================================*/

static char g_name[128];
#endif

/* ================================================================================
	DEFINICIÓN DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA	:	f_new_log()
// @UTILIDAD	:	primer reporte en el registro del juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_new_log(void)
{

	char *buffer;
#ifdef F_LOG_USE_FILE
	buffer = f_log_get_formated_time(F_LOG_FILE_NAME_T_FORMAT);
	snprintf(g_name, sizeof(g_name), F_LOG_FILE, buffer);

	FILE *log;
	f_open_log(&log, "w");
	buffer = f_log_get_formated_time(F_LOG_DATA_T_FORMAT);
	fprintf(log, "%s: %s\n", buffer, F_LOG_T_START);
	fclose(log);
#else
	buffer = f_log_get_formated_time(F_LOG_DATA_T_FORMAT);
	g_printf("%s: %s\n", buffer, F_LOG_T_START);
#endif
}

// @SUB-RUTINA	:	f_log_exit()
// @UTILIDAD	:	último reporte en el registro del juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void f_log_exit(void)
{
	char *buffer;
#ifdef F_LOG_USE_FILE
	FILE *log;
	f_open_log(&log, "a");
	buffer = f_log_get_formated_time(F_LOG_DATA_T_FORMAT);
	fprintf(log, "%s: %s\n", buffer, F_LOG_T_END);
	fclose(log);
#else
	buffer = f_log_get_formated_time(F_LOG_DATA_T_FORMAT);
	g_printf("%s: %s\n", buffer, F_LOG_T_END);
#endif
}

#ifdef F_LOG_USE_FILE
// @SUB-RUTINA	:	f_open_log(FILE **, const char *)
// @UTILIDAD	:	acceso al archivo registro del juego.
// @PARAMETROS	:	file 	>	dirección del puntero simple a manipular el archivo.
//					mode	>	modo de acceso al archivo.
// @RETORNO		:	ninguno.
void f_open_log(FILE **file, const char *mode)
{
	*file = fopen(g_name, mode);

	if (!(*file))
	{
		perror(g_name);
		exit(EXIT_FAILURE);
	}
}
#endif

// @SUB-RUTINA	:	f_log_get_formated_time(const char *)
// @UTILIDAD	:	genera un forma de tiempo.
// @PARAMETROS	:	format 	> formato del tiempo.
// @RETORNO		:	string con formato.
char *f_log_get_formated_time(const char *format)
{
	time_t time;
	static char buffer[64];
	struct tm *timeinfo;

	time = _time64(NULL);
	timeinfo = localtime(&time);
	strftime(buffer, sizeof(buffer), format, timeinfo);

	return buffer;
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#ifdef F_LOG_USE_FILE
#undef F_LOG_FILE_F
#undef F_LOG_DIR
#undef F_LOG_FILE
#endif