#include "minimax.h"
#define INFINITO 999999
#define true 1
#define false 0

int max(int a, int b)
{
    if(a > b) return a;
    return b;
}

int min(int a, int b)
{
    if(a > b) return b;
    return a;
}

int minimax_aux(int profundidad, Tablero tab, int esMax, int alpha, int beta)
{

    if(profundidad <= 0 || tableroConsultaGanador(tab) != NONE)
    {
        return tableroLeerPuntuacion(tab);
    }

    Equipo turno = tableroLeerTurno(tab);
    ConjuntoMovimientos c = creaConjuntoMovimiento();

    if(esMax)
    {
        int mejor = -INFINITO;
        for(int x = 0; x < 5; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                if(turno == tableroLeerPosicion(tab, x, y))
                {
                    calcular_movimientos(x, y, tab, c);
                    Iterador_ConjuntoMovmientos it = creaIteradorCm(x, y, c);
                    while(!(finIteradorCm(it)))
                    {
                        int valor = minimax_aux(profundidad-1, accedeTableroIteradorCm(it), false, alpha, beta);      //ACCEDE AL CONJUNTO DIRECTAMENTE
                        mejor = max(valor, mejor);
                        alpha = max(alpha, mejor);

                        if(beta <= alpha)
                        {
                            break;
                        }

                        avanzaIteradorCm(it);
                    }
                    liberaIterador(it);

                }
            }
        }
        liberaConjuntoMovimiento(c);
        return mejor;
    }

    else
    {
        int mejor = INFINITO;
        for(int x = 0; x < 5; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                if(turno == tableroLeerPosicion(tab, x, y))
                {
                    calcular_movimientos(x, y, tab, c);
                    Iterador_ConjuntoMovmientos it = creaIteradorCm(x, y, c);
                    while(!(finIteradorCm(it)))
                    {
                        int valor = minimax_aux(profundidad-1, accedeTableroIteradorCm(it), true, alpha, beta);      //ACCEDE AL CONJUNTO DIRECTAMENTE
                        mejor = min(mejor, valor);
                        beta = min(mejor, beta);
                        if(beta <= alpha)
                        {
                            break;
                        }
                        avanzaIteradorCm(it);
                    }
                    liberaIterador(it);

                }
            }
        }

        liberaConjuntoMovimiento(c);
        return mejor;
    }

    return -1;
}


int minimax(int profundidad, Tablero tab, int esMax)
{

    return minimax_aux(profundidad, tab, esMax, -INFINITO, INFINITO);

}




