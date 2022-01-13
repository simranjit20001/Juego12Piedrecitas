#include "pizarra.h"
#include <stdlib.h>
#include <assert.h>

#define IMG_PIZARRA "imagenes/pizarra.bmp"
#define ANCHO 362
#define ALTO 587
#define MAX_LINEA 10
#define CAR_LINEA 20
#define INICIO_TEXTO_X 115
#define INICIO_TEXTO_Y 150

struct PizarraRep
{
    char texto[MAX_LINEA][CAR_LINEA+1];
    int x;
    int y;
};

Pizarra crearPizarra()
{
    Pizarra nuevo = malloc(sizeof(struct PizarraRep));

    for(int i = 0; i < MAX_LINEA; i++){
        nuevo -> texto[i][0] = '\0'; // texto = ""
        nuevo -> texto[i][CAR_LINEA] = '\0'; //Esto hace que si la cadena tiene más de 20 car, pare el recorrido en los "20" sin preocuparnos por mantener el caracter de fin en cada insercion

    }

    nuevo -> x = 0;
    nuevo -> y = 0;
    return nuevo;
}

void pizarraEstablecerPosicion(int x, int y, Pizarra p)
{
    assert(p != NULL);
    p -> x = x;
    p -> y = y;
}

void pizarraDibujar(Pizarra p)
{
    assert(p != NULL);
    Imagen img  =  Pantalla_ImagenLee(IMG_PIZARRA , 0);
    Pantalla_DibujaImagen(img, p->x, p->y, ANCHO, ALTO);
    Pantalla_ColorTrazo(0, 255, 0, 255);
    for(int i = 0; i < MAX_LINEA; i++){
        Pantalla_DibujaTexto(p->texto[i], INICIO_TEXTO_X, INICIO_TEXTO_Y+20*i);
    }

    Pantalla_ImagenLibera(img);
}

void pizarraMover(int x, int y, Pizarra p)
{
    assert(p != NULL);
    p -> x = p -> x + x;
    p -> y = p -> y + y;
}

void pizarraDesplazarDerecha(Pizarra p)
{
    assert(p != NULL);
    p -> x = p->x + 10;
}
void pizarraDesplazarIzquierda(Pizarra p)
{
    assert(p != NULL);
    p -> x = p->x - 10;
}
void pizarraDesplazarArriba(Pizarra p)
{
    assert(p != NULL);
    p -> y = p->y + 10;
}

void pizarraDesplazarAbajo(Pizarra p)
{
    assert(p != NULL);
    p -> y = p->y - 10;
}

void pizarraEscribirTexto(char * texto, Pizarra p, int linea)
{
    assert(p != NULL);
    for (int i = 0; texto[i] != 0 && i < CAR_LINEA; i++) {
        p -> texto[linea][i] = texto[i]; //Conseguimos no solo mantener el maximo de 20 car sino tambien "encapsular" el texto
    }
}
void pizarraBorrarTexto(Pizarra p)
{
    assert(p != NULL);
    for(int i = 0; i < MAX_LINEA; i++){
        p->texto[i][0] = '\0';
    }
}
void pizarraLiberar(Pizarra p)
{
    assert(p != NULL);
    free(p);
}

