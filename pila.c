#include "Pila.h"
#include <stdlib.h>
#include <assert.h>


struct Nodo
{
    Elemento dato;
    struct Nodo *sig;
};

typedef struct Nodo *NodoPtr;

struct PilaRep
{
    NodoPtr tope;
    int n;
};

Pila pilaCrea()
{
    Pila nueva = malloc(sizeof(struct PilaRep));
    nueva->tope = NULL;
    nueva->n = 0;
    return nueva;
}
void pilaLibera(Pila p)
{
    while (p->tope != NULL)
    {
        NodoPtr borrado = p->tope;
        p->tope = borrado->sig;
        free(borrado);
    }

    free(p);
}

void pilaInserta(Pila p, Elemento e)
{
    NodoPtr nuevo = malloc(sizeof(struct Nodo));
    nuevo->dato = e;
    nuevo->sig = p->tope;
    p->tope = nuevo;
    p->n = p->n + 1;
}

void pilaSuprime(Pila p)
{
    assert(p->tope != NULL);
    NodoPtr borrar = p->tope;
    p->tope = borrar->sig;
    free(borrar);
    p->n = p->n -1;
}

Elemento pilaRecupera(Pila p)
{
    assert(p->tope != NULL);
    return p->tope->dato;
}

Elemento pilaRecuperaAnterior(Pila p)
{
    assert(p->n > 1);
    return p->tope->sig->dato;
}
int pilaCantElem(Pila p)
{
    return p->n;
}
int pilaVacia(Pila p)
{
    return p->tope == NULL;
}
int pilaLlena(Pila p)
{
    return 0;
}
