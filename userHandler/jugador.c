#include "jugador.h"
#include "../env/pregunta.h"

void cargarJugadores(tJuego* juego)
{
    int numJugador;
    tJugador jugadorActual;

    numJugador = 0;

    ingresarNombreJugador(numJugador + 1, &jugadorActual);

    while(strcmp(jugadorActual.nombre, "0") && (numJugador < MAX_JUGADORES))
    {
        numJugador++;
        (juego->cantJugadores)++;
        jugadorActual.puntaje = 0;
        ponerEnOrdenConDuplicados(&(juego->jugadores), &jugadorActual, sizeof(jugadorActual), compararIdJugadores, NULL);
        ingresarNombreJugador(numJugador + 1, &jugadorActual);
    }
}

void ingresarNombreJugador(int numJugador, tJugador* jugadorActual)
{
    do
    {
        fprintf(stdout, "Ingrese el nombre del jugador %d o ingrese '0' para finalizar: ", numJugador);
        fflush(stdin);
        gets(jugadorActual->nombre);
    }
    while(strlen(jugadorActual->nombre) == 0);

    jugadorActual->id = rand() * (rand() & 1? -1 : 1);

    system("cls");
}

int compararIdJugadores(const void *jugador1, const void *jugador2)
{
    tJugador *jug1,
             *jug2;

    if(!jugador1)
        return MAYOR_DEFAULT;
    if(!jugador2)
        return MENOR_DEFAULT;

    jug1 = (tJugador *) jugador1;
    jug2 = (tJugador *) jugador2;

    return jug1->id - jug2->id;
}

int mostrarOrdenJugador(void *jugador, void *recurso)
{
    tJugador *jug;
    byte *nro;

    if(!jugador || !recurso)
        return ERROR_PARAMETROS;

    jug = (tJugador *) jugador;
    nro = (byte *) recurso;

    printf("Turno %d: %s\n", *nro, jug->nombre);

    (*nro)++;

    return TODO_OK;
}

int compararPuntaje(const void *ganador, const void *jugador)
{
    tJugador *jug,
             *gan;

    if(!jugador)
        return MAYOR_DEFAULT;
    if(!ganador)
        return MENOR_DEFAULT;

    jug = (tJugador *) jugador;
    gan = (tJugador *) ganador;

    return  gan->puntaje - jug->puntaje;
}

/// (recordemos que la cola tiene las respuestas respectivamente a como están los jugadores en la lista)
/// fn para mapear lista de jugadores
int mostrarJugadorRespuesta(void *jugador, void *recurso)
{
    tJugador *jug;
    tRespuesta rta;
    tAuxResumenFinal *recursoResumen;

    if(!jugador || !recurso)
        return ERROR_PARAMETROS;

    recursoResumen = (tAuxResumenFinal *) recurso;
    jug = (tJugador *)jugador;

    if(sacarDeCola(&(recursoResumen->preg->respuestas), &rta, sizeof(tRespuesta)) == TODO_OK_)
    {
        calificarJugadorPorRespuestas(jug, recursoResumen->preg, &rta);
        if(rta.opcion) /// significa que el jugador respondió algo -bien o mal-
            fprintf(recursoResumen->juego->salidaActual, "%s: %d %s en contestar\t %c (%s%d)\n", jug->nombre,
                                                                                 rta.tiempoDeRespuesta,
                                                                                 rta.tiempoDeRespuesta == 1?"segundo":"segundos",
                                                                                 rta.opcion,
                                                                                 rta.puntaje > 0 ? "+" : "",
                                                                                 rta.puntaje);
        else /// el jugador no respondió nada
            fprintf(recursoResumen->juego->salidaActual, "%s: No contesta\t0 puntos\n", jug->nombre);
    }

    return TODO_OK;
}

int mostrarPuntajesTotales(void *jugador, void *recurso)
{
    tJugador *jug;
    tJuego *juego;

    if(!jugador || !recurso)
        return ERROR_PARAMETROS;

    jug = (tJugador *)jugador;
    juego = (tJuego *)recurso;

    fprintf(juego->salidaActual, "\t%s:\t%3d %s\n", jug->nombre, jug->puntaje, jug->puntaje == 1 || jug->puntaje == -1?"punto":"puntos");

    return TODO_OK;
}

int mostrarSiEsGanador(void *jugador, void *recurso)
{
    tJugador *jug;
    tJuego *juego;

    if(!jugador || !recurso)
        return ERROR_PARAMETROS;

    jug = (tJugador *)jugador;
    juego = (tJuego *)recurso;

    if(jug->puntaje == juego->puntajeMaximo)
        fprintf(juego->salidaActual, "\t%s\n", jug->nombre);

    return TODO_OK;
}
