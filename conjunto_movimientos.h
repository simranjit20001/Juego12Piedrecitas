/**
* @file conjunto_movimientos.h
* @Author Simranjit Singh
* @date 07/01/2022
 * @brief Conjunto de movimientos.
 *   <p>Se trata de un conjunto de movimientos. Por lo que es necesario remarcar que es un movimiento:</p>
 *   <p><strong>Que es un movimiento</strong></p>
 *   <p>Un movimiento esta compuesto por:</p>
 *   <ol type="1">
 *   <li style="text-align: center;">Una casilla de origen. La casilla viene definida por coordenadas [x,y]</li>
 *   <li style="text-align: center;">Una casilla de destino. &nbsp;La casilla viene definida por coordenadas [x,y]</li>
 *   <li style="text-align: center;">Un Tablero. Se trata del tablero que "se queda" definido tras realizar el movimiento</li>
 *   </ol>
 * <p>La prioridad de este TDA es ofrecer velocidad.
 * <p>Por esa misma razon hay un "tradeoff" con  la memoria y se debe tener cuidado si se pretenden usar rangos muy amplios @see TAM_MAX_COORDENADA </p>
 * <p>La memoria utilizada es: (k*TAM_MAX_COORDENADA)^2</p>
*/


#ifndef	__conjunto_movimiento_H__
#define	__conjunto_movimiento_H__
#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Establecer el rango de coordenada sobre las que operara el conjunto de movimiento. El rango esta compuesto por el intervalo [0, TAM_MAX_COORDENADA)
 * @see ConjuntoMovimientos
 */

#define TAM_MAX_COORDENADA 5

/**
 * @brief Conjunto de movimientos.
 *   <p>Se trata de un conjunto de movimientos. Por lo que es necesario remarcar que es un movimiento:</p>
 *   <p><strong>Que es un movimiento</strong></p>
 *   <p>Un movimiento esta compuesto por:</p>
 *   <ol type="1">
 *   <li style="text-align: center;">Una casilla de origen. La casilla viene definida por coordenadas [x,y]</li>
 *   <li style="text-align: center;">Una casilla de destino. &nbsp;La casilla viene definida por coordenadas [x,y]</li>
 *   <li style="text-align: center;">Un Tablero. Se trata del tablero que "se queda" definido tras realizar el movimiento</li>
 *   </ol>
 *   <p>ConjuntoMovimientos es un TDA que actua como una colecion de movimentos</p>
 * @see Tablero
 */

typedef struct ConjuntoRep * ConjuntoMovimientos;

/**
 * @brief Se trata de un iterador del ConjuntoMovimientos. Tiene como objetivo de facilitar el recorrido o la iteracion de un ConjuntoMovimientos
 */

typedef struct Iterador * Iterador_ConjuntoMovmientos;

/**
 * @brief Crea un conjunto de movimientos nuevo, y vacio.
 * @return un ConjuntoMovimientos vacio
 */

ConjuntoMovimientos creaConjuntoMovimiento();


/**
 * @brief Inserta un movimiento en un conjunto de movimientos
 * Si el conjunto ya contine un movimiento definido por las mismas casillas de inicio y destino, entonces el conjunto mantendra el movimiento con mejor puntuacion sobre el tablero [para turno del Tablero t]
 * y expulsara el movimiento con peor resultado.
 * NULL indica que ningun tablero fue expulsado.
 * @pre Los valores de las coordenadas deben de pertecer al rango [0, TAM_MAX_COORDENADA]
 * @param inicio_x Coordenada x de la casilla inicial
 * @param inicio_y Coordenada y de la casilla inicial
 * @param ultimo_x Coordenada x de la casilla de destino
 * @param ultimo_y Coordenada y de la casilla de destino
 * @param t Tablero que definido tras realizar el movimiento en cuestion.
 * @param conjunto Conjunto al que se desea insertar el movimiento
 * @return Tablero expulsado del conjunto, en su caso. En caso contrario NULL.
 */


Tablero insertaMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, Tablero t, ConjuntoMovimientos conjunto);


/**
 * @brief Elimina un movimiento en un conjunto de movimientos.
 * No libera la memoria asociada al tablero de dicho movimiento, en su caso.
 * @pre Los valores de las coordenadas deben de pertecer al rango [0, TAM_MAX_COORDENADA]
 * @param inicio_x Coordenada x de la casilla inicial
 * @param inicio_y Coordenada y de la casilla inicial
 * @param ultimo_x Coordenada x de la casilla de destino
 * @param ultimo_y Coordenada y de la casilla de destino
 * @param conjunto Conjunto en el que se desea eliminar el movimiento
 *
 */


void eliminaMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, ConjuntoMovimientos conjunto);

/**
 * @brief Indica si el movimiento desde una casilla inicial a una casilla destino existe.
 * @pre Los valores de las coordenadas deben de pertecer al rango [0, TAM_MAX_COORDENADA]
 * @param inicio_x Coordenada x de la casilla inicial
 * @param inicio_y Coordenada y de la casilla inicial
 * @param ultimo_x Coordenada x de la casilla de destino
 * @param ultimo_y Coordenada y de la casilla de destino
 * @param conjunto Conjunto en el que se busca el movimiento
 * @return Entero que indica si existe el movimiento con un valor igual a 1, y la ausencia de movimiento con un 0.
 *
 */


int  existeMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, ConjuntoMovimientos conjunto);

/**
 * @brief Extrae, si existe, el tablero asociado al movimiento buscado.
 * @pre Los valores de las coordenadas deben de pertecer al rango [0, TAM_MAX_COORDENADA]
 * Un retorno NULL indica que el movimiento buscado no existe.
 * @param inicio_x Coordenada x de la casilla inicial
 * @param inicio_y Coordenada y de la casilla inicial
 * @param ultimo_x Coordenada x de la casilla de destino
 * @param ultimo_y Coordenada y de la casilla de destino
 * @param conjunto Conjunto en el que se busca extraer el movimiento
 * @return Tablero asociado al movimiento, si existe. NULL, en caso contrario.
 *
 */

Tablero extraerMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, ConjuntoMovimientos conjunto);


/**
 * @brief Indica si existe un movimiento desde una casilla inicial [x,y] a una casilla destino cualequiera
 * @pre Los valores de las coordenadas deben de pertecer al rango [0, TAM_MAX_COORDENADA]
 * @param x Coordenada x de la casilla inicial
 * @param y Coordenada y de la casilla inicial
 * @param c Conjunto sobre el que se opera
 * @return Entero, con un valor igual a 1 si existe un movimiento desde una casilla inicial [x,y] a una casilla destino cualequiera, o 0 en caso contrario.
 */


int existeInsercionConjuntoMovimiento(int x, int y, ConjuntoMovimientos c);



/**
 * @brief Vacial el conjunto. Libera la memoria asociada al Tablero.
 * Para impedir librar la memoria asociada al tablero se deben eliminar todos los movimientos
 * individualmente @see eliminaMovimientoConjunto()
 * @param conjunto Conjunto sobre el que se opera
 */

void vaciarConjunto(ConjuntoMovimientos conjunto);

/**
 * @brief Libera el conjunto. Tambien libera la memoria asociada al Tablero.
 * Para impedir librar la memoria asociada al tablero se deben eliminar todos los movimientos
 * individualmente @see eliminaMovimientoConjunto()
 * @param conjunto Conjunto sobre el que se opera
 */

void liberaConjuntoMovimiento(ConjuntoMovimientos conjunto);

/**
 * @brief Crea un iterador asociado a un conjunto y una casilla inicial para facilitar su recorrido.
 * Recorre por lo tanto todos los movimientos desde una casilla que se encuentran insertados.
 * El Iterador queda invalido si se modifica el conjunto y se debe resetear @see reseteaIteradorCm().
 * @param conjunto Conjunto que se asocia al iterador
 * @param x Coordenada x de la casilla inicial
 * @param y Coordenada y de la casilla inicial
 * @return Un iterador nuevo asociado a la casilla [x,y] y conjunto indicado-
 */


Iterador_ConjuntoMovmientos creaIteradorCm(int x, int y,  ConjuntoMovimientos conjunto);

/**
 * @brief Indica si se ha alcanzado el final del recorrido. Una vez llegados a este punto no
 * se debe ni avanzar, ni acceder al contenido del iterador.
 * @param it Iterador sobre el que se opera
 */

int finIteradorCm(Iterador_ConjuntoMovmientos it);

/**
 * @brief Accede al Tablero del movimeinto apuntado por el iterador
 * @pre El iterador debe apuntar a un contenido valido, es decir no debe haber alcanzado su final, @see finIteradorCm
 *
 * @param it Iterador sobre el que se opera
 */

Tablero accedeTableroIteradorCm(Iterador_ConjuntoMovmientos it);

/**
 * @brief Accede a la coordenada x del movimeinto apuntado por el iterador
 * @pre El iterador debe apuntar a un contenido valido, es decir no debe haber alcanzado su final, @see finIteradorCm
 *
 * @param it Iterador sobre el que se opera
*/


int  accedeXIteradorCm(Iterador_ConjuntoMovmientos it);


/**
 * @brief Accede a la coordenada y del movimeinto apuntado por el iterador
 * @pre El iterador debe apuntar a un contenido valido, es decir no debe haber alcanzado su final, @see finIteradorCm
 *
 * @param it Iterador sobre el que se opera
 */



int  accedeYIteradorCm(Iterador_ConjuntoMovmientos it);

/**
 * @brief Avanza el iterador para que apunte al siguiente movimiento disponible
 * @pre No se debe avanzar si ya ha alcanzado su "final" @see finIteradorCm
 *
 * @param it Iterador sobre el que se opera
 */

void avanzaIteradorCm(Iterador_ConjuntoMovmientos it);

/**
 * @brief Resetea el iterador para que vuelva a apuntar a la primer movimiento disponible
 * @param it Iterador sobre el que se opera
 */


void reseteaIteradorCm(Iterador_ConjuntoMovmientos it);

/**
 * @brief Libera la memoria asociada al Iterador
 * @param it Iterador sobre el que se opera
 */


void liberaIterador(Iterador_ConjuntoMovmientos it);

#endif
