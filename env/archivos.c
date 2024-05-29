#include "archivos.h"

char abrirArchivo(FILE** archivoAAbrir, const char* nombreArchivo, const char* modoApertura)
{
    if((*archivoAAbrir = fopen(nombreArchivo, modoApertura)) == NULL)
    {
        perror("No se pudo abrir/crear el archivo");
        return FILE_ERR;
    }

    return OK;
}

char leerArchivoConfig(tJuego* juego)
{
    FILE* archConfig;
    char linea[MAX_LINEA_CONFIG];

    if(abrirArchivo(&archConfig, "config.txt", "rt") != OK)
        return FILE_ERR;

    if(fgets(linea, MAX_LINEA_CONFIG, archConfig))
        sscanf(linea, "Rounds: %d", &juego->cantRondas);

    if(fgets(linea, MAX_LINEA_CONFIG, archConfig))
        sscanf(linea, "Tiempo por round: %d", &juego->tiempoRonda);

    fclose(archConfig);

    if(juego->cantRondas < MIN_RONDAS ||
            juego->cantRondas > MAX_RONDAS ||
            juego->tiempoRonda < MIN_TIEMPO_RONDA)
        return ERROR_PARAMETROS;

    return OK;
}

char imprimirResultados(tJuego* juego)
{
    FILE* archInforme;
    char estado,
         nombreArch[TAM_NOMBRE_INFORME];
    time_t tiempoTranscurrido;
    struct tm* fechaHora;

    tiempoTranscurrido = time(NULL);
    fechaHora = localtime(&tiempoTranscurrido);

    snprintf(nombreArch, sizeof(nombreArch),
             "../logs/informe-juego_%4d-%02d-%02d-%02d-%02d.txt",
             fechaHora->tm_year + 1900,
             fechaHora->tm_mon + 1,
             fechaHora->tm_mday,
             fechaHora->tm_hour,
             fechaHora->tm_min);

    if((estado = abrirArchivo(&archInforme, nombreArch, "wt") != OK))
        return estado;

    juego->salidaActual = archInforme;
    generarImpresion(juego);

    fclose(archInforme);

    mostrarResultadosPorConsola(nombreArch);

    return OK;
}

void generarImpresion(tJuego* juego)
{
    tJugador puntajeMaximo;
    byte cantGanadores;

    juego->rondaActual = 1;
    recorrerEnOrdenSimpleArbolBinBusq(&(juego->preguntas), juego, mostrarOpcionesPreguntaConRespuestas);
    fprintf(juego->salidaActual, "Total\n");
    mapLista(&(juego->jugadores), mostrarPuntajesTotales, juego);
    cantGanadores = buscarMayorElemNoClaveLista(&(juego->jugadores), &puntajeMaximo, sizeof(tJugador), compararPuntaje);
    juego->puntajeMaximo = puntajeMaximo.puntaje;
    fprintf(juego->salidaActual, "\n¡¡Felicitaciones %s!!:\n", cantGanadores == 1? "ganador/a" : "ganadoras/es");
    mapLista(&(juego->jugadores), mostrarSiEsGanador, juego);
}

/// (recordemos que la cola tiene las respuestas respectivamente a como están los jugadores en la lista)
/// fn para mapear lista de jugadores
int mostrarJugadorRespuesta(void *jugador, void *recurso)
{
    tJugador *jug;
    tRespuesta rta;
    tAuxResumenFinal *recursoResumen;

    if(!jugador || !recurso)
        return -32;

    recursoResumen = (tAuxResumenFinal *) recurso;
    jug = (tJugador *)jugador;

    if(sacarDeCola(&(recursoResumen->preg->respuestas), &rta, sizeof(tRespuesta)) == TODO_OK_)
    {
        calificarJugadorPorRespuestas(jug, recursoResumen->preg, &rta);
        if(rta.opcion) /// significa que el jugador respondió algo -bien o mal-
            fprintf(recursoResumen->juego->salidaActual, "%s: %d %s en contestar\t %c (%s%d)\n", jug->nombre,
                                                                                 rta.tiempoDeRespuesta,
                                                                                 rta.tiempoDeRespuesta == 1?"segundo":"segundos",
                                                                                 rta.opcion,
                                                                                 rta.puntaje > 0 ? "+" : "",
                                                                                 rta.puntaje);
        else /// el jugador no respondió nada
            fprintf(recursoResumen->juego->salidaActual, "%s: No contesta\t0 puntos\n", jug->nombre);
    }

    return TODO_OK;
}

void mostrarResultadosPorConsola(char *nombreArch)
{
    FILE *pf = fopen(nombreArch, "rt");
    char linea[TAM_MAX_LECTURA];

    if(!pf)
    {
        printf("\nInforme no disponible.\n");
        return;
    }

    while(fgets(linea, TAM_MAX_LECTURA, pf))
        fprintf(stdout, "%s", linea);

    fclose(pf);
}
