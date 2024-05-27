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
char imprimirResultados(const tJuego* juego);
void generarImpresion(FILE* salida, const tJuego* juego);
void calcularPuntajeMaximo(const tJugador* jugadores, int* puntajeMaximo,
                           int cantJugadores);

#endif
