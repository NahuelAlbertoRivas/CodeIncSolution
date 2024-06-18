#include "pregunta.h"
#include "juego.h"

#define TAM_MAX_OP 14

void parsearPregunta(char* json, tJuego *juego)
{
    cJSON *json_array = cJSON_Parse(json),
          *item;
    tPregunta preguntaAux;
    byte i,
         j,
         cantPreguntas;
    char opcion[TAM_MAX_OP];

    cantPreguntas = cJSON_GetArraySize(json_array);
    if (json_array == NULL)
    {
        fprintf(stderr, "Error al parsear el JSON.\n");
        return;
    }

    for (i = 0; i < cantPreguntas; i++)
    {
        item = cJSON_GetArrayItem(json_array, i);
        if (item == NULL)
        {
            fprintf(stderr, "Error al obtener el item %d del vector del JSON.\n", i);
            return;
        }

        preguntaAux.id = rand() * (rand() & 1? -1 : 1);
        strcpy(preguntaAux.pregunta, cJSON_GetObjectItem(item, "pregunta")->valuestring);

        for(j = 0; j < CANT_OPCIONES; j++)
        {
            if(j)
                snprintf(opcion, sizeof(opcion), "opcion_%d", j);
            else
                strcpy(opcion, "resp_correcta");
            strcpy(preguntaAux.opciones[j].valor, cJSON_GetObjectItem(item, opcion)->valuestring);
            preguntaAux.opciones[j].valida = j ? 0 : 1;
        }

        preguntaAux.nivel = cJSON_GetObjectItem(item, "nivel")->valueint;
        preguntaAux.menorTiempoRespuesta = juego->tiempoRonda;
        preguntaAux.cantMenorTiempoRespuesta = 0;

        mezclarOpciones(preguntaAux.opciones, CANT_OPCIONES);

        ponerEnOrdenConDuplicados(&(juego->preguntas), &preguntaAux, sizeof(tPregunta), compararIdPregunta, NULL);
    }

    cJSON_Delete(json_array);
}

void mezclarOpciones(tOpcion *opciones, int cantOpciones)
{
    int i;
    int j;

    for(i = cantOpciones - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        if (i != j)
            intercambiarOpciones(&opciones[i], &opciones[j]);
    }
}

void intercambiarOpciones(tOpcion* opcionA, tOpcion* opcionB)
{
    tOpcion temp = *opcionA;

    *opcionA = *opcionB;
    *opcionB = temp;
}

int mostrarPreguntasAlJugador(void *jugador, void *recurso)
{
    tJugador *jug;
    tJuego *juego;

    if(!jugador || !recurso)
        return ERROR_PARAMETROS;

    juego = (tJuego *) recurso;
    jug = (tJugador *)jugador;

    juego->rondaActual = 1;

    system("cls");
    printf("Preparate %s, cuando estés listo presioná cualquier tecla\n",
                jug->nombre);
    ingresoNoRequerido(CLEAN_BUFFER);
    fflush(stdin); /// por si anteriormente ingresaron enter, ya que esta última tecla tiene doble acción sobre el buffer
    system("cls");
    printf("[Tu turno %s]", jug->nombre);

    mapLista((&juego->preguntas), realizarPregunta, juego);

    printf("\n\nFin de tu turno %s, ingresá cualquier tecla para continuar", jug->nombre);
    ingresoNoRequerido(CLEAN_BUFFER);
    fflush(stdin);
    system("cls");

    return TODO_OK;
}

int realizarPregunta(void *pregunta, void *recurso)
{
    tPregunta *preg;
    tJuego *juego;
    tRespuesta respuesta;
    byte opcion;

    if(!pregunta || !recurso)
        return ERROR_PARAMETROS;

    preg = (tPregunta *) pregunta;
    juego = (tJuego *) recurso;

    printf("\n\nPregunta %d: %s\n", juego->rondaActual, preg->pregunta);

    for(opcion = 0; opcion < CANT_OPCIONES; opcion++)
        printf("%c- %s\n", 'A' + opcion, preg->opciones[opcion].valor);
    printf("Respuesta: ");
    respuesta.tiempoDeRespuesta = iniciarTemporizador(&(respuesta.opcion), juego->tiempoRonda);
    respuesta.puntaje = 0;

    procesarRespuesta(juego, preg, respuesta);
    juego->rondaActual++;

    return TODO_OK;
}

void procesarRespuesta(tJuego* juego, tPregunta *pregunta, tRespuesta respuesta)
{
    char res;

    if(respuesta.opcion == '\0')
        respuesta.esCorrecta = 0;
    else
    {
        if(islower(respuesta.opcion))
            respuesta.opcion = toupper(respuesta.opcion);
        respuesta.esCorrecta = pregunta->opciones[(respuesta.opcion-'A')].valida;
        if(respuesta.esCorrecta)
        {
            if((res = pregunta->menorTiempoRespuesta - respuesta.tiempoDeRespuesta) > 0)
            {
                pregunta->menorTiempoRespuesta = respuesta.tiempoDeRespuesta;
                pregunta->cantMenorTiempoRespuesta = 1;
            }
            else if(res == 0)
                pregunta->cantMenorTiempoRespuesta++;
        }
    }

    ponerEnCola(&(pregunta->respuestas), &respuesta, sizeof(respuesta));
}

int mostrarOpcionesPreguntaConRespuestas(void *pregunta, void *recurso)
{
    byte opcion;
    tPregunta *preg;
    tJuego *juego;

    if(!pregunta || !recurso)
        return ERROR_PARAMETROS;

    preg = (tPregunta *) pregunta;
    juego = (tJuego *) recurso;

    fprintf(juego->salidaActual, "Pregunta: %s", preg->pregunta);
    for(opcion = 0; opcion < CANT_OPCIONES; opcion++)
        fprintf(juego->salidaActual, "\n\t%c) %s %s", 'A' + opcion,
                                         preg->opciones[opcion].valor,
                                         preg->opciones[opcion].valida? "(Correcta)" : "");
    fprintf(juego->salidaActual, "\n\n[Respuestas]:\n");
    mostrarRespuestasPorPregunta(preg, juego);
    fprintf(juego->salidaActual, "\n\n");

    return TODO_OK;
}

void mostrarRespuestasPorPregunta(tPregunta *preg, tJuego *juego)
{
    tAuxResumenFinal recursoResumen;

    if(!preg || !juego)
        return;

    recursoResumen.juego = juego;
    recursoResumen.preg = preg;
    mapLista(&(juego->jugadores), mostrarJugadorRespuesta, &recursoResumen);
}

int compararIdPregunta(const void *pregunta1, const void *pregunta2)
{
    tPregunta *preg1,
              *preg2;

    if(!pregunta1)
        return MAYOR_DEFAULT;
    if(!pregunta2)
        return MENOR_DEFAULT;

    preg1 = (tPregunta *)pregunta1;
    preg2 = (tPregunta *)pregunta2;

    return preg1->id - preg2->id;
}

void calificarJugadorPorRespuestas(tJugador *jug, tPregunta *preg, tRespuesta *rta)
{
    if(!jug || !preg)
        return;

    if (rta->esCorrecta)
    {
        if (rta->tiempoDeRespuesta == preg->menorTiempoRespuesta)
        {
            if(preg->cantMenorTiempoRespuesta <= 1)
            {
                rta->puntaje = PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA;
                jug->puntaje += PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA;
            }
            else
            {
                rta->puntaje = PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA;
                jug->puntaje += PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA;
            }
        }
        else
        {
            rta->puntaje = PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA;
            jug->puntaje += PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA;
        }
    }
    else if(rta->opcion != '\0') /// si no es correcta, y además respondió algo erróneamente
    {
        rta->puntaje = PUNTOS_RESPUESTA_INCORRECTA;
        jug->puntaje += PUNTOS_RESPUESTA_INCORRECTA;
    }
}

int crearColaRespuestas(void *pregunta, void *recurso)
{
    tPregunta *preg;

    if(!pregunta)
        return ERROR_PARAMETROS;

    preg = (tPregunta *) pregunta;

    crearCola(&(preg->respuestas));

    return TODO_OK;
}

int inicializarMenorTiempoPreguntas(void *pregunta, void *recurso)
{
    tPregunta *preg;
    tJuego *juego;

    if(!pregunta || !recurso)
        return TODO_OK;

    preg = (tPregunta *) pregunta;
    juego = (tJuego *)recurso;

    preg->menorTiempoRespuesta = (byte) juego->tiempoRonda;

    return TODO_OK;
}

int liberarColaRespuestas(void *pregunta, void *recurso)
{
    tPregunta *preg;

    if(!pregunta)
        return ERROR_PARAMETROS;

    preg = (tPregunta *) pregunta;

    vaciarCola(&(preg->respuestas));

    return TODO_OK;
}
