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

#include <gtk/gtk.h>
#include "f_error.h"
#include "headers/w_about.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_ABOUT_WIDGET_S	"window_aboutdialog"

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

static GtkWidget *g_widget;

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

void w_about_load_from_builder(GtkBuilder *builder)
{
	g_widget = GTK_WIDGET(gtk_builder_get_object(builder, UI_ABOUT_WIDGET_S));
	F_ERROR_LOG_CHECK_PTR(g_widget);
}

void w_about_show(void)
{
	gtk_dialog_run(GTK_DIALOG(g_widget));
	gtk_widget_hide(g_widget);
}

void w_about_destroy(void)
{
	gtk_widget_destroy(g_widget);
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_ABOUT_WIDGET_S