
/**
* @file minimax.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Modulo que ofrece la posiblidad de usar el algoritmo de minimax sobre un Tablero @see Tablero 
*/


#ifndef __MINIMAX__H__
#define __MINIMAX__H__
#include "tablero.h"
#include "conjunto_movimientos.h"
#include "reglas_movimiento.h"

/**
 * @brief Ejecuta el algoritmo minimax sobre el Tablero tab con una profundidad determinado. esMax indica si se esta "Maximizando" la puntuacion.
 * Para ofrecer el mejor movimiento al equipo cuyo turno es el actual, esMax debe ser 1
 * En caso contrario debe ser 0
 * @param profundidad Indica la profundidad que se desea explorar. Atencion: tiene complejidad exponencial. Valores muy altos provocan inestablidad.
 * @param tab Tablero sobre el que se ejecuta el algoritmo
 * @param esMax entero usado como valor booleano que indica si se maximiza la puntuacion del turno actual (1, maximiza, 0 no maximiza).
 * @return int 
 */

int minimax(int profundidad, Tablero tab, int esMax);

#endif
