/**
* @file pila.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Implementacion del TDA contenedor Pila
*/


#ifndef __pila_H__
#define __pila_H__

#include "tablero.h"

/**
 * @brief Establecer el tipo de Elemento sobre el que opera la Pila.
 */

typedef Tablero Elemento;

/**
 * @brief Representa al TDA Pila.
 */

typedef struct PilaRep * Pila;

/**
 * @brief Crea una pila vacia.
 * @return Una pila nueva vacia.
 */


Pila pilaCrea();


/**
 * @brief Libera la memoria asociada a la pila.
 * @param p Pila a liberar.
 */

void pilaLibera( Pila p );

/**
 * @brief Inserta un elemento en la pila.
 * @param p Pila en la que se quiere insertar un elemento.
 * @param e Elemento a insertar en la pila.
 */

void pilaInserta( Pila p, Elemento e );


/**
 * @brief Suprime el ultimo elemento insertado en la pila.
 * @pre La pila no puede estar vacia.
 * @param p Pila en la que se quiere suprimir el ultimo elemento insertado.
 */

void pilaSuprime( Pila p );

/**
 * @brief Devuelve el ultimo elemento insertado en la pila.
 * @pre La pila no puede estar vacia.
 * @param p Pila de la que se quiere obtner el ultimo elemento insertado.
 * @return El ultimo elemento insertado en la pila.
 */
Elemento pilaRecupera( Pila p );

/**
 * @brief Devuelve el penultimo [Anterior al ultimo] elemento insertado en la pila.
 * @pre La pila debe contener, al menos, 2 elementos.
 * @param p Pila de la que se quiere obtner el penultimo elemento insertado.
 * @return El penultimo elemento insertado en la pila.
 */


Elemento pilaRecuperaAnterior( Pila p );

/**
 * @brief Consulta si una pila esta vacia.
 * @param p Pila sobre la que se consulta si es vacia.
 * @return Entero, un 0 si no se encuentra vacia. Un 1 si se encuentra vacia.
 */

int pilaVacia( Pila p );

/**
 * @brief Consulta si una pila esta llena.
 * @param p Pila sobre la que se consulta si esta llena.
 * @return Entero, un 0 si no se encuentra llena. Un 1 si se encuentra llena.
 */

int pilaLlena( Pila p );

/**
 * @brief Consulta la cantidad de elementos que contiene la pila.
 * @param p Pila sobre la que se consulta la cantidad de elementos que contiene.
 * @return Entero igual a la cantidad de elementos que contiene la pila.
 */


int pilaCantElem(Pila p);
#endif

