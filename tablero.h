/**
* @file tablero.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Implementacion del TDA tablero
*/

#ifndef	__tablero_H__
#define	__tablero_H__

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "Pantalla.h"

/**
 * @brief Representacion del TDA Tablero.
 */

typedef struct TableroRep    *  Tablero;

/**
 * @brief Representacion de Equipo
 *  Existen dos Equipos: EquipoA y el EquipoB
 *  NONE indica NINGUN EQUIPO
 */

typedef enum Equipo {EquipoA, EquipoB, NONE} Equipo;

/**
 * @brief Crea un tablero en su estado inicial.
 *        Inicialmente sus casillas siguen la siguiente distribucion:
 *<ol>
 *          <li>EquipoA, EquipoA, EquipoA, EquipoA, EquipoA</li>
 *          <li>EquipoA, EquipoA, EquipoA, EquipoA, EquipoA</li>
 *          <li>EquipoA, EquipoA, NONE   , EquipoB, EquipoB</li>
 *          <li>EquipoB, EquipoB, EquipoB, EquipoB, EquipoB</li>
 *          <li>EquipoB, EquipoB, EquipoB, EquipoB, EquipoB</li>
 *</ol>
 * El EquipoA comienza el juego (turno del tablero -> EquipoA)
 *
 *  \return Un Tablero nuevo.
 */

Tablero crearTablero();

/**
 * @brief Sustrae y crea un tablero a partir de un tablero guardado con anterioridad.
 * El tablero debe haberse guardado en el fichero por la funcion tablero tableroGuardar(Tablero t, FILE * fp);
 * En cualquier caso si los datod del fichero apuntado no cumplen con el formato correcto, devulve NULL
 *
 *    @pre El fichero debe ser diferente de NULO, abierto en modo lectura.
 *    @param Puntero a un fichero abiertoen modo lectura, en el que anteriormente se guardo un Tablero
 *
 *    @return NULL, si no fue posible extraer el Tablero. Tablero extraido en caso contrario.
 *
 */



Tablero tableroExtraer(FILE * fp);

/**
 * @brief Indica el estado del Tablero (Si existe un Ganador). Devuelve, en caso de que exista, el EQUIPO ganador.
 *
 *    @param Un Tablero
 *
 *    @return Equipo ganador, si existe. NONE  en caso contrario.
 *
 */





Equipo tableroConsultaGanador(Tablero tab);

/**
 * @brief Consulta la posicion del Tablero y devuelve su estado actual (Que Equipo ocupa dicha posicion)
 *
 *    @param Tablero sobre el que se realiza la consulta
 *    @pre Los enteros en referencia a la posicion deben ser validos, es decir pertenecer al rango [0-5)
 *    @param Entero x: numero de posicion x sobre el que se hace la consulta
 *    @param Entero y: numero de posicion y sobre el que se hace la consulta
 *
 *    @return Equipo que ocupa dicha casilla, si existe. NONE  en caso contrario.
 *
 */




Equipo tableroLeerPosicion(Tablero tab, int x, int y);

/**
 * @brief Puntuacion del tablero
 * Indica en una escala de (-12, 12) la puntacion del tablero
 * Una puntuacion mayor de 0 indica ventaja para el EquipoA
 * Una puntuacion menor de 0 indica ventaja para el EquipoB
 * Una puntucion igual a 0 indica estado actual de Empate
 *  @pre Los valores asociados a las coordenas de la ficha deben ser validos [0-5) y no se comprobaran a la hora de la ejecucion ocasionando su uso incorrecto fallos inesperados
 *    @param Tablero sobre el que se realiza la consulta
 *
 *    @return Entero que indica la puntuacion del equipo
 *
 */


int tableroLeerPuntuacion(Tablero tab);

/**
 * @brief Consulta el turno actual del Tablero
 *
 *    @param Tablero sobre el que se realiza la consulta
 *
 *    @return Equipo del cual es el turno actual.
 *
 */


Equipo tableroLeerTurno(Tablero tab);


/**
 * @brief Dada dos coordenadas, seleciona si dichas coordenas estan sobre una ficha del tablero.
 *  Si se encuentran dentro establece el valor de los enteros apuntados por fx, fy, sobre la que se encuentran dichas coordenas.
 *  Si por ejemplo x,y estan sobre la ficha X=4, Y=2, se estableceria el valor de *fx = 4, *fy=2
 *  En caso contrario, se establece el valor de *fx = -1, *fy = -1 (LAS COORDENADAS NO ESTAN SOBRE NINGUNA FICHA)
 *
 *  @pre El calculo se realiza suponiendo que el tablero se encuentra dibujado en una pantalla estandar de dimensiones 1280x720 por la funcion tableroDibujar() de este TDA
 *  @pre Los valores asociados a las coordenas de la ficha deben ser validos [0-5) y no se comprobaran a la hora de la ejecucion ocasionando su uso incorrecto fallos inesperados
 *
 *  @param x Coordenada x
 *  @param x Coordenada y
 *  @param fx Puntero a un entero. Se almacenara en esta dirrecion la componente X de la ficha sobre la que se encuentran las coordenadas, o -1, si no ha sido posible encontrarla
 *  @param fy Puntero a un entero. Se almacenara en esta dirrecion la componente Y de la ficha sobre la que se encuentran las coordenadas, o -1, si no ha sido posible encontrarla
 *
 *
 */


void tableroFichaCoordenadas(double x, double y, int * fx, int * fy);


/**
 * @brief Dibuja la casilla pasada por parametro de un color especial indicando que se encuentra seleccionada
 *
 *  @pre Los valores asociados a las coordenas de la ficha deben ser validos [0-5) y no se comprobaran a la hora de la ejecucion ocasionando su uso incorrecto fallos inesperados
 *
 *  @param x Coordenada x de la ficha
 *  @param x Coordenada y de la ficha
 *
 */

void tableroDibujarFichaSeleccionada(int x, int y);


/**
 * @brief Dibuja la casilla de un color especial indicando que se encuentra disponible para realizar un movimiento que acaba en esta casilla
 *
 *  @pre Los valores asociados a las coordenas de la ficha deben ser validos [0-5) y no se comprobaran a la hora de la ejecucion ocasionando su uso incorrecto fallos inesperados
 *
 *  @param x Coordenada x de la casilla
 *  @param x Coordenada y de la casilla
 *
 */



void tableroDibujarPremov(int x, int y);



/**
 * @brief Cambia el turno del tablero pasado por parametro
 *
 *  @param tab Tablero del que se desea cambiar el turno
 *
 */





void tableroCambiarTurno(Tablero tab);



/**
 * @brief Devuelve un tablero nuevo con la modificacion deseada sobre el actual
 *
 *  Dado un tablero inicial, se pasan por parametro 3 posiciones
 *  1. (x, y) iniciales: indican la posicion de la ficha del tablero que se desea mover
 *  2. (x, y) finales: indican la posicion del tablero a la cual se desea mover la ficha anterior
 *  3. (x, y) [OPCIONAL: Indicar con -1 que no se desea usar] Ficha que se desea eliminar del tablero
 *
 *  @pre Los valores asociados a las coordenadas de la ficha deben ser validos [0-5) y no se comprobaran a la hora de la ejecucion ocasionando su uso incorrecto fallos inesperados
 *  @param tab_inicial Tablero a partir del cual se desea realizar la modificacion
 *  @param x_inicial posicion x de la ficha que se desea desplazar
 *  @param y_inidial posicion y de la ficha que se desea desplazar
 *  @param x_final posicion x de la casilla a la que se desea desplazar la ficha original
 *  @param y_final posicion y de la casilla a la que se desea desplazar la ficha original
 *  @param ficha_eliminar_x [OPCIONAL: Indicar con -1 que no sea usar]. Posicion x de la ficha a eliminar
 *  @param ficha_eliminar_y [OPCIONAL: Indicar con -1 que no sea usar]. Posicion y de la ficha a eliminar
 *
 *  @return Tablero nuevo con la modificacion anterior
 */

Tablero tableroModificar(Tablero tab_inicial, int x_inicial,
                         int y_inicial, int x_final, int y_final,
                         int ficha_eliminar_x, int ficha_eliminar_y);


/**
 * @brief Dibuja el tablero pasado en la pantalla usando la libreria "Pantalla.h".
 * @pre Se necesita la libreria "Pantalla.h"
 * @pre La pantalla sobre la que se dibuja es de 1280x720
 * @param t Tablero que se quiere dibujar en la Pantalla
 */


void tableroDibujar(Tablero t);



/**
 * @brief Guarda el tablero en un archivo de texto. Se puede recuperar por Tablero tableroExtraer(FILE * fp);
 *
 *
 *  @pre El fichero debe ser diferente de NULO, abierto en modo escritura.
 *
 *  @param t Tablero que se quiere guardar
 *  @param *fp Puntero al fichero en el que se quiere guardar el tablero t
 *
 */


void tableroGuardar(Tablero t, FILE * fp);





/**
 * @brief Libera la memoria asociada al TDA tablero
*
 *  @param tab_eliminar Tablero que se desea eliminar
 *
 */




void liberarTablero(Tablero tab_eliminar);



/**
 * @brief Devuelve un tablero nuevo que es una copia identica del tablero pasado por parametro
 *
 * @param tab_original Tablero que se desea copiar
 * @return Tablero nuevo que es una copia identica del tablero tab_original
 *
 */




Tablero tableroObtenerCopia(Tablero tab_original);



/**
 * @brief Devuelve el equipo contrario del equipo cuyo turno es en el tablero pasado por parametro
 *
 *  @param tab Tablero sobre el que se realiza la consulta
 *  @return Equipo contrario del equipo cuyo turno es en el tablero pasado por parametro
 */





Equipo tableroTurnoContrario(Tablero tab);

#endif
