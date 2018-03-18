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
#include "w_window.h"
#include "w_board.h"
#include "w_vtable_white.h"
#include "w_vtable_black.h"
#include "w_status_bar.h"
#include "w_new_game.h"
#include "w_end_game.h"
#include "w_about.h"
#include "w_menubar.h"
#include "f_error.h"
#include "f_game.h"
#include "ui.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define UI_GLADE_FILE 					"..\\res\\ui_12h.glade"
#define UI_CSS_FILE						"..\\res\\css_12h.css"

#define LOAD(WIDGET)					w_##WIDGET##_load_from_builder(builder)
#define SIGNAL(WIDGET)					w_##WIDGET##_signal_connect()
#define HIDE(WIDGET)					w_##WIDGET##_hide()
#define DESTROY(WIDGET)					w_##WIDGET##_destroy()

/* ================================================================================
	PROTOTIPOS DE SUB-RUTINAS LOCALES
   ================================================================================*/

static void css_load(void);

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	: 	ui_init()
// @UTILIDAD	:	inicializar los elementos de la interfaz
//					grafica de usuario.
// @RETORNO 	: 	ninguno.
void ui_init(void)
{
	GtkBuilder *builder = NULL;
	gtk_init(NULL, NULL);
	builder = gtk_builder_new_from_file(UI_GLADE_FILE);
	
	LOAD(main_window);
	LOAD(board);
	LOAD(vtable_white);
	LOAD(vtable_black);
	LOAD(statusbar);
	LOAD(menubar);
	LOAD(new_game);
	LOAD(end_game);
	LOAD(about);

	SIGNAL(main_window);
	SIGNAL(menubar);
	SIGNAL(new_game);
	SIGNAL(main_window);

	w_main_window_show_all();

	HIDE(status_bar);
	HIDE(vtable_white);
	HIDE(vtable_black);

	css_load();
	gtk_main();

	DESTROY(end_game);
	DESTROY(main_window);
	DESTROY(about);
}

// @SUB-RUTINA 	: 	css_load()
// @UTILIDAD 	:	cargar y permitir la modificación
//					de elementos de la interfaz 
// 					por CSS.
// @RETORNO 	:	ninguno.
static void css_load(void)
{
	GtkCssProvider 	*css;
	GdkDisplay		*display;
	GdkScreen 		*screen;
	gboolean 		css_loader;

	css = gtk_css_provider_new();

	css_loader = gtk_css_provider_load_from_path(css, UI_CSS_FILE, NULL);

	if (!css_loader)
		F_ERROR_LOG_VALUE(css_loader);

	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);

	// las propiedades visuales de los widgets
	// se muestran en pantalla
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef UI_GLADE_FILE
#undef UI_CSS_FILE
#undef LOAD
#undef SIGNAL
#undef HIDE
#undef DESTROY