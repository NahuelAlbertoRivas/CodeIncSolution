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

char imprimirResultados(const tJuego* juego)
{
    FILE* archInforme;
    char estado;
    time_t tiempoTranscurrido;
    struct tm* fechaHora;
    char nombreArch[TAM_NOMBRE_INFORME];

    generarImpresion(stdout, juego);

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

    generarImpresion(archInforme, juego);

    fclose(archInforme);

    return OK;
}

void generarImpresion(FILE* salida, const tJuego* juego)
{
    int ronda;
    int jugador;
    int puntajeMaximo;

    calcularPuntajeMaximo(juego->jugadores, &puntajeMaximo, juego->cantJugadores);

    for (ronda = 0; ronda < juego->cantRondas; ronda++)
    {
        fprintf(salida, "%d- %s\n\tA) %s %s\n\tB) %s %s\n\tC) %s %s\n\tD) %s %s\n\n[Respuestas]:\n",
                ronda + 1, juego->preguntas[ronda].pregunta,
                juego->preguntas[ronda].opciones[0].valor,
                juego->preguntas[ronda].opciones[0].valida? "(Correcta)" : "",
                juego->preguntas[ronda].opciones[1].valor,
                juego->preguntas[ronda].opciones[1].valida? "(Correcta)" : "",
                juego->preguntas[ronda].opciones[2].valor,
                juego->preguntas[ronda].opciones[2].valida? "(Correcta)" : "",
                juego->preguntas[ronda].opciones[3].valor,
                juego->preguntas[ronda].opciones[3].valida? "(Correcta)" : "");

        for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        {
            if(juego->jugadores[jugador].respuestas[ronda].opcion != 0)
            {
                fprintf(salida, "%s: %d %s en contestar\t %c (%s%d)\n",
                        juego->jugadores[jugador].nombre,
                        juego->jugadores[jugador].respuestas[ronda].tiempoDeRespuesta,
                        juego->jugadores[jugador].respuestas[ronda].tiempoDeRespuesta == 1?"segundo":"segundos",
                        juego->jugadores[jugador].respuestas[ronda].opcion,
                        juego->jugadores[jugador].respuestas[ronda].puntaje > 0 ? "+" : "",
                        juego->jugadores[jugador].respuestas[ronda].puntaje);
            }
            else
                fprintf(salida, "%s: No contesta\t0 puntos\n", juego->jugadores[jugador].nombre);
        }
        fprintf(salida, "\n\n");
    }

    fprintf(salida, "Total\n");
    for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        fprintf(salida, "\t%s:\t%3d %s\n",
                juego->jugadores[jugador].nombre,
                juego->jugadores[jugador].puntaje,
                juego->jugadores[jugador].puntaje == 1 || juego->jugadores[jugador].puntaje == -1?"punto":"puntos");

    fprintf(salida, "\nGanador/es:\n");
    for (jugador = 0; jugador < juego->cantJugadores; jugador++)
        if (juego->jugadores[jugador].puntaje == puntajeMaximo)
            fprintf(salida, "\t%s\n", juego->jugadores[jugador].nombre);
}

void calcularPuntajeMaximo(const tJugador* jugadores, int* puntajeMaximo, int cantJugadores)
{
    int jugador;

    *puntajeMaximo = jugadores[0].puntaje;

    for (jugador = 1; jugador < cantJugadores; jugador++)
        if (jugadores[jugador].puntaje > *puntajeMaximo)
            *puntajeMaximo = jugadores[jugador].puntaje;
}
