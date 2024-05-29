#include"arbol.h"

#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

#define RESERVAR_MEMORIA_NODO_ARBOL(nodo, tamNodo, info, tamInfo) ( !( (nodo) = (tNodoArbol *) malloc(tamNodo) )  ||    \
                                                                    !( (info) = malloc(tamInfo) )?                      \
                                                                          free(nodo), SIN_MEM : TODO_BIEN               )

void crearArbolBinBusq(tArbolBinBusq *p)
{
    *p = NULL;
}

int insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam, int (*cmp)(const void *, const void *))
{
    tNodoArbol *nue;
    int rc;

    while(*p)
    {
        if((rc = cmp(d, (*p)->info)) < 0)
            p = &(*p)->izq;
        else if (rc > 0)
            p = &(*p)->der;
        else
            return CLA_DUP;
    }
    if(!RESERVAR_MEMORIA_NODO_ARBOL(nue, sizeof(tNodoArbol), nue->info, tam))
        return SIN_MEM;
    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);
    nue->der = nue->izq = NULL;
    *p = nue;
    return TODO_BIEN;
}

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq * p, void * params, void (*accion)(void *, unsigned, void *))
{
    if(!*p)
        return;
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq, params, accion);
    accion((*p)->info, (*p)->tamInfo, params);
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der, params, accion);
}

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *))
{
    if(!(p = buscarNodoArbolBinBusq(p,d,cmp)))
        return 0; ///NO_EXISTE
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

tNodoArbol **buscarNodoArbolBinBusq(const tArbolBinBusq * p, const void * d, int (*cmp)(const void*, const void *))
{
    int rc;
    while(*p && (rc=cmp(d, (*p)->info)))
    {
        if(rc<0)
            p = &(*p)->izq;
        else
            p = &(*p)->der;
    }
    if(!*p)
        return NULL;
    return (tNodoArbol **)p;
}

const tArbolBinBusq *buscarNodoNoClaveArbolBinBusq(const tArbolBinBusq *p, const void *d,
                                                    int (*cmp)(const void *, const void *))
{
    const tArbolBinBusq * busq = NULL;
    if (!*p)
        return NULL;
    if (cmp((*p)->info, d)<0)
        return p;
    if((busq = buscarNodoNoClaveArbolBinBusq(&(*p)->izq, busq, cmp)))
        return busq;
    return buscarNodoNoClaveArbolBinBusq(&(*p)->der, busq, cmp);
}

tNodoArbol ** mayorNodoArbolBinBusq(const tArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    while((*p)->der)
        p = &(*p)->der;
    return (tNodoArbol **) p;
}

int mayorElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *))
{
    const tArbolBinBusq * mayor = p;
    if (!*p)
        return 0;
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->izq, mayor, cmp);
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->der, mayor, cmp);

    memcpy(d, (*mayor)->info, MINIMO(tam, (*mayor)->tamInfo));

    return 1;
}

const tArbolBinBusq * mayorNodoNoClaveArbolBinBusq(const tArbolBinBusq *p, const tArbolBinBusq *mayor,
                                                    int (*cmp)(const void *, const void *))
{
    if (!*p)
        return mayor;
    if (cmp((*p)->info, (*mayor)->info)>0)
        mayor = p;
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->izq, mayor, cmp);
    mayor = mayorNodoNoClaveArbolBinBusq(&(*p)->der, mayor, cmp);
    return mayor;
}

int mayorElemArbolBinBusq(const tArbolBinBusq * p, void * d, unsigned tam)
{
    if(!(p = mayorNodoArbolBinBusq(p)))
        return 0;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

tNodoArbol ** menorNodoArbolBinBusq(const tArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    while((*p)->izq)
        p = &(*p)->izq;
    return (tNodoArbol **) p;
}

int menorElemArbolBinBusq(const tArbolBinBusq * p, void * d, unsigned tam)
{
    if(!(p = menorNodoArbolBinBusq(p)))
        return 0;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

int menorElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam, int (*cmp)(const void *, const void *))
{
    const tArbolBinBusq * menor = p;
    if (!*p)
        return 0;
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->izq, menor, cmp);
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->der, menor, cmp);

    memcpy(d, (*menor)->info, MINIMO(tam, (*menor)->tamInfo));

    return 1;
}

const tArbolBinBusq *menorNodoNoClaveArbolBinBusq(const tArbolBinBusq *p, const tArbolBinBusq *menor,
                                                    int (*cmp)(const void *, const void *))
{
    if (!*p)
        return menor;
    if (cmp((*p)->info, (*menor)->info)<0)
        menor = p;
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->izq, menor, cmp);
    menor = menorNodoNoClaveArbolBinBusq(&(*p)->der, menor, cmp);
    return menor;
}

void eliminarArbol(tArbolBinBusq *pa){ /// tiene que ser en posorden
    if(!(*pa)) /// me fijo si hay árbol
        return;
    if((*pa)->izq) /// primero izq
        eliminarArbol(&((*pa)->izq));
    if((*pa)->der) /// desp der
        eliminarArbol(&((*pa)->der));
    free((*pa)->info); /// la info
    free(*pa);
    *pa = NULL;
}
