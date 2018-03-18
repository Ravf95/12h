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

#if !defined _H_F_FICHAS_
#define _H_F_FICHAS_

#define F_FICHAS_N	12

// @SUB-RUTINA 	:	f_get_player_fichas(guint8 )
// @UTILIDAD	:	obtener el número de fichas colocadas
//					en el tablero del jugador indicado.
// @PARAMETROS	:	id > jugador.
// @RETORNO		:	número de fichas del jugador indicado.
guint16 f_get_player_fichas(guint8 id);

// @SUB-RUTINA 	:	f_get_player_fichas_robadas(guint8 )
// @UTILIDAD	:	obtener el número de fichas robadas
//					por el jugador indicado.
// @PARAMETROS	:	id > jugador.
// @RETORNO		:	número de fichas robadas.
guint16 f_get_player_fichas_robadas(guint8 id);

// @SUB-RUTINA 	:	f_fichas_enqueue(guint8 , guint8 )
// @UTILIDAD	:	cola circular, contiene las posiciones de las
// 					casillas (ID) que tienen fichas en el tablero de
//					un jugador determinado (PLAYER).
// @PARAMETROS	:	id 		> identificador de la casilla donde se encuentra la ficha.
//					player 	> jugador dueño de la ficha.
// @RETORNO		:	ninguno.
// @CREDITOS	:	Pedro González Ruiz (Autor del Algoritmo)
// 					website: http://www.pedrogonzalezruiz.net/colas/colas.html
void f_fichas_enqueue(guint8 id, guint8 player);

// @SUB-RUTINA 	:	f_fichas_dequeue(guint8 )
// @UTILIDAD	:	colar circular, retornar la posicion de la fichas
// 					de un determinado jugador la cual se encuentra
// 					en el tablero.
// @PARAMETROS	:	player 	> jugador dueño de la ficha.
// @RETORNO		:	valor en cola.
// @CREDITOS	:	Pedro González Ruiz (Autor del Algoritmo)
// 					website: http://www.pedrogonzalezruiz.net/colas/colas.html
gint8 f_fichas_dequeue(guint8 player);

// @SUB-RUTINA 	:	f_fichas_queue_remove_item(guint8 , guint8 )
// @UTILIDAD	:	remover una valor de la colar circular.
// @PARAMETROS	:	player 	> jugador dueño de la ficha.
//					id 		> identificador de la casilla donde se encuentra la ficha.
// @RETORNO		:	ninguno.
void f_fichas_queue_remove_item(guint8 player, guint8 id);

// @SUB-RUTINA 	:	f_fichas_player_mill_count(guint
// @UTILIDAD	:	contador de mill por cada jugador.
// @PARAMETROS	:	player > jugador que realizo mill.
// @RETORNO		:	ninguno.
void f_fichas_player_mill_count(guint8 player);

// @SUB-RUTINA 	:	f_fichas_player_get_mill_count(guint8)
// @UTILIDAD	:	retorna la cantidad de mills que realizo
//					un jugador determinado.
// @PARAMETROS	:	player 	> jugador a evaluar.
// @RETORNO		:	número de mills hechos.
guint8 f_fichas_player_get_mill_count(guint8 player);

#define FICHAS_MOV_NO_ADYACENTE(PLAYER)			(f_get_player_fichas(PLAYER) == 3)

#endif	// _H_F_FICHAS_