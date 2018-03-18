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

/*
	Header file : f_board.h
	C file		: f_board.c

	Prototipos de sub-rutinas
*/

#if !defined _H_F_BOARD_
#define _H_F_BOARD_

#include <gtk/gtk.h>

#define F_BOARD_STACK_MAX_TOP	2

/* ================================================================================
	PROCEDIMIENTOS
   ================================================================================*/

//	@SUB-RUTINA 	:	f_board_stack_push(GtkWidget *);
//	@UTILIDAD		:	Permite agregar elementos del tipo de dato (GtkWidget *),
//						a una pila circular local, esta es usada para almacenar las
//						direcciones de los widget's de los contenedores de las
//						fichas seleccionadas por el usuario, esta son de clase (GtkEventBox) que 
//						estan en la interfaz grafica, los cuales pueden tener
//						o no hijos (las fichas del juego (GtkLabel)).
//	@RETORNO		:	Ninguno.
void f_board_stack_push(GtkWidget *widget);

/* ================================================================================
	FUNCIONES
   ================================================================================*/

//	@SUB-RUTINA 	:	f_board_stack_pop();
//	@UTILIDAD		:	Obtener de la pila local la direccion del contenedor (GtkEventBox *),
//						en el cual se encuentra una ficha del juego (GtkLabel *). 
//	@RETORNO		:	Dirección del widget contenedor (GtkEventBox *), el cual
//						tiene como hijo una ficha del juego (GtkLabel *). 	
GtkWidget *f_board_stack_pop(void);

// 	@SUBRUTINA 		:	f_board_stack_top()
//	@UTILIDAD		:	Obtener el número de elementos de la pila circular local.
//	@RETORNO		:	Tope actual de la pila circular.
unsigned short int f_board_stack_top(void);

// @SUB-RUTINA 	:	f_board_check_move(unsigned short int , unsigned short int )
// @UTILIDAD	:	verificar a partir de la posición base y la nueva posición
//					de una ficha a ser movida, si el movimiento es válido.
// @PARAMETROS	:	base_id		> posición actual de la ficha.
//					target_id	> nueva posición de la ficha.
//					player 		> jugador a verificar.
// @RETORNO		:	TRUE		> la nueva posición es válida.
//					FALSE		> la nueva posición no es válida.
gboolean f_board_check_move(unsigned short int player, unsigned short int base_id, unsigned short int target_id);

#endif // _H_F_BOARD_