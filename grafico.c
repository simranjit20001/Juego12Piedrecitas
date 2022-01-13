#include "grafico.h"
#define true 1
#define false 0
#define X_BOTON_RETROCESO 1180
#define Y_BOTON_RETROCESO 0
#define ANCHO_BOTON_RETROCESO 100
#define ALTO_BOTON_RETROCESO 100

#define TECLA_RETROCESO "imagenes/tecla_atras.bmp"
#define TECLA_MUESTRA_ANTERIOR "imagenes/botonMuestraAnterior.bmp"
#define IMG_MANUAL0 "imagenes/manual_0.bmp"
#define IMG_MANUAL1 "imagenes/manual_1.bmp"
#define IMG_MANUAL2 "imagenes/manual_2.bmp"
#define IMG_MANUAL3 "imagenes/manual_3.bmp"
#define IMG_MANUAL4 "imagenes/manual_4.bmp"
#define IMG_MANUAL5 "imagenes/manual_5.bmp"
#define IMG_MANUAL6 "imagenes/manual_6.bmp"
#define IMG_MANUAL7 "imagenes/manual_7.bmp"
#define IMG_MANUAL8 "imagenes/manual_8.bmp"
#define IMG_MANUAL9 "imagenes/manual_9.bmp"
#define IMG_MANUAL10 "imagenes/manual_10.bmp"
#define IMG_GANADOR_EQUIPOA "imagenes/ganador_azul.bmp"
#define IMG_GANADOR_EQUIPOB "imagenes/ganador_rojo.bmp"
#define IMG_NO_PARTIDA_GUARDADA "imagenes/errorNoHayPartida.bmp"

#define INDETERMINADO -1

void dibujarBotonMuestraAnterior()
{
    Imagen img  =  Pantalla_ImagenLee(TECLA_MUESTRA_ANTERIOR , 0);
    Pantalla_DibujaImagen(img, X_BOTON_RETROCESO, Y_BOTON_RETROCESO+100, ANCHO_BOTON_RETROCESO, ALTO_BOTON_RETROCESO);
    Pantalla_ImagenLibera(img);
}


int ratonSobreMuestraAnterior()
{
    double x = 0;
    double y = 0;
    Pantalla_RatonCoordenadas(&x, &y);
    return x > X_BOTON_RETROCESO && y > (Y_BOTON_RETROCESO+100) && x < X_BOTON_RETROCESO + ANCHO_BOTON_RETROCESO && y < (Y_BOTON_RETROCESO + ALTO_BOTON_RETROCESO + 100);
}


void actualizaTeclaClickada(int * pulsado, int * x, int *y)
{

    if( Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT) )
    {
        * pulsado = true;
        * x = INDETERMINADO;
        * y = INDETERMINADO; // INDETERMINADO indica no hay ficha clikada
        return ;
    }
    else if (* pulsado == false)
    {
        * x = INDETERMINADO;
        * y = INDETERMINADO; // INDETERMINADO indica no hay ficha clikada
        return ; //si no se cliko entonces no hago nada
    }

    double ratonX = 0;
    double ratonY = 0;
    * pulsado = 0;
//PASAR ARRIBA LOS VALORES POR DEFECTO Y HACERLO EN CASCADA
    Pantalla_RatonCoordenadas(&ratonX, &ratonY);
    tableroFichaCoordenadas(ratonX, ratonY, x, y);
}

void actualizaFichaSelecionada(int xClikada, int yClikada, int * xSelecionada, int * ySelecionada, Tablero t)
{
    if(xClikada == -1) return ;
    if( xClikada == * xSelecionada && yClikada == * ySelecionada)
    {
        * xSelecionada = INDETERMINADO;
        * ySelecionada = INDETERMINADO;
        return ;
    }
    if( tableroLeerTurno(t) == tableroLeerPosicion(t, xClikada, yClikada) )
    {
        * xSelecionada = xClikada;
        * ySelecionada = yClikada;
    }
}

void dibujarPreMovimientos(int fichaSelecionadaX, int fichaSelecionadaY, ConjuntoMovimientos conjunto)
{
    if(fichaSelecionadaX == -1) return ;
    Iterador_ConjuntoMovmientos it = creaIteradorCm(fichaSelecionadaX, fichaSelecionadaY, conjunto);
    while(!(finIteradorCm(it)))
    {
        tableroDibujarPremov(accedeXIteradorCm(it), accedeYIteradorCm(it));
        avanzaIteradorCm(it);
    }
    liberaIterador(it);
}

void mostrarGanador(Equipo equipo)
{
    Imagen img = NULL;
    if(equipo == EquipoA ) img  =  Pantalla_ImagenLee(IMG_GANADOR_EQUIPOA , 0);
    else img  =  Pantalla_ImagenLee(IMG_GANADOR_EQUIPOB , 0);
    Pantalla_DibujaImagen(img, 0, 0, 1280, 720);
    Pantalla_ImagenLibera(img);
}

void dibujarManual(int pos)
{

    Imagen img_selec = NULL;
    Pantalla_ColorTrazo(0, 255, 0, 255);
    Pantalla_DibujaTexto("USA LAS FLECHAS PARA MOVERTE <-   -> ", 156, 60);
    Pantalla_DibujaTexto("Y PULSA ENTER PARA CONTINUAR", 156, 90);


    switch(pos)
    {
    case 0:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL0, 0);

        break;
    case 1:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL1, 0);
        break;
    case 2:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL2, 0);

        break;
    case 3:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL3, 0);

        break;
    case 4:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL4, 0);

        break;
    case 5:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL5, 0);
        break;
    case 6:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL6, 0);
        break;
    case 7:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL7, 0);
        break;

    case 8:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL8, 0);
        break;

    case 9:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL9, 0);
        break;

    case 10:
        img_selec = Pantalla_ImagenLee(IMG_MANUAL10, 0);
        break;
    }


    Pantalla_DibujaImagen(img_selec, 0, 0, 1280, 720);
    Pantalla_ImagenLibera(img_selec);
}
