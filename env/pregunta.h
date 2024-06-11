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
int realizarPregunta(void *pregunta, void *recurso);
void procesarRespuesta(tJuego* juego, tPregunta *pregunta, tRespuesta respuesta);
void calificarJugadorPorRespuestas(tJugador *jug, tPregunta *preg, tRespuesta *rta);
int compararIdPregunta(const void *pregunta1, const void *pregunta2);
int mostrarOpcionesPreguntaConRespuestas(void *pregunta, void *recurso);
void mostrarRespuestasPorPregunta(tPregunta *pregunta, tJuego *juego);

int crearColaRespuestas(void *pregunta, void *recurso);
int inicializarMenorTiempoPreguntas(void *pregunta, void *recurso);
int liberarColaRespuestas(void *pregunta, void *recurso);

#endif
