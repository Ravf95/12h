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

#if !defined _H_W_MACROS_
#define _H_W_MACROS_

#include <gtk/gtk.h>

#define W_FICHA_GET_OWNER(CHILD)				GPOINTER_TO_INT(g_object_get_data(G_OBJECT(CHILD), "owner"))
#define W_CASILLA_GET_ID(WIDGET)				GPOINTER_TO_INT(g_object_get_data(G_OBJECT(WIDGET), "id"))
#define W_CASILLA_GET_SRC(WIDGET)				GPOINTER_TO_INT(g_object_get_data(G_OBJECT(WIDGET), "src"))

#define W_WIDGET_SET_DATA(WIDGET, TAG, VALUE)	g_object_set_data(G_OBJECT(WIDGET), TAG, GUINT_TO_POINTER(VALUE))

#endif // _H_W_MACROS_