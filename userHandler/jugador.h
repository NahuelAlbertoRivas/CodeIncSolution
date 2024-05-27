#ifndef JUGADOR
#define JUGADOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../env/estructuras.h"

void cargarJugadores(tJuego* juego);
void ingresarNombreJugador(int numJugador, tJugador* jugadorActual);
void mezclarJugadores(void* juego, int cantJugadores);
void intercambiarJugadores(tJugador* jugadorA, tJugador* jugadorB);
void calcularPuntajePorJugador(tJugador* jugador, int nroRonda, int menorTiempo,
                               int correctasEnMenorTiempoPorRonda);

#endif
