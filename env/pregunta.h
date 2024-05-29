#ifndef PREGUNTA
#define PREGUNTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "estructuras.h"

void parsearPregunta(char* jsonString, tJuego* juego);
void imprimirPregunta(FILE* salida, const void* pregunta);

void mezclarOpciones(tOpcion* opciones, int cantOpciones);
void intercambiarOpciones(tOpcion* opcionA, tOpcion* opcionB);

int mostrarPreguntasAlJugador(void *jugador, void *recurso);
void realizarPregunta(void *pregunta, unsigned tamInfo, void *recurso);
void procesarRespuesta(tJuego* juego, tPregunta *pregunta, tRespuesta respuesta);
void calificarJugadorPorRespuestas(tJugador *jug, tPregunta *preg, tRespuesta *rta);
int compararIdPregunta(const void *pregunta1, const void *pregunta2);
void mostrarOpcionesPreguntaConRespuestas(void *pregunta, unsigned tamInfo, void *recurso);
void mostrarRespuestasPorPregunta(tPregunta *pregunta, tJuego *juego);

void crearColaRespuestas(void *pregunta, unsigned tamInfo, void *recurso);
void inicializarMenorTiempoPreguntas(void *pregunta, unsigned tamInfo, void *recurso);
void liberarColaRespuestas(void *pregunta, unsigned tamInfo, void *recurso);

#endif
