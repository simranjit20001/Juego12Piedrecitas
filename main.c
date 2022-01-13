
/**
* @file main.h
* @Author Simranjit Singh
* @date 07/01/2022
* @brief Modulo principal
*/

#include <stdio.h>
#include <windows.h>
#include "Pantalla.h"
#include "tablero.h"
#include "conjunto_movimientos.h"
#include "reglas_movimiento.h"
#include "grafico.h"
#include "pila.h"
#include "pizarra.h"


/**
 * @brief Asocia al modo MULTIJUGADOR
 *
 */

#define MULTIJUGADOR 1

/**
 * @brief Indica modo IA
 *
 */

#define IA 0

/**
 * @brief Indica valor verdadero
 *
 */

#define true 1

/**
 * @brief Indica valor falso
 *
 */

#define false 0

/**
 * @brief Indica indeterminacion
 *
 */

#define INDETERMINADO -1 //INDICA qu� el valor es INVALIDO;


/**
 * @brief Representa a una coordenada bidimensional
 *
 */

typedef struct coordenada
{
    int x, y;
} Coordenada;


/**
    \mainpage Main
    <h1> 12 THINI </h1>
    <p>12 Thini es un juego asociado a algunas de las regiones rurales de Asia</p>
    <p>Esta es una implementacion de dicho juego para el Proyecto de TP</p>
    <p>Dispone de un modo multijugador, y modo contra IA</p>
    <p>Tambien dispone de un Manual de Ayuda</p>
    <p>Cualquier duda puede ser resuelta por el autor, es posible contactar mediante correo:</p>
    <p>simranjit.singh@um.es</p>
*/




/**
 * @brief Reproduce una partida guardada, y sino indica que no existe ninguna
 *
 */

void reproducirPartida()
{

    Pantalla_Crea("Simranjit", 1280, 720);
    Pantalla_ColorTrazo(0, 255, 0, 255);
    Pantalla_ColorRelleno(0,0,0, 255);

    FILE * fp = NULL;
    fp	=	fopen(	"ultimaPartida.txt",	"r"	);

    if(fp == NULL)
    {
        Pantalla_DibujaTexto("NO HA ENCONTRADO NINGUNA PARTIDA GUARDADA", 156, 60);
        Pantalla_Actualiza();
        Pantalla_Espera(2000);
        Pantalla_Libera();
        return ;
    }

    Tablero * tabs = NULL;
    int lecturaCorrecta = false;
    int n;
    lecturaCorrecta = !feof(fp) && fscanf(fp, "%d\n", &n ) == 1;

    if(!lecturaCorrecta)
    {
        fclose(fp);
        Pantalla_DibujaTexto("NO HA ENCONTRADO NINGUNA PARTIDA GUARDADA", 156, 60);
        Pantalla_Actualiza();
        Pantalla_Espera(2000);
        Pantalla_Libera();
        return ;
    }

    tabs = malloc(n*sizeof(Tablero));
    int i = 0;
    int lectCorrecta = true;
    while(i < n && lectCorrecta)
    {
        tabs[i] = tableroExtraer(fp);
        if(tabs[i] != NULL)
            i++; //Solo actualizamos si hemos leido el dato de forma correcta
        else
            lectCorrecta = false;

    }

    fclose(fp);

    if(i != n)
    {
        for(int j = 0; j < i; j++)
        {
            liberarTablero(tabs[j]);
        }

        Pantalla_DibujaTexto("NO HA ENCONTRADO NINGUNA PARTIDA GUARDADA", 156, 60);
        Pantalla_Actualiza();
        Pantalla_Espera(2000);
        Pantalla_Libera();
        return ;
    }

    int pulsado = false;
    int mostrar = n-1;

    while( Pantalla_Activa() )
    {

        Pantalla_DibujaRellenoFondo	(0,0,0, 0);

        if(pulsado)
        {
            pulsado = false;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_UP))
        {
            pulsado = true;
            if(mostrar < n-1)
                mostrar++;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN))
        {
            pulsado = true;
            if(mostrar > 1)
            {
                mostrar--;
            }
        }

        tableroDibujar(tabs[mostrar]);
        Pantalla_Actualiza();
        Pantalla_Espera(40);

    }

    for(int j = 0; j < n; j++)
    {
        liberarTablero(tabs[j]);
    }

    free(tabs);
    Pantalla_Libera();
}

/**
 * @brief Inicia el juego
 *
 * @param modoMultiugador Indica si el modo a usar es MULTIJUGADOR o IA
 */

void iniciarJuego(int modoMultiugador)
{

    Pantalla_Crea("Simranjit", 1280, 720);
    Pantalla_ColorRelleno(0,0,0, 0);


    const int pizInititPosX = 40;
    const int pizInititPosY = 50;
    Pizarra pizarra = crearPizarra();
    pizarraEstablecerPosicion(pizInititPosX, pizInititPosY, pizarra);
    pizarraEscribirTexto("  Para SALIR pulse X", pizarra, 0);

    Pila pilaTableros = pilaCrea();
    Tablero tableroActual = NULL;

    Coordenada fichaSelecionada = {INDETERMINADO, INDETERMINADO};
    Coordenada fichaClikada = {INDETERMINADO, INDETERMINADO};

    ConjuntoMovimientos movimientosDisponibles = creaConjuntoMovimiento();

    int noTerminado = true;
    int pulsado = false;
    int esRecuperada = false;

    //Buscamos si existe una partida sin terminar:
    FILE	*	fp	=	NULL;
    fp	=	fopen(	"noTerminada.txt",	"r"	);

    if(fp !=NULL)
    {
        //Existe el archivo
        tableroActual = tableroExtraer(fp);
        if(tableroActual != NULL)  //Existe un tablero en el formato correcto
        {
            char * quererSeguir = Pantalla_LeeTexto(240,320,105, "   Existe una partida sin terminar. Si desea continuarla introduzca"
                                                    " SI, en caso contrario pulse ENTER");

            if(quererSeguir == NULL || strcmp(quererSeguir, "SI") != 0)
            {
                liberarTablero(tableroActual);
                tableroActual = crearTablero();
            }
            else
            {
                esRecuperada = true;
            }
        }
    }


    fclose(fp);
    fp = NULL;
    remove("noTerminada.txt"); //Al entrar de nuevo se borra definitivamente la partida sin guardar

    if(!esRecuperada)
    {
        tableroActual = crearTablero(); //Si no se recupera la partida partimos del tablero en su estado inicial
    }

    pilaInserta(pilaTableros, tableroActual); //Insertamos el primer tablero a la pila

    while (Pantalla_Activa() && noTerminado)
    {

        if(tableroConsultaGanador(tableroActual) != NONE)
        {
            pilaInserta(pilaTableros, tableroActual);
            noTerminado = false;
            tableroDibujar(tableroActual);
            Pantalla_Actualiza();
            Pantalla_Espera(1000);
            mostrarGanador(tableroConsultaGanador(tableroActual));
            Pantalla_Actualiza();
            Pantalla_Espera(5000);
            break;
        }

        int puntuacionActual = tableroLeerPuntuacion(tableroActual);
        if(puntuacionActual > 0){
            pizarraEscribirTexto("  VENTAJA: EQUIPO A", pizarra, 6);
        }
        else if (puntuacionActual < 0) {
            pizarraEscribirTexto("  VENTAJA: EQUIPO B", pizarra, 6);
        }
        else{
            pizarraEscribirTexto("  ESTADO DE EMPATE", pizarra, 6);
        }

        if (tableroLeerTurno(tableroActual) == EquipoA || modoMultiugador)
        {
            pizarraEscribirTexto("  TURNO:   EQUIPO A", pizarra, 5);

            if (efectuarMovimientoJugador(&(fichaSelecionada.x), &(fichaSelecionada.y), fichaClikada.x, fichaClikada.y, movimientosDisponibles, &tableroActual) )
            {
                pilaInserta(pilaTableros, tableroActual);
            }
        }

        else
        {
            pizarraEscribirTexto("  TURNO:   EQUIPO B", pizarra, 5);
            pizarraDibujar(pizarra);
            Pantalla_Actualiza(); //necesitamos actualizar la pantalla para que muestre el turno
            efectuarMovimientoBot(&tableroActual);
            pilaInserta(pilaTableros, tableroActual);
        }


        if(ratonSobreMuestraAnterior())
        {
            if(pilaCantElem(pilaTableros) > 1) tableroDibujar(pilaRecuperaAnterior(pilaTableros));
        }
        else
        {
            tableroDibujar(tableroActual);
        }

        actualizaTeclaClickada(&pulsado, &(fichaClikada.x), &(fichaClikada.y));
        actualizaFichaSelecionada(fichaClikada.x, fichaClikada.y, &(fichaSelecionada.x), &(fichaSelecionada.y), tableroActual);
        tableroDibujarFichaSeleccionada(fichaSelecionada.x, fichaSelecionada.y);

        if (fichaSelecionada.x != INDETERMINADO)
            calcular_movimientos(fichaSelecionada.x, fichaSelecionada.y, tableroActual, movimientosDisponibles);

        dibujarPreMovimientos(fichaSelecionada.x, fichaSelecionada.y, movimientosDisponibles);
        dibujarBotonMuestraAnterior();
        pizarraDibujar(pizarra);

        Pantalla_Actualiza();
        Pantalla_Espera(40);

    }



    if(noTerminado)
    {
        fp	=	fopen(	"noTerminada.txt",	"w"	);
        if(fp != NULL) tableroGuardar(tableroActual, fp);
        fclose(fp);
        fp = NULL;
    }
    else
    {
        fp	=	fopen(	"ultimaPartida.txt",	"w"	); //SOLO SE GUARDA LA ULTIMA PARTIDA TERMINADA
        if(fp != NULL) fprintf(fp, "%d\n", pilaCantElem(pilaTableros));
    }

    while (!pilaVacia(pilaTableros))
    {
        Tablero temp = pilaRecupera(pilaTableros);
        if(fp != NULL)
        {
            tableroGuardar(temp, fp);
        }
        liberarTablero(temp); //OJO: la pila ya contine a T
        pilaSuprime(pilaTableros);
    }

    fclose(fp);
    pilaLibera(pilaTableros);
    pizarraLiberar(pizarra);
    liberaConjuntoMovimiento(movimientosDisponibles);
    Pantalla_Libera();
}


/**
 * @brief Muestra el menu
 *
 * @return int Indica la opcion escogida, 999 indica que NINGUNA opcion fue selecionada
 */
int menu()
{
    Pantalla_Crea("Simranjit",600,750);
    Pantalla_ColorTrazo(0, 255, 0, 255);
    Pantalla_ColorRelleno(0,0,0, 255);

    int terminado = 0;
    double const origen_x = 195;
    double const origen_y = 280;
    int  cuadrado_x = 190;
    int  cuadrado_y = 266;
    int pulsado = 0;

    while( Pantalla_Activa() && !terminado )
    {

        Pantalla_DibujaRellenoFondo	(0,0,0, 0);

        if(pulsado)
        {
            pulsado = 0;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN))
        {
            pulsado = 1;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_UP))
        {
            pulsado = 2;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN))
        {
            pulsado = 3;
        }

        switch(pulsado)
        {
        case 1:
            cuadrado_y = cuadrado_y + 50;
            if(cuadrado_y > 466) cuadrado_y = 266;
            break;
        case 2:
            cuadrado_y = cuadrado_y - 50;
            if(cuadrado_y < 266) cuadrado_y = 416;
            break;
        case 3:
            terminado = 1;

        }


        Pantalla_DibujaRectangulo((double)cuadrado_x, (double)cuadrado_y, 255, 40);

        Pantalla_DibujaTexto("INICIAR JUEGO: CONTRA LA IA", origen_x, origen_y);
        Pantalla_DibujaTexto("INICIAR JUEGO: MULTIJUGADOR", origen_x, origen_y+50);
        Pantalla_DibujaTexto("     MANUAL DE USUARIO     ", origen_x, origen_y+100);
        Pantalla_DibujaTexto("     REPRODUCIR PARTIDA    ", origen_x, origen_y+150);
        Pantalla_DibujaTexto("          SALIR            ", origen_x, origen_y+200);



        Pantalla_Actualiza();
        Pantalla_Espera( 80 );

    }

    Pantalla_Libera();

    if(!terminado)
    {
        const int SALIR = 999;
        return SALIR;
    }

    return (cuadrado_y-266)/50;

}

/**
 * @brief Muestra el manual de juego
 *
 */

void mostrarManual()
{

    Pantalla_Crea("Simranjit",1280,720);
    Pantalla_ColorTrazo(255, 0, 0, 0);
    Pantalla_ColorRelleno(0,0,0,0);

    int selecion = 0;
    int terminado = 0;
    int pulsado = 0;

    while( Pantalla_Activa() && !terminado )
    {


        if(pulsado)
        {
            pulsado = 0;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_LEFT))
        {
            pulsado = 1;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_RIGHT))
        {
            pulsado = 2;
        }
        else if(Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN))
        {
            pulsado = 3;
        }


        switch(pulsado)
        {
        case 1:
            selecion--;
            if(selecion < 0) selecion = 10;
            break;
        case 2:
            selecion++;
            if(selecion > 10) selecion = 0;
            break;
        case 3:
            terminado = 1;
        }


        dibujarManual(selecion);

        Pantalla_Actualiza();
        Pantalla_Espera( 80 );

    }

    Pantalla_Libera();
}

/**
    \brief Funcion main que hace de orquestador entre el resto de funciones
*/

int main( int argc, char *argv[] )
{
    int terminado = false;

    while(!terminado)
    {

        int selec = menu();

        switch(selec)
        {
        case 0:
            iniciarJuego(IA);
            break;
        case 1:
            iniciarJuego(MULTIJUGADOR);
            break;
        case 2:
            mostrarManual();
            break;
        case 3:
            reproducirPartida();
            break;
        default:
            terminado = true;
        }

    }
    return 0;
}
