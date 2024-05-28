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
int mostrarOrdenJugador(void *jugador, void *recurso);
void mostrarInformacionJuego(tJuego* juego);  /// borrar
void iniciarTrivia(tJuego* juego);
int mostrarPreguntasAlJugador(void *jugador, void *recurso);
void inicializarMenorTiempoPreguntas(void *pregunta, unsigned tamInfo, void *recurso);
void crearColaRespuestas(void *pregunta, unsigned tamInfo, void *recurso);
void liberarColaRespuestas(void *pregunta, unsigned tamInfo, void *recurso);
int mostrarJugadorRespuesta(void *jugador, void *recurso);

void determinarPuntos(tJuego* juego);
int obtenerCorrectasEnMenorTiempo(const tJugador* jugadores, int cantJugadores,
                                  int nroRonda, int menorTiempo);

#endif
