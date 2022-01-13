#include "tablero.h"
#include <assert.h>



//RUTAS
#define IMG_TABLERO  "imagenes/tablero_sin_espacio.bmp"
#define IMG_F_ROJAS  "imagenes/fichas_rojas.bmp"
#define IMG_F_AZULES "imagenes/fichas_azules.bmp"
#define IMG_FICHA_VERDE "imagenes/ficha_selecionada.bmp"
#define IMG_FICHA_AMARILLO "imagenes/ficha_posibleMov.bmp"

//FIN RUTAS
//DEFINIMOS CONSTANTES ARIMETICAS
#define ANCHURA 600
#define LONGITUD 600

#define POS_X_C1 490
#define POS_Y_C1 40
#define RADIO    40

#define false 0
#define true  1

#define INDETERMINADO -1

typedef enum COLOR {AZUL, ROJO, VERDE, AMARILLO} COLOR;

struct TableroRep
{
    Equipo tablero[5][5];
    int turno;
    int cantFichasA;
    int cantFichasB;
};


Tablero crearTablero()
{

    Tablero nuevo = malloc(sizeof(struct TableroRep));

//INICIALIZAMOS LAS 12 PRIMERAS CASILLAS CON FICHAS DEL Equipo A
    for(int i = 0; i < 12; i++)
    {
        nuevo -> tablero[i/5][i%5] = EquipoA;
    }

    nuevo -> tablero[2][2] = NONE; //La casilla [2][2] se encuentra VACIA en el inicio

//INICIALIZAMOS LAS 12 ULTIMAs CASILLAS CON FICHAS DEL Equipo A
    for(int i = 13; i < 26; i++)
    {
        nuevo -> tablero[i/5][i%5] = EquipoB;
    }

    /*
    Representacion visual del array bidimensional que representa al tablero tras los anteriores for:

        {
            EquipoA, EquipoA, EquipoA, EquipoA, EquipoA,
            EquipoA, EquipoA, EquipoA, EquipoA, EquipoA,
            EquipoA, EquipoA, NONE   , EquipoB, EquipoB,
            EquipoB, EquipoB, EquipoB, EquipoB, EquipoB,
            EquipoB, EquipoB, EquipoB, EquipoB, EquipoB,
        };

    */
    nuevo -> turno = EquipoA;
    nuevo -> cantFichasA = 12;
    nuevo -> cantFichasB = 12;

    return nuevo;
}


Equipo tableroLeerPosicion(Tablero tab, int x, int y)
{
    assert(tab != NULL);
    return tab -> tablero[x][y];
}

int tableroLeerPuntuacion(Tablero tab)
{
    assert(tab != NULL);
    return tab -> cantFichasA - tab->cantFichasB;
}

Equipo tableroLeerTurno(Tablero tab)
{
    assert(tab != NULL);
    return tab -> turno;
}



Tablero tableroObtenerCopia(Tablero tab_original)
{
    assert(tab_original != NULL);
    Tablero nuevo = malloc(sizeof(struct TableroRep));

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            nuevo -> tablero[i][j] = tab_original ->tablero[i][j];
        }
    }

    nuevo -> cantFichasA = tab_original -> cantFichasA;
    nuevo -> cantFichasB = tab_original -> cantFichasB;
    nuevo -> turno      = tab_original -> turno;

    return nuevo;
}

void tableroCambiarTurno(Tablero tab)
{
    assert(tab != NULL);
    if(tab -> turno == EquipoA)
    {
        tab -> turno = EquipoB;
    }
    else
    {
        tab -> turno = EquipoA;
    }
}

Tablero tableroModificar(Tablero tab_inicial, int x_inicial, int y_inicial, int x_final, int y_final, int ficha_eliminar_x, int ficha_eliminar_y)
{
    assert(tab_inicial != NULL);

    //Dado de que se trata de un objeto inmutable debemos crear una copia del tablero original antes de modificarlo
    Tablero tab = tableroObtenerCopia(tab_inicial);
    tab -> tablero[x_final][y_final] = tab->tablero[x_inicial][y_inicial];         //movemos la ficha de la posicion original a la final
    tab -> tablero[x_inicial][y_inicial] = NONE;                                 //la posicion inicial queda libre

    if(ficha_eliminar_x != INDETERMINADO)
    {

        if(tab -> tablero[ficha_eliminar_x][ficha_eliminar_y] == EquipoA)
        {
            tab -> cantFichasA = tab -> cantFichasA - 1;
        }
        else
        {
            tab -> cantFichasB = tab -> cantFichasB - 1;
        }

        tab -> tablero[ficha_eliminar_x][ficha_eliminar_y] = NONE;
    }   //ficha_eliminar_x = INDETERMINADO indica que no hay que borrar ninguna ficha

    tableroCambiarTurno(tab);

    return tab;
}



void tableroDibujar(Tablero t)
{
    assert(t != NULL);

    Pantalla_DibujaRellenoFondo(255,255,255,255);

    Imagen img_tablero  =  Pantalla_ImagenLee(IMG_TABLERO , 0);
    Imagen img_f_rojas  =  Pantalla_ImagenLee(IMG_F_ROJAS , 0);
    Imagen img_f_azules =  Pantalla_ImagenLee(IMG_F_AZULES, 0);

    Pantalla_DibujaRellenoFondo(255,255,255,0);
    Pantalla_DibujaImagen(img_tablero, 500, 50, ANCHURA, LONGITUD );

    int valor_tablero = NONE;



    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
        {

            if(t != NULL) valor_tablero = tableroLeerPosicion(t, i, j);

            if(valor_tablero != NONE)
            {
                if( valor_tablero == EquipoA ) Pantalla_DibujaImagen(img_f_rojas , POS_X_C1+j*130, POS_Y_C1+i*130, 90, 90 );
                else                            Pantalla_DibujaImagen(img_f_azules, POS_X_C1+j*130, POS_Y_C1+i*130, 90, 90 );
            }
        }
    }



    Pantalla_ImagenLibera(img_tablero);
    Pantalla_ImagenLibera(img_f_rojas);
    Pantalla_ImagenLibera(img_f_azules);

}

void tableroFichaCoordenadas(double x, double y, int * fx, int * fy)   //int
{

    int noEncontrado = true;
    double distancia = 99999;


    for(int i = 0; i<5 && noEncontrado; i++)
    {
        for(int j = 0; j<5 && noEncontrado; j++)
        {

            double posFichaX = POS_X_C1 + 40 + j*130;
            double posFichaY = POS_Y_C1 + 40 + i*130;

            distancia = sqrt( (posFichaX-x)*(posFichaX-x) + (posFichaY-y)*(posFichaY-y));

            if(distancia < 61)
            {
                noEncontrado = false;
                *fx = i;
                *fy = j;
            }
        }
    }

    if(noEncontrado)
    {
        *fx=INDETERMINADO;
        *fy=INDETERMINADO;
    }
}

void dibujarFichaColor(int x, int y, COLOR color)
{
    Imagen img_ficha = NULL;

    switch(color)
    {
    case AMARILLO:
        img_ficha = Pantalla_ImagenLee(IMG_FICHA_AMARILLO, 0);
        break;
    default:
        img_ficha = Pantalla_ImagenLee(IMG_FICHA_VERDE, 0);
    }

    Pantalla_DibujaImagen(img_ficha, POS_X_C1+y*130, POS_Y_C1+x*130, 90, 90 );
    Pantalla_ImagenLibera(img_ficha);
}

void tableroDibujarFichaSeleccionada(int x, int y)
{
    dibujarFichaColor(x, y, VERDE);
}

void tableroDibujarPremov(int x, int y)
{
    dibujarFichaColor(x, y, AMARILLO);
}



void liberarTablero(Tablero tab_eliminar)
{
    assert(tab_eliminar != NULL);
    free(tab_eliminar);
}

Equipo tableroConsultaGanador(Tablero tab)
{
    if(tab -> cantFichasA == 0) return EquipoB;
    else if(tab -> cantFichasB == 0) return EquipoA;
    return NONE;
}

Equipo tableroTurnoContrario(Tablero tab)
{
    assert(tab != NULL);
    if(tableroLeerTurno(tab) == EquipoA) return EquipoB;
    return EquipoA;

}


void tableroGuardar(Tablero t, FILE * fp)
{
    assert(t != NULL);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            fprintf(	fp,	"%d ", t->tablero[i][j] 	);
        }
    }

    fprintf(	fp,	"%d\n", t->turno	);

}

Tablero tableroExtraer(FILE	*	fp)
{
    assert(fp != NULL);

    Tablero nuevo = malloc(sizeof(struct TableroRep));
    int i = 0;
    int lecturaCorrecta = true;
    int dato;

    while(lecturaCorrecta)
    {
        lecturaCorrecta = !feof(fp) && i < 25 && fscanf(fp, "%d ", &dato ) == 1;
        nuevo -> tablero[i/5][i%5] = dato;

        if(dato == EquipoA)
        {
            nuevo -> cantFichasA = nuevo -> cantFichasA + 1;
        }
        else if(dato == EquipoB)
        {
            nuevo -> cantFichasB = nuevo -> cantFichasB + 1;
        }
        else if( dato != NONE)
        {
            lecturaCorrecta = false; //Si no es ninguno significa que esta mal el dato
        }

        i++;
    }


    if( i == 26 && !feof(fp) && fscanf(fp, "%d\n", &dato ) == 1 && (dato == EquipoB || dato == EquipoA) )
    {
        nuevo -> turno = dato;
        return nuevo; //Proceso terminado
    }

    liberarTablero(nuevo);
    return NULL;


}
