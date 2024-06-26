#include "juego.h"
#include "archivos.h"
#include "../userHandler/jugador.h"
#include "../apiConfigs/curlReducido.h"

char mostrarMenu()
{
    char opcion;

    do
    {
        puts("Bienvenido al juego:");
        puts("[A] Jugar");
        puts("[B] Salir");
        printf("Ingrese su opción: ");
        fflush(stdin);
        scanf("%c", &opcion);
        system("cls");
        printf("Opción no válida. Por favor, ingrese A o B.\n");
    }
    while(toupper(opcion) != 'B' && toupper(opcion) != 'A');

    system("cls");

    return toupper(opcion);
}

char iniciarJuego()
{
    tJuego juego;
    char opcion,
         estado;

    opcion = mostrarMenu();

    switch(opcion)
    {
    case 'A':
        crearLista(&(juego.preguntas));
        crearLista(&(juego.jugadores));
        if((estado = configurarJuego(&juego)) != OK)
            return estado;
        mostrarOrdenJuego(&juego);
        printf("\n[Detalles]\nCantidad de rondas: %d\nTiempo por ronda: %d\n\n¡Éxitos a todos!\n\nPor favor, ingresen cualquier tecla para continuar",
                          juego.cantRondas,     juego.tiempoRonda);
        getch();
        system("cls");
        fflush(stdin);
        mapLista(&(juego.preguntas), crearColaRespuestas, &juego);
        iniciarTrivia(&juego);
        estado = imprimirResultados(&juego);
        vaciarLista(&(juego.jugadores));
        mapLista(&(juego.preguntas), liberarColaRespuestas, &juego);
        vaciarLista(&(juego.preguntas));
        return estado;
    case 'B':
        printf("¡Hasta luego!\n");
        break;
    }

    return OK;
}

int configurarJuego(tJuego* juego)
{
    CURL* cURL;
    int estado;

    if((estado = leerArchivoConfig(juego)) != OK)
        return estado;

    juego->cantJugadores = 0;
    cargarJugadores(juego);
    if(juego->cantJugadores == 0)
        return SIN_JUGADORES;

    elegirDificultad(juego);

    if ((estado = cargarCURL(&cURL)) != OK)
        return estado;

    if(cURL)
        estado = obtenerPreguntas(&cURL, juego, juego->dificultad, juego->cantRondas);

    liberarCurl(&cURL);

    return estado;
}

void elegirDificultad(tJuego* juego)
{
    int i;
    char dificultad;
    tMapeoDificultad mapeo[] =
    {
        {"FACIL", FACIL},
        {"MEDIO", MEDIO},
        {"DIFICIL", DIFICIL}
    };

    fprintf(stdout, "Ingresá la dificultad deseada:\n");
    for(i = 0; i < sizeof(mapeo) / sizeof(tMapeoDificultad); i ++)
        printf("%2c: %15s\n", mapeo[i].nombre[0], mapeo[i].nombre);
    dificultad = captarIngresoDificultad(mapeo, sizeof(mapeo) / sizeof(tMapeoDificultad));

    for (i = 0; i < sizeof(mapeo) / sizeof(mapeo[0]); ++i)
    {
        if (dificultad == mapeo[i].nombre[0])
        {
            juego->dificultad = mapeo[i].valor;
            system("cls");
            return;
        }
    }
}

void mezclar(void* item, int cantElementos, void(*mezclarImpl)(void*, int))
{
    mezclarImpl(item, cantElementos);
}

void mostrarOrdenJuego(tJuego* juego)
{
    byte i = 1;

    puts("¡Fue sorteado el orden en que jugarán! La disposición es la siguiente\n");
    mapLista(&(juego->jugadores), mostrarOrdenJugador, &i);
}

void iniciarTrivia(tJuego* juego)
{
    mapLista(&(juego->preguntas), inicializarMenorTiempoPreguntas, juego);

    mapLista(&(juego->jugadores), mostrarPreguntasAlJugador, juego);

    puts("¡Juego terminado! Ingresen cualquier tecla para ver los resultados");
    ingresoNoRequerido(CLEAN_BUFFER);
    system("cls");
}
