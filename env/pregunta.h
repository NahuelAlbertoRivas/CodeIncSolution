#ifndef PREGUNTA
#define PREGUNTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "estructuras.h"

void parsearPregunta(char* jsonString, tJuego* juego);
void imprimirPregunta(FILE* salida, const void* pregunta);

void mezclarPreguntas(void* preguntas, int cantPreguntas);
void intercambiarPreguntas(tPregunta* preguntaA, tPregunta* preguntaB);

void cargarYMezclarOpciones(char opciones[][TAM_OPCION],
                            const tPregunta* pregunta);
void mezclarOpciones(tOpcion* opciones, int cantOpciones);
void intercambiarOpciones(tOpcion* opcionA, tOpcion* opcionB);

void realizarPregunta(void *pregunta, unsigned tamInfo, void *recurso);
void procesarRespuesta(tJuego* juego, tPregunta *pregunta, tRespuesta respuesta);
void calificarJugadorPorRespuestas(void *pregunta, unsigned tamInfo, void *recurso);
int compararIdPregunta(const void *pregunta1, const void *pregunta2);
void mostrarOpcionesPreguntaConRespuestas(void *pregunta, unsigned tamInfo, void *recurso);
void mostrarRespuestasPorPregunta(tPregunta *pregunta, tJuego *juego);

#endif
