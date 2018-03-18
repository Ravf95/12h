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

#include <stdlib.h>
#include <limits.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include "w_vtable_black.h"
#include "w_board.h"
#include "callback_board.h"
#include "callback_vtable_black.h"
#include "f_mill.h"
#include "f_error.h"
#include "f_game.h"
#include "f_fichas.h"
#include "ia.h"

/* ================================================================================
	MACROS
   ================================================================================*/

#define T_VT_MAX_LVL					3
#define T_VT_ADV(X) 					((X == 0) ? 1 : 0)
#if !defined MAX
#define MAX(X, Y)						(((X) > (Y)) ? (X) : (Y))
#endif

/* ================================================================================
	TIPOS DE DATOS DEFINIDOS
   ================================================================================*/

typedef struct board board_t;
typedef struct node node_t;

struct board
{
	unsigned char casilla_id;
	unsigned char ficha_owner;
};

/*
	Estrucuta de cada nodo
	del árbol de juegos
*/

struct node
{
	node_t *left;				// child
	node_t *right;				// sibling
	unsigned char casilla_id;	// ficha agregada al tablero virtual
	unsigned char turno;		// turno al cual corresponde la jugada
	unsigned char n;			// número de fichas que contiene el tablero virtual
	board_t *vboard;			// tablero virtual
};

/* ================================================================================
	VARIABLES GLOBALES DEL ARCHIVO
   ================================================================================*/

static node_t *g_node;
static signed long long int g_bestvalue;
static node_t *g_bestvalue_node;
static guint8 g_ia_turno;
static guint8 g_vtable_widget_id;

/* ================================================================================
	SUB-RUTINAS LOCALES
   ================================================================================*/

static board_t* generar_tablero_actual(unsigned char *ptrn);
static void troot(unsigned char turno);
static void generar_arbol(node_t *parent, unsigned char turno, unsigned char lvl);
static board_t *new_vboard(node_t *node, unsigned char id, unsigned char player);
static gboolean casilla_unica_vboard(node_t *node, unsigned char casilla);
static gboolean vboard_check_mill(node_t *node, unsigned char turno);
static void ia_primera_jugada(void);
static void ia_colocar_ficha(void);

static void delele_lcrs_tree(node_t **node);
static void last_child(node_t ** );
static void last_sibling(node_t ** );

static signed long long int e(node_t *x, signed char lvl);
static signed long long int AB(node_t *x, signed char lvl, signed long long int LB, signed long long int D);

/* ================================================================================
	DEFINICION DE SUB-RUTINAS
   ================================================================================*/

// @SUB-RUTINA 	:	ia()
// @UTILIDAD	: 	establer el movimiento
//					actual de la inteligencia.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
void ia(void)
{
	if (f_game_get_jugadas() == 0)
	{
		ia_primera_jugada();
		return;
	}

	ia_colocar_ficha();
}

// @SUB-RUTINA 	:	ia_primera_jugada()
// @UTILIDAD	:	establecer el primer movimiento
//					de la inteligencia si está
//					comienza el juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
static void ia_primera_jugada(void)
{
	guint8 casilla_id;
	casilla_id = rand() % 24;
	g_vtable_widget_id = 0;

	callback_vtable_black(w_vtable_black_get_parent(g_vtable_widget_id), NULL, GUINT_TO_POINTER(g_vtable_widget_id));
	callback_board(w_board_get_parent(casilla_id), NULL, GUINT_TO_POINTER(casilla_id));
	g_vtable_widget_id++;
}

// @SUB-RUTINA 	:	ia_colocar_ficha()
// @UTILIDAD	:	establecer el movimiento
//					de la inteligencia en la fase de
//					colocación de fichas del juego a partir
//					de un árbol de juego.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	ninguno.
static void ia_colocar_ficha(void)
{
	guint8 casilla_id;
	guint8 turno;

	g_bestvalue = 0;
	turno = f_game_get_turno();

	troot(T_VT_ADV(turno));
	generar_arbol(g_node, T_VT_ADV(turno), 0);
	AB(g_node, T_VT_MAX_LVL, LLONG_MIN, LLONG_MAX);
	casilla_id = g_node->casilla_id;
	delele_lcrs_tree(&g_node);

	callback_vtable_black(w_vtable_black_get_parent(g_vtable_widget_id), NULL, GUINT_TO_POINTER(g_vtable_widget_id));
	callback_board(w_board_get_parent(casilla_id), NULL, GUINT_TO_POINTER(casilla_id));
	g_vtable_widget_id++;
}

// @SUB-RUTINA 	:	ia_set_turno(guint 8)
// @UTILIDAD	:	asignar el orden de jugada
// 					a la ia en el juego.
// @PARAMETROS	:	0/1
// @RETORNO		:	ninguno
void ia_set_turno(guint8 turno)
{
	g_ia_turno = turno;
}

// @SUB-RUTINA 	:	ia_get_turno()
// @UTILIDAD	:	obtener el orden de jugada
//					de la ia.
// @PARAMETROS	:	ninguno.
// @RETORNO		:	el turno.
guint8 ia_get_turno(void)
{
	return g_ia_turno;
}

// @SUB-RUTINA 	:	casilla_unica_vboard(node_t *, unsigned char )
// @UTILIDAD	:	verificar si una determinada casilla
//					del vboard esta o no disponible.
// @PARAMETROS	:	node 	->	nodo que contiene el vboard.
//					id 		-> casilla
// @RETORNO		:	TRUE	-> esta disponible
//					FALSE	-> no esta disponible.
static gboolean casilla_unica_vboard(node_t *node, unsigned char id)
{
	unsigned char i;

	for (i = 0; i < node->n; i++)
		if (id == node->vboard[i].casilla_id)
			return FALSE;

	return TRUE;
}

// @SUB-RUTINA 	:	vboard_check_mill(node_t *, unsigned char )
// @UTILIDAD	:	verificar si alguna ficha del vboard esta
//					formanado o no un mill.
// @PARAMETROS	:	node 	-> nodo que contiene el vboard.
//					turno 	-> id del jugador a verificar.
// @RETORNO		:	TRUE 	-> se formo mill.
//					FALSE	-> no se formo mill.
static gboolean vboard_check_mill(node_t *node, unsigned char turno)
{
	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char l;
	unsigned char id;
	unsigned char count;

	id = node->casilla_id;

	for (i = 0, count = 0; i < f_mill_valid_mchk_col(id, i); i++, count = 0)
	{
		for (j = 0; j < 3; j++)
		{
			k = f_mill_get_mchk_value(id, i, j);

			for (l = 0; l < node->n; l++)
				if (k == node->vboard[l].casilla_id)
					if (node->vboard[l].ficha_owner == turno)
					{
						count++;
						break;
					}
		}

		if (count == 3)
			return TRUE;
	}

	return FALSE;
}

// @SUB-RUTINA 	:	generar_tablero_actual(unsigned char *)
// @UTILIDAD	:	generar un vboard con la fichas
//					que estan en el tablero actual.
// @PARAMETROS	:	ptrn 	-> 	dirección de la variable que almacena la
//								cantidad de fichas del vboard.
// @RETORNO		:	tablero virtual.
static board_t* generar_tablero_actual(unsigned char *ptrn)
{
	board_t *vboard;
	unsigned char i;
	unsigned char j;
	unsigned char n;
	unsigned char max;
	unsigned char temp;
	unsigned char player;

	for (i = 0, n = 0; i < 2; i++)
		n += f_get_player_fichas(i);

	vboard = (board_t *) malloc(sizeof(board_t) * n);
	F_ERROR_LOG_CHECK_PTR(vboard);

	for (player = 0, j = 0; player < 2; player++)
	{
		max = f_get_player_fichas(player);

		for (i = 0; i < max; i++, j++)
		{
			temp = f_fichas_dequeue(player);
			vboard[j].casilla_id = temp;
			vboard[j].ficha_owner = player;
			f_fichas_enqueue(temp, player);
		}
	}

	*ptrn = n;
	return vboard;
}

// @SUB-RUTINA 	:	troot(unsigned char )
// @UTILIDAD	:	crear el nodo raíz
//					del árbol de juegos a partir
//					del turno actual.
// @PARAMETROS	:	turno 	->	id del jugador.
// @RETORNO		:	ninguno.
static void troot(unsigned char turno)
{
	board_t *vboard;
	unsigned char total;

	g_node = (node_t *) malloc(sizeof(node_t));
	F_ERROR_LOG_CHECK_PTR(g_node);

	vboard = generar_tablero_actual(&total);

	g_node->left 		= NULL;
	g_node->right 		= NULL;
	g_node->casilla_id 	= UCHAR_MAX;
	g_node->turno 		= turno;
	g_node->n 			= total;
	g_node->vboard 		= vboard;
}

// @SUB-RUTINA 	:	generar_arbol(node_t *, unsigned char , unsigned char )
// @UTILIDAD	:	generar los nodos hijos o hermanos del árbol de juegos
//					de forma recursiva, un nuevo nivel del árbol corresponde
//					a una jugada del jugador actual o el adversario esto varia
//					según el cambio de turno en la función, los nodos hijos
//					pueden tener hermanos que representan las posibilidades
//					de colocar una ficha en varios lugares.
// @PARAMETROS	:	parent 	-> padre del nodo a crear.
//					turno  	-> turno a evaluar.
//					lvl 	-> nivel actual del árbol.
// @RETORNO		: 	ninguno.
static void generar_arbol(node_t *parent, unsigned char turno, unsigned char lvl)
{
	node_t *node;
	node_t *sibling;
	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char id;
	unsigned char owner;
	unsigned char casilla;

	if (lvl >= T_VT_MAX_LVL)
		return;

	if (lvl > ( 12 - f_get_player_fichas(T_VT_ADV(turno))) )
		return;

	for (i = 0; i < parent->n; i++)
	{
		owner = parent->vboard[i].ficha_owner;

		if (owner != turno)
			continue;

		id = parent->vboard[i].casilla_id;

		for (j = 0; f_mill_valid_mchk_col(id, j); j++)
		{
			for (k = 0; k < 3; k++)
			{
				casilla = f_mill_get_mchk_value(id, j, k);

				if (!casilla_unica_vboard(parent, casilla))
					continue;

				if (vboard_check_mill(parent, turno))
					continue;

				node = (node_t *) malloc(sizeof(node_t));
				F_ERROR_LOG_CHECK_PTR(node);

				node->right 		= NULL;
				node->left 			= NULL;
				node->casilla_id 	= casilla;
				node->n 			= parent->n + 1;
				node->turno 		= T_VT_ADV(turno);
				node->vboard 		= new_vboard(parent, node->casilla_id, node->turno);

				if (parent->left)
				{
					sibling = parent->left;

					while (sibling->right)
						sibling = sibling->right;

					sibling->right = node;
				}
				else
					parent->left = node;

				generar_arbol(node, T_VT_ADV(turno), lvl + 1);
			}
		}
	}
}

// @SUB-RUTINA 	:	new_vboard(node_t *, unsigned char , unsigned char )
// @UTILIDAD	:	genera el vboard a partir de un nodo y casilla determinada.
// @PARAMETROS	:	nodo 	->	nodo que contiene los datos para un nuevo vboard.
//					id 		-> 	casilla a representar en el vboard.
//					player 	-> 	turno actual.
// @RETORNO		:	vboard.
static board_t *new_vboard(node_t *node, unsigned char id, unsigned char player)
{
	board_t *board;
	unsigned char i;
	unsigned char n;

	n = node->n;
	board = (board_t *) malloc(sizeof(board_t) * (n + 1));
	F_ERROR_LOG_CHECK_PTR(board);

	for (i = 0; i < n; i++)
		board[i] = node->vboard[i];

	board[n].casilla_id = id;
	board[n].ficha_owner = player;

	return board;
}

// @SUB-RUTINA 	:	delele_lcrs_tree(node_t **)
// @UTILIDAD	:	elimina la raíz de un árbol
//					left child right sibling y todos
//					los nodos conectados.
// @PARAMETROS	:	node 	-> direccíon de la varible que
//								apunta al nodo raíz.
// @RETORNO		:	ninguno.
static void delele_lcrs_tree(node_t **node)
{
	if (!(*node))
		return;

	last_child(&(*node)->left);

	free((*node)->vboard);
	free((*node));
	*node = NULL;
}

static void last_child(node_t **node)
{
	if (!(*node))
		return;

	last_child(&(*node)->left);
	last_sibling(&(*node)->right);

	free((*node)->vboard);
	free((*node));
	*node = NULL;
}

static void last_sibling(node_t **node)
{
	if (!(*node))
		return;

	last_sibling(&(*node)->right);
	last_child(&(*node)->left);

	free((*node)->vboard);
	free((*node));
	*node = NULL;
}

// @SUB-RUTINA 	:	signed long long int e(node_t *, signed char )
// @UTILIDAD	:	funcíon de evaluación del árbol de juego.
// @PARAMETROS	:	x 	-> 	nodo a evaluar.
//					lvl -> nivel actual del árbol.
// @RETORNO		:	evaluación.
static signed long long int e(node_t *x, signed char lvl)
{
	signed char bonus;
	unsigned char enemy;
	unsigned char player;
	signed long long int result;

	result = 0;
	player = x->turno;
	enemy = T_VT_ADV(player);
	bonus = T_VT_MAX_LVL - lvl;

	if (vboard_check_mill(x, player))
		result += 63;

	if (vboard_check_mill(x, enemy))
		result -= 63;

	if (!vboard_check_mill(x, enemy))
		result += 20;

	result *= (1 * bonus);

	if (result > g_bestvalue)
	{
		g_node->casilla_id = x->casilla_id;
		g_bestvalue = result;
		g_bestvalue_node = x;
	}

	return result;
}

// @SUB-RUTINA 	:	AB(node_t *, signed char , signed long long int , signed long long int )
// @UTILIDAD	:	Buscar la mejor posición a partir de un árbol un árbol de juegos y una 
//					función de evaluación para colocar una ficha en el tablero actual del juego.
// @PARAMETROS	:	x 		-> 	nodo
//					lvl 	->	nivel del árbol de juegos.
//					LB 		-> 	valor máximo.
//					D 		-> valor mínimo.
// @RETORNO		:	evaluacíon de la mejor posición.
static signed long long int AB(node_t *x, signed char lvl, signed long long int LB, signed long long int D)
{
	if (x == NULL || lvl == 0)
		return e(x, lvl);

	node_t *ptr;
	signed long long int ans;
	ans = LB;

	for (ptr = x; ptr; ptr = ptr->right)
	{
		if (ptr->left)
			ans = MAX(ans, -AB(ptr->left, lvl - 1, -D, -ans));

		if (ans >= D)
			return ans;
	}

	return ans;
}

/* ================================================================================
	INDEFINICIÓN DE MACROS
   ================================================================================*/

#undef T_VT_MAX_LVL
#undef T_VT_ADV
#undef MAX
#if !defined MAX
#undef MAX
#endif