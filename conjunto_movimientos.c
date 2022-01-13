#include "conjunto_movimientos.h"
#include <assert.h>
#define true 1
#define false 0
#define TAM_CONJ TAM_MAX_COORDENADA*TAM_MAX_COORDENADA

struct ConjuntoRep
{
    Tablero posicion[TAM_CONJ][TAM_CONJ];
};

struct Iterador
{
    ConjuntoMovimientos conjunto;
    int inicio;
    int ultimo;
};

int conversorCoordenadas(int x, int y)
{
    return x*TAM_MAX_COORDENADA+y;
}

int reconvertirXCordenadas(int coordenada)
{
    return coordenada/TAM_MAX_COORDENADA;
}

int reconvertirYCordenadas(int coordenada)
{
    return coordenada%TAM_MAX_COORDENADA;
}

ConjuntoMovimientos creaConjuntoMovimiento()
{
    ConjuntoMovimientos nuevo = malloc(sizeof(struct ConjuntoRep));

    for(int i = 0; i < TAM_CONJ; i++)
    {
        for(int j = 0; j < TAM_CONJ; j++)
        {
            nuevo -> posicion[i][j] = NULL; //Inicialmente no hay movimientos disponibles; NULL indica ausencia de movimiento.
        }
    }

    return nuevo;
}


Tablero insertaMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, Tablero t, ConjuntoMovimientos conjunto)
{

    assert(inicio_x < TAM_MAX_COORDENADA);
    assert(inicio_y < TAM_MAX_COORDENADA);
    assert(ultimo_x < TAM_MAX_COORDENADA);
    assert(ultimo_y < TAM_MAX_COORDENADA);
    assert(conjunto != NULL);

    int inicio = conversorCoordenadas(inicio_x, inicio_y);
    int ultimo =  conversorCoordenadas(ultimo_x, ultimo_y);
    Tablero contenido = conjunto -> posicion[inicio][ultimo];
    if(contenido != NULL && contenido !=t)
    {
        if(tableroLeerPuntuacion(contenido) > tableroLeerPuntuacion(t) && tableroLeerTurno(t) == EquipoA)
        {
            return t;
        }
        else
        {
            conjunto -> posicion[inicio][ultimo] = t;
            return contenido;
        }
    }


    conjunto -> posicion[inicio][ultimo] = t;
    return NULL;
}

void eliminaMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, ConjuntoMovimientos conjunto)
{
    assert(inicio_x < TAM_MAX_COORDENADA);
    assert(inicio_y < TAM_MAX_COORDENADA);
    assert(ultimo_x < TAM_MAX_COORDENADA);
    assert(ultimo_y < TAM_MAX_COORDENADA);
    assert(conjunto != NULL);

    int inicio = conversorCoordenadas(inicio_x, inicio_y);
    int ultimo =  conversorCoordenadas(ultimo_x, ultimo_y);

    conjunto -> posicion[inicio][ultimo] = NULL;
}

int existeMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, ConjuntoMovimientos conjunto)
{
    assert(inicio_x < TAM_MAX_COORDENADA);
    assert(inicio_y < TAM_MAX_COORDENADA);
    assert(ultimo_x < TAM_MAX_COORDENADA);
    assert(ultimo_y < TAM_MAX_COORDENADA);
    assert(conjunto != NULL);

    int inicio = conversorCoordenadas(inicio_x, inicio_y);
    int ultimo =  conversorCoordenadas(ultimo_x, ultimo_y);
    return conjunto -> posicion[inicio][ultimo] != NULL;
}

Tablero extraerMovimientoConjunto(int inicio_x, int inicio_y, int ultimo_x, int ultimo_y, ConjuntoMovimientos conjunto)
{
    assert(inicio_x < TAM_MAX_COORDENADA);
    assert(inicio_y < TAM_MAX_COORDENADA);
    assert(ultimo_x < TAM_MAX_COORDENADA);
    assert(ultimo_y < TAM_MAX_COORDENADA);
    assert(conjunto != NULL);

    int inicio = conversorCoordenadas(inicio_x, inicio_y);
    int ultimo =  conversorCoordenadas(ultimo_x, ultimo_y);
    return tableroObtenerCopia(conjunto -> posicion[inicio][ultimo]);
}
void vaciarConjunto(ConjuntoMovimientos conjunto)
{
    assert(conjunto != NULL);
    Tablero tablero = NULL;

    for(int i = 0; i < TAM_MAX_COORDENADA*TAM_MAX_COORDENADA; i++)
    {
        for(int j = 0; j < TAM_MAX_COORDENADA*TAM_MAX_COORDENADA; j++)
        {
            tablero = conjunto->posicion[i][j];

            if(tablero != NULL)
            {
                liberarTablero(tablero);
            }

            conjunto -> posicion[i][j] = NULL;

        }
    }

}

int existeInsercionConjuntoMovimiento(int x, int y, ConjuntoMovimientos c)
{
    assert(c != NULL);
    assert(x < TAM_MAX_COORDENADA);
    assert(y < TAM_MAX_COORDENADA);

    int ficha = conversorCoordenadas(x, y);
    for(int i = 0; i < TAM_CONJ; i++)
    {
        if(c -> posicion[ficha][i] != NULL) return true;
    }
    return false;
}

void liberaConjuntoMovimiento(ConjuntoMovimientos conjunto)
{
    assert(conjunto != NULL);
    vaciarConjunto(conjunto);
    free(conjunto);
}

Iterador_ConjuntoMovmientos creaIteradorCm(int x, int y, ConjuntoMovimientos conjunto)
{
    assert(conjunto != NULL);
    assert(x < TAM_MAX_COORDENADA);
    assert(y < TAM_MAX_COORDENADA);

    Iterador_ConjuntoMovmientos it = malloc(sizeof(struct Iterador));
    it -> inicio = conversorCoordenadas(x,y);
    it -> ultimo = -1;
    it -> conjunto = conjunto;
    avanzaIteradorCm(it);
    return it;
}

int finIteradorCm(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);

    return it -> ultimo == TAM_CONJ;
}

Tablero accedeTableroIteradorCm(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);

    return it -> conjunto -> posicion[it -> inicio][it -> ultimo];
}

int  accedeXIteradorCm(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);
    return reconvertirXCordenadas(it -> ultimo);
}
int  accedeYIteradorCm(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);
    return reconvertirYCordenadas(it -> ultimo);
}

void avanzaIteradorCm(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);
    it -> ultimo = it -> ultimo + 1;
    while(it -> ultimo < TAM_CONJ && it -> conjunto -> posicion[it -> inicio][it -> ultimo] == NULL)
        it -> ultimo++;
}

void reseteaIteradorCm(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);
    it -> ultimo = -1;
    avanzaIteradorCm(it);
}

void liberaIterador(Iterador_ConjuntoMovmientos it)
{
    assert(it != NULL);
    free(it);
}

