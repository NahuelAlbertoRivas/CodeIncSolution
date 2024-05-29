#ifndef JUEGO
#define JUEGO

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
void mostrarOrdenJuego(tJuego* juego);
void iniciarTrivia(tJuego* juego);

void determinarPuntos(tJuego* juego);
int obtenerCorrectasEnMenorTiempo(const tJugador* jugadores, int cantJugadores,
                                  int nroRonda, int menorTiempo);

#endif
