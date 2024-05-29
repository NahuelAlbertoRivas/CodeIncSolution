#ifndef ARCHIVOS
#define ARCHIVOS

#include "juego.h"
#include "estructuras.h"

#define MAX_LINEA_CONFIG 255

#define TAM_NOMBRE_INFORME 100
#define FILE_ERR -1
#define OK 0
#define TAM_MAX_LECTURA 509

char abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo,
                 const char* modoApertura);
char leerArchivoConfig(tJuego* juego);
char imprimirResultados(tJuego* juego);
void mostrarResultadosPorConsola(char *nombreArch);
void generarImpresion(tJuego* juego);

#endif
