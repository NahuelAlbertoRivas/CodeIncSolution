#ifndef ESTRUCTURAS
#define ESTRUCTURAS

#include <windows.h>

enum eDificultad
{
    FACIL = 1,
    MEDIO = 2,
    DIFICIL = 3
};

#define TAM_DIFICULTAD 10

typedef struct
{
    char nombre[TAM_DIFICULTAD];
    enum eDificultad valor;
} tMapeoDificultad;

#define TAM_ID 4
#define TAM_PREGUNTA 256
#define TAM_OPCION 256
#define CANT_OPCIONES 4

typedef struct
{
    char valor[TAM_OPCION],
         valida;
} tOpcion;

typedef struct
{
    char id[TAM_ID],
         pregunta[TAM_PREGUNTA];
    tOpcion opciones[CANT_OPCIONES];
    enum eDificultad nivel;
} tPregunta;

typedef struct
{
    int id;
    byte esCorrecta,
         tiempoDeRespuesta;
    char opcion,
         puntaje;
} tRespuesta;

#define NOMBRE_MAX 48
#define MAX_PREGUNTAS 100

typedef struct
{
    char nombre[NOMBRE_MAX],
         turno;
    short int puntaje;
    tRespuesta respuestas[MAX_PREGUNTAS]; // utilizar lista o cola
} tJugador;

#define MIN_TIEMPO_RONDA 1
#define MIN_RONDAS 4
#define MAX_RONDAS 7
#define MAX_PREGUNTAS 100
#define MAX_JUGADORES 10

typedef struct
{
    int cantRondas;
    int tiempoRonda;
    int cantJugadores;
    int menorTiempoRespuesta[MAX_PREGUNTAS];
    enum eDificultad dificultad;
    tPregunta preguntas[MAX_PREGUNTAS]; //Cambiar a tArbol si considero priorizar memoria antes que complejidad computacional (performance).
    tJugador jugadores[MAX_JUGADORES]; //Cambiar a tArbol si considero priorizar memoria antes que complejidad computacional (performance).
} tJuego;

// PUNTAJES
#define PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA 3
#define PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA 2
#define PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA 1
#define PUNTOS_RESPUESTA_INCORRECTA -2

#endif
