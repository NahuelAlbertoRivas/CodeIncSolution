#ifndef COLA_H
#define COLA_H

#include <stdlib.h>
#include <string.h>

#define MINIMO( X , Y ) ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )

#define SIN_MEM_ -55
#define TODO_OK_ 1
#define COLA_VACIA -119

typedef struct sNodoCola
{
    void *info;
    unsigned tamInfo;
    struct sNodoCola *sig;
} tNodoCola;

typedef struct
{
    tNodoCola *pri,
              *ult;
} tCola;

void crearCola(tCola *p);

int colaLlena(const tCola *p, unsigned cantBytes);

int ponerEnCola(tCola *p, const void *d, unsigned cantBytes);

int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes);

int colaVacia(const tCola *p);

int sacarDeCola(tCola *p, void *d, unsigned cantBytes);

void vaciarCola(tCola *p);

#endif
