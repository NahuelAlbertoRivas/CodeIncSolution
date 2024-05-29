#include "addFns.h"

void probarArbol()
{
    int vec[] = {100 , 50, 150, 25, 75, 175, 10, 30, 60, 90, 110, 130, 160, 200},
        i;
    tArbolBinBusq arbol;

    crearArbolBinBusq(&arbol);
}


/**

int leerDesdeArchivoBin(void *d, void *pf, unsigned pos, void *params)
{
    fseek((FILE*)pf, pos * tam, SEEK_SET);
    return fread(d, tam, 1, (FILE*)pf);
}


int cargarDesdeDatosOrdenadosRec(tArbolBinBusq * p, void * ds,
                        unsigned (*leer)(void **, void *, unsigned, void * params), int li, int ls, void * params)
{
    int m = (li+ls)/2,
    r;
    if (li>ls)
        return TODO_BIEN;

    if(!RESERVAR_MEMORIA_NODO(*p, sizeof(tNodoArbolBin), (*p)->info, cantBytes))
        return SIN_MEM;

    if(leer(&(*p)->info, ds, m, params) == EOF)
    {
        free((*p)->info);
        free(*p);
        return FIN_ARCHIVO;
    }

    (*p)->izq = (*p)->der = NULL;

    if((r=cargarDesdeDatosOrdenadosRec(&(*p)->izq, ds, leer, li, m-1, params))!= TODO_BIEN)
        return r;
    return cargarDesdeDatosOrdenadosRec(&(*p)->der, ds, leer, m+1, ls, params);
 }


**/
