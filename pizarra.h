/**
* @file pizarra.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Implementacion del TDA Pizarra
*/


#ifndef __pizarra_H
#define __pizarra_H
#include "stdio.h"
#include "Pantalla.h"


/**
 * @brief Representa al TDA Pila.
 */

typedef struct PizarraRep    *  Pizarra;

/**
 * @brief Crea una pizarra vacia.
 * Inicialmente su posicion es {0,0}
 * @return Una pizarra nueva vacia.
 */

Pizarra crearPizarra();

/**
 * @brief Establece la posicion de la pizarra
 * Sobrescribe cualquier valor relacionado con la posicion anterior
 *
 * @param x Entero que define la coordenada X de la posicion a establecer
 * @param y Entero que define la coordenada Y de la posicion a establecer
 * @param p Pizarra sobre la que se opera
 *
 */

void pizarraEstablecerPosicion(int x, int y, Pizarra p);

/**
 * @brief Dibuja la pizarra
 * @param p Pizarra sobre la que se opera
 */

void pizarraDibujar(Pizarra p);

/**
 * @brief Desplaza la pizzara horizontalmente y verticalmente sobre su posicion actual
 *
 * @param x Entero que define el desplazamiento horizontal
 * @param y Entero que define el desplazamiento vertical
 * @param p Pizarra sobre la que se opera
 *
 */

void pizarraMover(int x, int y, Pizarra p);


/**
 * @brief Escribe sobre la pizarra en la linea correspondiente.
 * Solo admite 20 caracteres por linea, en caso de que la cadena de texto
 * incluya más, se ignoran.
 * @pre La linea debe ser mayor o igual a 0, y menor a 10
 *
 * @param texto  Cadena de texto que se desea escibir
 * @param linea Entero que indica la linea sobre la que se desea escribir
 * @param p Pizarra sobre la que se opera
 *
 */


void pizarraEscribirTexto(char * texto, Pizarra p, int linea);

/**
 * @brief Borra todo el texto sobre la pizarra
 * @param p Pizarra sobre la que se opera
 */


void pizarraBorrarTexto(Pizarra p);

/**
 * @brief Desplaza la pizarra 10 coordenadas a la derecha
 * @param p Pizarra sobre la que se opera
 */

void pizarraDesplazarDerecha(Pizarra p);


/**
 * @brief Desplaza la pizarra 10 coordenadas a la izquierda
 * @param p Pizarra sobre la que se opera
 */


void pizarraDesplazarIzquierda(Pizarra p);


/**
 * @brief Desplaza la pizarra 10 coordenadas hacia arriba
 * @param p Pizarra sobre la que se opera
 */


void pizarraDesplazarArriba(Pizarra p);


/**
 * @brief Desplaza la pizarra 10 coordenadas hacia abajo
 * @param p Pizarra sobre la que se opera
 */


void pizarraDesplazarAbajo(Pizarra p);


/**
 * @brief Libera la pizarra
 * @param p Pizarra sobre la que se opera
 */


void pizarraLiberar(Pizarra p);

#endif
