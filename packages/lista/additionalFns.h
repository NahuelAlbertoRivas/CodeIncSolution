#ifndef ADDITIONAL_FNS
#define ADDITIONAL_FNS

#include "lista.h"

#ifndef END_PROCESS
#define END_PROCESS 500
#endif // END_PROCESS

#ifndef Accion
typedef int (*Accion)(void *);
#endif // Accion

#ifndef CallbackRed
typedef int (*CallbackRed)(void *, void *);
#endif // CallbackRed

#ifndef MINIMO
#define MINIMO(x, y) ((x) > (y))?(y):(x)
#endif // MINIMO

int recorrerLista(tLista *pl, Accion task);

void *_reduceClase(tLista *pl, void *valorInicial, CallbackRed accion);

/** //////////////////////////////// SECTOR PRUEBAS //////////////////////////////// **/

void crearListaEnteros(tLista *pl);

void mostrarEntero(const void *num, FILE *pf);

int sumarEnteros(void *num1, void* num2);

int valorMedioRedondeado(void *num1, void *num2);

#endif // ADDITIONAL_FNS
