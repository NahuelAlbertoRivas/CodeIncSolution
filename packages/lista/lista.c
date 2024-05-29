#include "lista.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) ( !( (nodo) = (tNodoLista *)malloc(tamNodo) )  ||    \
                                                              !( (info) = malloc(tamInfo) )?                     \
                                                                   free(nodo), SIN_MEM : TODO_OK                 )

void crearLista(tLista *p)
{
    *p = NULL;
}

int listaVacia(const tLista *p)
{
    return *p == NULL;
}

int mostrarLista(const tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    int cant = 0;

    while(*p)
    {
        mostrar((*p)->info, fp);
        p = &(*p)->sig;
        cant++;
    }
    return cant;
}

int ponerEnOrdenConDuplicados(tLista *p, const void *d, unsigned cantBytes, int (*comparar)(const void *, const void *),
                  int (*acumular)(void **, unsigned *, const void *, unsigned))
{
    tNodoLista *nue;

    while(*p && comparar((*p)->info, d) < 0)
        p = &(*p)->sig;
    if(*p && comparar((*p)->info, d) == 0)
    {
        if(acumular)
        {
            if(!acumular(&(*p)->info, &(*p)->tamInfo, d, cantBytes))
                return SIN_MEM;
            else
                return TODO_OK;
        }
    }
    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoLista), nue->info, cantBytes))
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;
    return TODO_OK;
}

/// puede quedar bien que al momento de realizar el informe se ordene por el orden en que se registraron

void ordenar(tLista *p, int (*comparar)(const void *, const void *))
{
    tLista *pri = p; // obs: ' pri ' siempre apuntará al inicio de la lista

    if(*p == NULL) // si la lista está vacía, retorna
        return;
    while((*p)->sig) // mientras que no estemos en el último nodo de la lista, recorremos la lista mediante ' p '
    {
        if(comparar((*p)->info, (*p)->sig->info) > 0) // si la info. del nodo actual es mayor al ' siguiente '
        {
            tLista *q = pri; // ' q ' siempre apunta al inicio de la lista al comenzar cada iteración
            tNodoLista *aux = (*p)->sig; // ' aux ' adquiere el ' siguiente ' nodo

            (*p)->sig = aux->sig; // se asigna a ' p ' el próximo nodo del nodo ' siguiente '
            while((*q)->sig && comparar((*q)->info, aux->info) > 0) // mientras que la info. del primer elemento de la lista sea ' mayor ' al ' siguiente '
                q = &(*q)->sig; // avanzo al siguiente nodo
            aux->sig = *q; //
            *q = aux;
        }
        else // si la info. del actual es menor *o igual* a la del sig.
            p = &(*p)->sig; // simplemente avanzo al siguiente nodo
    }
}

int mapLista(const tLista *pl, int (*accion)(void *, void *), void *contexto)
{
    int cant = 0;

    while(*pl)
    {
        accion((*pl)->info, contexto);
        cant++;
        pl = &(*pl)->sig;
    }

    return cant;
}

int buscarMayorElemNoClaveLista(tLista *pl, void *buffer, unsigned cantBytes, Comparar cmp)
{
    tNodoLista *mayor = *pl;
    unsigned cant;
    int res;

    if(!mayor)
        return LISTA_VACIA;

    pl = &((*pl)->sig);
    cant = 1;

    while(*pl)
    {
        if( (res = cmp(mayor->info, (*pl)->info)) < 0)
        {
            mayor = *pl;
            cant = 1;
        }
        else if(res == 0)
            cant++;
        pl = &((*pl)->sig);
    }

    memcpy(buffer, mayor->info, minimo(cantBytes, mayor->tamInfo));

    return cant;
}

int vaciarLista(tLista *p)
{
    int cant = 0;
    while(*p)
    {
        tNodoLista *aux = *p;

        cant++;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
    return cant;
}
