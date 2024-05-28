#include "additionalFns.h"

int recorrerLista(tLista *pl, Accion task){
    while(*pl){
        task((*pl)->info);
        pl = &(*pl)->sig;
    }
    return TODO_OK;
}
/// Teniendo en cuenta el comportamiento del método ' reduce ' en lenguajes orientados a objetos
///
/// primera versión, la más inflexible y estándar, se recibe:
/// la estructura,
/// un acumulador (debido a que la versión original trabaja con enteros, así será este también)
/// una acción simple

/**int _reduce(tLista *pl, Accion accion){
    int pivote;

    while(*pl){
        pivote = accion(&(*pl)->info);
        pl = &(*pl)->sig;
    }

    return 1;
}**/

/// en esta versión, el campo ' recurso ' podría ser usado, entre otros, como:
/// a) un simple acumulador
/// b) un valor pivote de comparación
/// c) si se quisiese realizar cualquier operación adicional
///    se le pasaría al parámetro una estructura contexto adecuada

void _reduce0(tLista *pl, void *recurso, CallbackRed accion){
    while(*pl){
        accion(recurso, &(*pl)->info);
        pl = &(*pl)->sig;
    }
}

/// siguiendo la firma:
///
/// array.reduce(function(total, currentValue, currentIndex, arr), initialValue)
///
/// si quisieramos adaptar el concepto de callbacks que usa el método en lenguajes como JavaScript,
/// podemos observar que al trabajar con TDAs no nos es necesario ' currentIndex ' y ' arr '
/// (éste último más que nada porque en la implementación original es opcional y
/// como no tenemos contexto heredado de un objeto en C, debemos pasarle sí o sí la estructura,
/// sin embargo se decide que la misma se debe pasar a la función contenedora '_reduce ')
/// finalmente, la funcionalidad del callback que se pasa en el primer parámetro de la firma original
/// será emulada mediante un puntero a fn. ->
///
/// typedef int (*CallbackRed)(void *, void *);


int _reduce1(tLista *pl, void *valorInicial, CallbackRed accion){ /// si el usuario no quisiese agregar un valor inicial y/o acumulador, pasa NULL en dicho/s campo/s
    int resultado = 0;

    if(valorInicial) /// si me pasaron un valor inicial previo, será la base
        memcpy(&resultado, (int *) valorInicial, sizeof(resultado));
    else if(*pl){ /// si no, el valor por defecto es el primer elemento de la estructura
        memcpy(&resultado, (*pl)->info, sizeof(resultado));
        pl = &(*pl)->sig;
    }

    while(*pl){
        accion(&resultado, (*pl)->info);
        pl = &(*pl)->sig;
    }

    return resultado;
}

void *_reduceClase(tLista *pl, void *redux, CallbackRed accion){ /// si el usuario no quisiese agregar un valor inicial y/o acumulador, pasa NULL en dicho/s campo/s
    while(*pl){
        accion(redux, (*pl)->info);
        pl = &(*pl)->sig;
    }

    return redux;
}


/** //////////////////////////////// SECTOR PRUEBAS //////////////////////////////// **/

void mostrarEntero(const void *num, FILE *pf){
    fprintf(pf, "%d", *((int*)num));
}

int sumarEnteros(void *num1, void* num2){
    return *((int *)num1) + *((int *)num2);
}

int valorMedioRedondeado(void *num1, void *num2){ /// obs: casteo implícito a int en el retorno
    return ( *((float *)num2) + *((float *)num2) ) / 2;
}

void crearListaEnteros(tLista *pl){
    int vec[] = {40, 11, 26, 44, 15, 13, 99, 20, 88, 100, 0, 60, 23, 7, 200, 9, 10, 2, 80, 1000, 4, 3, 5, 1, 8}, /// {8, 1, 5, 3, 4, 1000, 80, 2, 10, 9, 200, 7, 23, 60, 0, 100, 88, 20, 99, 13, 15, 44, 26, 11, 40},
        i,
        val;

    for(i = 0; i < (sizeof(vec) / sizeof(*(vec + i))); i++){
        val = *(vec + i);
        val = sizeof(*(vec + i));
        if(!ponerAlComienzo(pl, vec + i, sizeof(*(vec + i)))){
            vaciarLista(pl);
            i = sizeof(vec) / sizeof(*(vec + i));
        }
    }
}
