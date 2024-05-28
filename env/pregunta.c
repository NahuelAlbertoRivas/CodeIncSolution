#include "pregunta.h"
#include "juego.h"

void parsearPregunta(char* json, tJuego *juego)
{
    cJSON *json_array = cJSON_Parse(json),
          *item;
    tPregunta preguntaAux;
    byte i,
         cantPreguntas;

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
        strcpy(preguntaAux.opciones[0].valor, cJSON_GetObjectItem(item, "resp_correcta")->valuestring);
        preguntaAux.opciones[0].valida = 1;
        strcpy(preguntaAux.opciones[1].valor, cJSON_GetObjectItem(item, "opcion_1")->valuestring);
        preguntaAux.opciones[1].valida = 0;
        strcpy(preguntaAux.opciones[2].valor, cJSON_GetObjectItem(item, "opcion_2")->valuestring);
        preguntaAux.opciones[2].valida = 0;
        strcpy(preguntaAux.opciones[3].valor, cJSON_GetObjectItem(item, "opcion_3")->valuestring);
        preguntaAux.opciones[3].valida = 0;
        preguntaAux.nivel = cJSON_GetObjectItem(item, "nivel")->valueint;
        preguntaAux.menorTiempoRespuesta = juego->tiempoRonda;
        preguntaAux.cantMenorTiempoRespuesta = 0;

        mezclarOpciones(preguntaAux.opciones, CANT_OPCIONES);

        insertarArbolBinBusq(&(juego->preguntas), &preguntaAux, sizeof(tPregunta), compararIdPregunta);
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

void realizarPregunta(void *pregunta, unsigned tamInfo, void *recurso)
{
    tPregunta *preg;
    tJuego *juego;
    tRespuesta respuesta;
    byte opcion;

    if(!pregunta || !recurso)
        return;

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

void mostrarOpcionesPreguntaConRespuestas(void *pregunta, unsigned tamInfo, void *recurso)
{
    byte opcion;
    tPregunta *preg;
    tJuego *juego;

    if(!pregunta || !recurso)
        return;

    preg = (tPregunta *) pregunta;
    juego = (tJuego *) recurso;

    fprintf(juego->salidaActual, "%d- %s", juego->rondaActual, preg->pregunta);
    for(opcion = 0; opcion < CANT_OPCIONES; opcion++)
        fprintf(juego->salidaActual, "\n\t%c) %s %s", 'A' + opcion,
                                         preg->opciones[opcion].valor,
                                         preg->opciones[opcion].valida? "(Correcta)" : "");
    fprintf(juego->salidaActual, "\n\n[Respuestas]:\n");
    mostrarRespuestasPorPregunta(preg, juego);
    fprintf(juego->salidaActual, "\n\n");
    juego->rondaActual++;
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
        return -1;
    if(!pregunta2)
        return 1;

    preg1 = (tPregunta *)pregunta1;
    preg2 = (tPregunta *)pregunta2;

    return preg1->id - preg2->id;
}

void calificarJugadorPorRespuestas(void *pregunta, unsigned tamInfo, void *recurso)
{
    tPregunta *preg;
    tJugador *jug;
    tRespuesta rta;

    if(!pregunta || !recurso)
        return;

    preg = (tPregunta *) pregunta;
    jug = (tJugador *) recurso;

    if(sacarDeCola(&(preg->respuestas), &rta, sizeof(tRespuesta)) != TODO_OK_)
        return;

    if (rta.esCorrecta)
    {
        if (rta.tiempoDeRespuesta == preg->menorTiempoRespuesta)
        {
            if(preg->cantMenorTiempoRespuesta <= 1)
            {
                rta.puntaje = PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA;
                jug->puntaje += PUNTOS_RESPUESTA_CORRECTA_UNICA_MAS_RAPIDA;
            }
            else
            {
                rta.puntaje = PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA;
                jug->puntaje += PUNTOS_RESPUESTA_CORRECTA_NO_UNICA_MAS_RAPIDA;
            }
        }
        else
        {
            rta.puntaje = PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA;
            jug->puntaje += PUNTOS_RESPUESTA_CORRECTA_MENOS_RAPIDA;
        }
    }
    else if(rta.opcion != '\0') /// si no es correcta, y además respondió algo erróneamente
    {
        rta.puntaje = PUNTOS_RESPUESTA_INCORRECTA;
        jug->puntaje += PUNTOS_RESPUESTA_INCORRECTA;
    }

    ponerEnCola(&(preg->respuestas), &rta, sizeof(rta));
}
