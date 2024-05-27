#include "pregunta.h"
#include "juego.h"

void parsearPregunta(char* json, void* preguntas)
{

    cJSON* json_array = cJSON_Parse(json);
    cJSON* item;
    tPregunta* preguntaAux;
    int i;
    int cantPreguntas;

    cantPreguntas = cJSON_GetArraySize(json_array);
    preguntaAux = (tPregunta*) preguntas;
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

        strcpy(preguntaAux->id, cJSON_GetObjectItem(item, "id")->valuestring);
        strcpy(preguntaAux->pregunta, cJSON_GetObjectItem(item, "pregunta")->valuestring);
        strcpy(preguntaAux->opciones[0].valor, cJSON_GetObjectItem(item, "resp_correcta")->valuestring);
        preguntaAux->opciones[0].valida = 1;
        strcpy(preguntaAux->opciones[1].valor, cJSON_GetObjectItem(item, "opcion_1")->valuestring);
        preguntaAux->opciones[1].valida = 0;
        strcpy(preguntaAux->opciones[2].valor, cJSON_GetObjectItem(item, "opcion_2")->valuestring);
        preguntaAux->opciones[2].valida = 0;
        strcpy(preguntaAux->opciones[3].valor, cJSON_GetObjectItem(item, "opcion_3")->valuestring);
        preguntaAux->opciones[3].valida = 0;
        preguntaAux->nivel = cJSON_GetObjectItem(item, "nivel")->valueint;

        mezclarOpciones(preguntaAux->opciones, CANT_OPCIONES);

        preguntaAux++;
    }

    cJSON_Delete(json_array);
}

void mezclarPreguntas(void* preguntas, int cantPreguntas)
{
    int i;
    int j;

    for(i = cantPreguntas - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        if (i != j)
            intercambiarPreguntas(&((tPregunta*)preguntas)[i],
                                  &((tPregunta*)preguntas)[j]);
    }
}

void intercambiarPreguntas(tPregunta* preguntaA, tPregunta* preguntaB)
{
    tPregunta temp;

    memcpy(&temp, preguntaA, sizeof(tPregunta));
    memcpy(preguntaA, preguntaB, sizeof(tPregunta));
    memcpy(preguntaB, &temp, sizeof(tPregunta));
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

void realizarPregunta(tJuego* juego, int jugador, int rondaActual)
{
    char opciones[CANT_OPCIONES][TAM_OPCION],
         opcion,
         menorTiempo,
         tiempoDeRespuesta,
         respuesta;

    menorTiempo = juego->tiempoRonda;

    for (opcion = 0; opcion < CANT_OPCIONES; opcion++)
        printf("%c- %s\n", 'A' + opcion, juego->preguntas[rondaActual].opciones[(unsigned)opcion].valor);
    printf("Respuesta: ");
    tiempoDeRespuesta = iniciarTemporizador(&respuesta, juego->tiempoRonda);

    procesarRespuesta(juego, jugador, rondaActual, opciones, respuesta, menorTiempo, tiempoDeRespuesta);
}

void procesarRespuesta(tJuego* juego, int jugador, int rondaActual,
                       char opciones[][TAM_OPCION], char respuesta,
                       int menorTiempo, int tiempoDeRespuesta)
{
    if(respuesta == '\0')
        juego->jugadores[jugador].respuestas[rondaActual].esCorrecta = 0;
    else
    {
        respuesta = islower(respuesta) ? toupper(respuesta) : respuesta;
        juego->jugadores[jugador].respuestas[rondaActual].esCorrecta = juego->preguntas[rondaActual].opciones[respuesta - 'A'].valida;
    }

    if(juego->menorTiempoRespuesta[rondaActual] > tiempoDeRespuesta && juego->jugadores[jugador].respuestas[rondaActual].esCorrecta)
        juego->menorTiempoRespuesta[rondaActual] = tiempoDeRespuesta;

    juego->jugadores[jugador].respuestas[rondaActual].tiempoDeRespuesta = tiempoDeRespuesta;
    juego->jugadores[jugador].respuestas[rondaActual].opcion = respuesta;
    juego->jugadores[jugador].respuestas[rondaActual].puntaje = 0;
}
