#include "cola.h"

#define RESERVAR_MEMORIA_NODO(nodo, tamNodo, info, tamInfo) ( !( (nodo) = (tNodoCola *) malloc(tamNodo) )  ||      \
                                                                    !( (info) = malloc(tamInfo) )?                 \
                                                                          free(nodo), SIN_MEM_ : TODO_OK_           )

void crearCola(tCola *p)
{
    p->pri = NULL;
    p->ult = NULL;
}

int ponerEnCola(tCola *p, const void *d, unsigned cantBytes)
{
    tNodoCola *nue;

    if(RESERVAR_MEMORIA_NODO(nue, sizeof(tNodoCola), nue->info, cantBytes) != TODO_OK_)
        return SIN_MEM_;

    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    if(p->ult) /// si hab�a un �ltimo (en caso de que haya un solo elemento ser� el primero y �ltimo)
        p->ult->sig = nue; /// el siguiente del �ltimo apuntar� a este nuevo
    else
        p->pri = nue; /// si no hab�a ning�n elemento, el nuevo es el primero
    p->ult = nue; /// finalmente el nuevo siempre ser� el �ltimo
    return TODO_OK_;
}

int colaVacia(const tCola *p)
{
    return p->pri == NULL;
}

int sacarDeCola(tCola *p, void *d, unsigned cantBytes)
{
    tNodoCola *aux = p->pri; /// me guardo el primero en una var auxiliar
    if(aux == NULL) /// si la cola est� vac�a, me voy
        return COLA_VACIA;
    p->pri = aux->sig;
    memcpy(d, aux->info, MINIMO(aux->tamInfo, cantBytes));
    free(aux->info);
    free(aux);
    if(p->pri == NULL)
        p->ult = NULL;
    return TODO_OK_;
}

void vaciarCola(tCola *p)
{
    while(p->pri)
    {
        tNodoCola *aux = p->pri;
        p->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->ult = NULL;
}
