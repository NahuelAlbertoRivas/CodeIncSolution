#ifndef JUGADOR
#define JUGADOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../env/estructuras.h"

void cargarJugadores(tJuego* juego);
void ingresarNombreJugador(int numJugador, tJugador* jugadorActual);
int compararIdJugadores(const void *jugador1, const void *jugador2);
int mostrarOrdenJugador(void *jugador, void *recurso);
int calcularPuntajePorJugador(void* jugador, void *recurso);
int compararPuntaje(const void *jugador, const void *ganador);
int mostrarPuntajesTotales(void *jugador, void *recurso);
int mostrarSiEsGanador(void *jugador, void *recurso);

#endif
