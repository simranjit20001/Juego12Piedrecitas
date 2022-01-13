/**
* @file reglas_movimiento.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Implementacion del modulo asociado al calculo de los movimientos
*/

#ifndef	__reglas_movimiento_H__
#define	__reglas_movimiento_H__

#include "tablero.h"
#include "conjunto_movimientos.h"
#include "minimax.h"

/**
 * @brief Calcula todos los movimientos posibles para la ficha [x,y] en el Tablero tab y los añade al Conjunto conj
 *
 * @param pos_ficha_x Entero que indica la posicion x de la ficha
 * @param pos_ficha_y Entero que indica la posicion y de la ficha
 * @param tab Tablero tab sobre el que se calculan las movimientos
 * @param conj Conjunto al que se añaden los movimientos posibles calculados
 */

void calcular_movimientos(int pos_ficha_x, int pos_ficha_y, Tablero tab, ConjuntoMovimientos conj);

/**
 * @brief Realiza el mejor movimiento posible que ha podido ser calculado mediante un algoritmo de forma automatica
 *
 * @param t Puntero al tablero sobre el que se desea realizar el movimiento. Se sutituye el tablero apuntado por un con el movimiento nuevo realizado.
 */


void efectuarMovimientoBot(Tablero *t);

/**
 * @brief Si es posible, realiza el moviemiento desde una casilla inicial [x,y] hasta una casilla final [x1,y1]
 *
 * @pre Los valores de las casillas deben ser validos, es decir sus coordenadas pertenecer al intervalo [0,4]. En el caso de la casilla inicial -1 indica que no se debe buscar dicho movimiento.
 *
 * @param xi Puntero a entero a la coordenada X de la casilla inicial. Si se realiza el movimiento, el entero apuntado sera modificado a un valor igual a -1.
 * @param yi Puntero a entero a la coordenada Y de la casilla inicial. Si se realiza el movimiento, el entero apuntado sera modificado a un valor igual a -1.
 * @param xf Entero a la coordenada X de la casilla destino.
 * @param yf Entero a la coordenada Y de la casilla destino.
 * @param conj Conjunto de movimiento sobre el que se realiza la busqueda para determinar si existe el movimiento
 * @param t Puntero al tablero sobre el que se desea realizar el movimiento. Se sutituye el tablero apuntado por un con el movimiento nuevo realizado, en su caso.
 * @return int
 */

int efectuarMovimientoJugador(int * xi, int * yi, int xf, int yf, ConjuntoMovimientos conj, Tablero * t);

#endif
