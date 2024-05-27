#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "estructuras.h"

void parsearPregunta(char* jsonString, void* preguntas);
void imprimirPregunta(FILE* salida, const void* pregunta);

void mezclarPreguntas(void* preguntas, int cantPreguntas);
void intercambiarPreguntas(tPregunta* preguntaA, tPregunta* preguntaB);

void cargarYMezclarOpciones(char opciones[][TAM_OPCION],
                            const tPregunta* pregunta);
void mezclarOpciones(tOpcion* opciones, int cantOpciones);
void intercambiarOpciones(tOpcion* opcionA, tOpcion* opcionB);

void realizarPregunta(tJuego* juego, int jugador, int rondaActual);
void procesarRespuesta(tJuego* juego, int jugador, int rondaActual,
                       char opciones[][TAM_OPCION], char respuesta,
                       int menorTiempo, int tiempoDeRespuesta);

#endif // PREGUNTA_H_INCLUDED
