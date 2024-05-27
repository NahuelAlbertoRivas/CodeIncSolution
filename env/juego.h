#ifndef JUEGO
#define JUEGO

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>

#include "../apiConfigs/curlReducido.h"
#include "../env/pregunta.h"
#include "../userHandler/jugador.h"
#include "../env/estructuras.h"
#include "../env/teclado.h"

#define SIN_JUGADORES -4

char mostrarMenu();
char iniciarJuego();
int configurarJuego(tJuego* juego);
void elegirDificultad(tJuego* juego);
void mezclar(void* item, int cantElementos, void(*mezclarImpl)(void*, int));
void mostrarOrdenJuego(const tJuego* juego);
void mostrarInformacionJuego(const tJuego* juego);  /// borrar
void iniciarTrivia(tJuego* juego);
void realizarRondas(tJuego* juego, int jugador);
void inicializarMenorTiempoRondas(tJuego *juego);

void determinarPuntos(tJuego* juego);
int obtenerCorrectasEnMenorTiempo(const tJugador* jugadores, int cantJugadores,
                                  int nroRonda, int menorTiempo);

#endif
