#include <stdio.h>
#include <stdlib.h>
#include "reglas_movimiento.h"

#define true 1
#define false 0
#define INFINITO 99999

void movComplejos(int x, int y, int pInicialX, int pInicialY, Tablero tab, ConjuntoMovimientos conj);

void insertaMovSimple(int xInicial, int yInicial, int xFinal, int yFinal, ConjuntoMovimientos conj, Tablero tabInicial)
{
    if(tableroLeerPosicion(tabInicial, xFinal, yFinal) == NONE)
    {
        Tablero aux = tableroModificar(tabInicial, xInicial, yInicial, xFinal, yFinal, -1, -1);   //NO EXISTE FICHA PARA SER BORRADA
        Tablero temp = insertaMovimientoConjunto(xInicial, yInicial, xFinal, yFinal, aux, conj);
        if(temp != NULL){
            liberarTablero(temp);
        }
    }
}

void movSimples(int x, int y, Tablero tab, ConjuntoMovimientos conj)
{

    int posicionPar = (x*5+y)%2 == 0;

    if(posicionPar)
    {
        if(x > 0 && y > 0)  insertaMovSimple(x, y, x - 1, y - 1, conj, tab);
        if(x > 0 && y < 4)  insertaMovSimple(x, y, x - 1, y + 1, conj, tab);
        if(x < 4 && y > 0)  insertaMovSimple(x, y, x + 1, y - 1, conj, tab);
        if(x < 4 && y < 4)  insertaMovSimple(x, y, x + 1, y + 1, conj, tab);
    }

    if(x > 0)   insertaMovSimple(x, y, x - 1, y, conj, tab);
    if(y > 0)   insertaMovSimple(x, y, x, y - 1, conj, tab);
    if(x < 4)   insertaMovSimple(x, y, x + 1, y, conj, tab);
    if(y < 4)   insertaMovSimple(x, y, x, y + 1, conj, tab);

}


void insertaMovComplejo(int xInicial, int yInicial, int xMitad, int yMitad, int xFinal, int yFinal, ConjuntoMovimientos conj, Tablero tabInicial, int pInicialX, int pInicialY)
{
    int esPosible =  tableroLeerPosicion(tabInicial, xMitad, yMitad) == tableroTurnoContrario(tabInicial) && tableroLeerPosicion(tabInicial, xFinal, yFinal) == NONE &&
                     !(xFinal == pInicialX && yFinal == pInicialY);      //Vemos si el movimiento es posible para ello debe haber un patron tipo FICHA_EQUIPO1 FICHA_EQUIPO2 NONE

    if(esPosible)
    {
        Tablero nuevo = tableroModificar(tabInicial, xInicial, yInicial, xFinal, yFinal, xMitad, yMitad);
        Tablero temp = insertaMovimientoConjunto(pInicialX, pInicialY, xFinal, yFinal, nuevo, conj);
        tableroCambiarTurno(nuevo);
        movComplejos(xFinal, yFinal, pInicialX, pInicialY, nuevo, conj);

        if(temp != NULL){
           liberarTablero(temp);
        }

        if(temp != nuevo)
            tableroCambiarTurno(nuevo);
    }


}

void movComplejos(int x, int y, int pInicialX, int pInicialY, Tablero tab, ConjuntoMovimientos conj)
{

    int posicionPar = (x*5+y)%2 == 0;

    if(posicionPar)
    {
        if(x > 1 && y > 1)  insertaMovComplejo(x, y, x-1, y-1, x-2, y-2, conj, tab, pInicialX, pInicialY);
        if(x > 1 && y < 3)  insertaMovComplejo(x, y, x-1, y+1, x-2, y+2, conj, tab, pInicialX, pInicialY);
        if(x < 3 && y > 1)  insertaMovComplejo(x, y, x+1, y-1, x+2, y-2, conj, tab, pInicialX, pInicialY);
        if(x < 3 && y < 3)  insertaMovComplejo(x, y, x+1, y+1, x+2, y+2, conj, tab, pInicialX, pInicialY);
    }

    if(x > 1)  insertaMovComplejo(x, y, x-1, y, x-2, y,  conj, tab, pInicialX, pInicialY);
    if(y > 1)  insertaMovComplejo(x, y, x, y-1, x, y-2,  conj, tab, pInicialX, pInicialY);
    if(x < 3)  insertaMovComplejo(x, y, x+1, y, x+2, y,  conj, tab, pInicialX, pInicialY);
    if(y < 3)  insertaMovComplejo(x, y, x, y+1, x, y+2,  conj, tab, pInicialX, pInicialY);
}

void calcular_movimientos(int pos_ficha_x, int pos_ficha_y, Tablero tab, ConjuntoMovimientos conj)
{
    if( existeInsercionConjuntoMovimiento(pos_ficha_x, pos_ficha_y, conj) ) return ;
    movSimples(pos_ficha_x, pos_ficha_y, tab, conj);
    movComplejos(pos_ficha_x, pos_ficha_y, pos_ficha_x, pos_ficha_y, tab, conj);
}

int efectuarMovimientoJugador(int * xi, int * yi, int xf, int yf, ConjuntoMovimientos conj, Tablero * t)
{
    if( * xi == -1 || xf == -1)
    {
        return 0;
    }

    if(existeMovimientoConjunto(* xi, * yi, xf, yf, conj))
    {
        * t = extraerMovimientoConjunto(* xi, * yi, xf, yf, conj);
        vaciarConjunto(conj);
        * xi = -1;
        * yi = -1;
        return 1;
    }

    return 0;
}

void efectuarMovimientoBot(Tablero * t)
{

    ConjuntoMovimientos c = creaConjuntoMovimiento();
    Equipo turno = tableroLeerTurno(*t);
    Tablero mejorMov = NULL;
    int mejorPunt = INFINITO;
    int const profundidad = 6;
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 5; y++)
        {
            if(tableroLeerPosicion(*t, x, y) == turno)
            {
                calcular_movimientos(x, y, *t, c);
                Iterador_ConjuntoMovmientos it = creaIteradorCm(x, y, c);
                while(!(finIteradorCm(it)))
                {
                    int punt = minimax(profundidad, accedeTableroIteradorCm(it), false);

                    if(punt < mejorPunt)
                    {
                        mejorPunt = punt;
                        mejorMov = accedeTableroIteradorCm(it);
                    }
                    avanzaIteradorCm(it);
                }

                liberaIterador(it);
            }
        }
    }

    * t = tableroObtenerCopia(mejorMov);
    liberaConjuntoMovimiento(c);

}
