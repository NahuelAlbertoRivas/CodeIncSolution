#ifndef ARBOL_BIN_BUSQ_H_INCLUDED
#define ARBOL_BIN_BUSQ_H_INCLUDED

#ifndef STRING
#include<string.h>
#endif // STRING

#ifndef STDLIB
#include<stdlib.h>
#endif // STDLIB

#ifndef STDIO
#include<stdio.h>
#endif // STDIO

#ifndef MATH
#include<math.h>
#endif // MATH

#ifndef CLA_DUP
#define CLA_DUP 0
#endif // CLA_DUP

#ifndef SIN_MEM
#define SIN_MEM 0
#endif // SIN_MEM

#ifndef SIN_INICIALIZAR
#define SIN_INICIALIZAR 0
#endif // SIN_INICIALIZAR

#ifndef ERROR_ARCH
#define ERROR_ARCH 0
#endif // ERROR_ARCH

#ifndef TODO_BIEN
#define TODO_BIEN 1
#endif // TODO_BIEN


typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                    *der;
}tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;

typedef int (*accionManejoDatos)(void *, void *);

void crearArbolBinBusq(tArbolBinBusq *p);

int insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam, int (*cmp)(const void *, const void *));

int insertarRecArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam, int (*cmp)(const void*, const void *));

void recorrerEnOrdenArbolBinBusq(const tArbolBinBusq * p, void * params, void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenInversoArbolBinBusq(const tArbolBinBusq * p, void * params, void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPreOrdenArbolBinBusq(const tArbolBinBusq * p, void * params, void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPosOrdenArbolBinBusq(const tArbolBinBusq * p, void * params, void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params, void (*accion)(void *, unsigned, void *));

void recorrerPreOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params, void (*accion)(void *, unsigned, void *));

void recorrerPosOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params, void (*accion)(void *, unsigned, void *));

int eliminarRaizArbolBinBusq(tArbolBinBusq *p);

int eliminarElemArbolBinBusq(tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *));

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *));

int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(tArbolBinBusq *p, FILE *pf, unsigned tamInfo);

int cargarArchivoBinOrdenadoArbolBinBusq(tArbolBinBusq * p, const char * path, unsigned tamInfo);

int cargarDesdeDatosOrdenadosArbolBinBusq(tArbolBinBusq *p, void *ds, unsigned cantReg,
                                            unsigned (*leer)(void **, void *, unsigned, void *params), void * params);

int mayorElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *));

int menorElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *));

int buscarElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *));

int buscarYAccionarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, void *recurso, int (*cmp)(const void *, const void *), accionManejoDatos tarea);

///Utils

unsigned alturaArbolBin(const tArbolBinBusq *p);

unsigned cantNodosArbolBin(const tArbolBinBusq *p);

unsigned cantNodosHastaNivelArbolBin(const tArbolBinBusq *p, int n);

int mayorElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam);

int menorElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam);

int esCompletoArbolBin(const tArbolBinBusq *p);

int esBalanceadoArbolBin(const tArbolBinBusq *p);

int esAVLArbolBin(const tArbolBinBusq *p);

int esCompleto2ArbolBin(const tArbolBinBusq *p);

int esBalanceado2ArbolBin(const tArbolBinBusq *p);

int esAVL2ArbolBin(const tArbolBinBusq *p);

void eliminarArbol(tArbolBinBusq *pa);

/// ////////////////////////////////////////////////////////////////////////////

tNodoArbol **mayorNodoArbolBinBusq(const tArbolBinBusq *p);

tNodoArbol **menorNodoArbolBinBusq(const tArbolBinBusq *p);

tNodoArbol **mayorRecNodoArbolBinBusq(const tArbolBinBusq *p);

tNodoArbol **menorRecNodoArbolBinBusq(const tArbolBinBusq *p);

tNodoArbol **buscarNodoArbolBinBusq(const tArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *));

tNodoArbol **buscarRecNodoArbolBinBusq(const tArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *));

int esCompletoHastaNivelArbolBin(const tArbolBinBusq *p, int n);

int esAVL2CalculoArbolBin(const tArbolBinBusq *p);

const tArbolBinBusq * mayorNodoNoClaveArbolBinBusq(const tArbolBinBusq *p, const tArbolBinBusq *mayor,
                                                    int (*cmp)(const void *, const void *));

const tArbolBinBusq * menorNodoNoClaveArbolBinBusq(const tArbolBinBusq *p, const tArbolBinBusq *menor,
                                                    int (*cmp)(const void *, const void *));

const tArbolBinBusq * buscarNodoNoClaveArbolBinBusq(const tArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *));

int accionarSobreElemArbolBinBusq(const tArbolBinBusq * p, const void * d, void *recurso, int (*cmp)(const void*, const void *), int(*accion)(void *, void *));

#endif // ARBOL_BIN_BUSQ_H_INCLUDED
