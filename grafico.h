/**
* @file grafico.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Modulo que sirve de intervalo entre la biblioteca "Pantalla.h" para realizar
* aquellas operaciones que son más complejas relacionadas con el procesamiento grafico para
* mejorar la legiblidad fundamentalmente.
* A todos efectos es una "ampliacion" del main para mejorar la claridad
* @pre la pantalla sobre la que se opera es de tamaño igual a 1280x720
*/


#ifndef __GRAFICO_H__
#define __GRAFICO_H__
#include <stdio.h>
#include <stdlib.h>
#include "tablero.h"
#include "Pantalla.h"
#include "conjunto_movimientos.h"

/**
 * @brief Tiene como finalidad mantener en los valores apuntados por x,y 
 * el valor de la ficha que ha sido pulsada por el usuario, en su caso.
 * -1 indica que no hay ninguna ficha pulsada
 * @param pulsado Puntero a entero usado como booleano que determina si ha habido una pulsacion (Click)
 * @param x Puntero a entero que almacenara el valor de la coordenada X de la ficha pulsada, en su caso, y -1 si no hubiera ninguna ficha pulsada 
 * @param y Puntero a entero que almacenara el valor de la coordenada Y de la ficha pulsada, en su caso, y -1 si no hubiera ninguna ficha pulsada
 */

void actualizaTeclaClickada(int * pulsado, int * x, int *y);

/**
 * @brief Tiene como finalidad mantener en los valores apuntados por xSelecionada, ySelecionada
 * el valor de la ficha selecionada por el usuario, en su caso.
 * -1 indica que no hay ninguna ficha selecionada
 * @param xClikada Entero que indica la coordenada X de la ficha pulsada, en su caso, y -1 si no hubiera ninguna ficha pulsada
 * @param yClikada Entero que indica la coordenada Y de la ficha pulsada, en su caso, y -1 si no hubiera ninguna ficha pulsada
 * @param xSelecionada Puntero a entero que almacenara el valor de la coordenada X de la ficha selecionada, en su caso, y -1 si no hay ninguna ficha selecionada
 * @param ySelecionada Puntero a entero que almacenara el valor de la coordenada Y de la ficha selecionada, en su caso, y -1 si no hay ninguna ficha selecionada
 * @param t Tablero sobre el que se desea saber si existe alguna ficha selecionada
 */

void actualizaFichaSelecionada(int xClikada, int yClikada, int * xSelecionada, int * ySelecionada, Tablero t);

/** 
 * @brief Dibuja los movimientos disponebles en el conjunto de movimientos 
 * 
 * @param fichaSelecionadaX entero que indica la coordenada X de la ficha selecionada, en su caso, y -1 si no hay ninguna ficha selecionada
 * @param fichaSelecionadaY entero que indica la coordenada Y de la ficha selecionada, en su caso, y -1 si no hay ninguna ficha selecionada
 * @param conjunto Conjunto de moviemientos que se usara para saber que moviemientos disponibles existen
 * 
 * 
 */

void dibujarPreMovimientos(int fichaSelecionadaX, int fichaSelecionadaY, ConjuntoMovimientos conjunto);

/**
 * @brief Dibuja la pagina de manual requerida 
 * @pre La pagina  de manual ha de ser valida y pertenecer al intervalo [0,10]
 * @param pos Entero que indica la pagina de manual a dibujar
 */


void dibujarManual(int pos);

/**
 * @brief Dibuja el boton asociado a visualizar el tablero anterior
 */

void dibujarBotonMuestraAnterior();

/**
 * @brief Determina si el raton se encuentra sobre el boton de "Muestra anterior" @see dibujarBotonMuestraAnterior()
 * @return Entero usado como valor booleano que indica con un 1 si el raton se encuentra sobre el boton de "Muestra anterior" y 0 en caso contrario.
 */

int ratonSobreMuestraAnterior();

/**
 * @brief Muestra la animacion asociada a la felicitacion al ganador de la partida
 * @param equipo Equipo ganador 
 */


void mostrarGanador(Equipo equipo);

#endif

