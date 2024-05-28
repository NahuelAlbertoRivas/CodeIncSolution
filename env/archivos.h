#ifndef ARCHIVOS
#define ARCHIVOS

#include "juego.h"
#include "estructuras.h"

#define MAX_LINEA_CONFIG 255

#define TAM_NOMBRE_INFORME 100
#define ERROR_PARAMETROS -2
#define FILE_ERR -1
#define OK 0

char abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo,
                 const char* modoApertura);
char leerArchivoConfig(tJuego* juego);
char imprimirResultados(tJuego* juego);
void generarImpresion(tJuego* juego, tJugador, byte cantGanadores);
void calcularPuntajeMaximo(const tJugador* jugadores, int* puntajeMaximo,
                           int cantJugadores);
void obtenerMaximoPuntaje(void *jugador, void *maximo);

#endif
