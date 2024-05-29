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
        crearArbolBinBusq(&(juego.preguntas));
        crearLista(&(juego.jugadores));
        if((estado = configurarJuego(&juego)) != OK)
            return estado;
        mostrarOrdenJuego(&juego);
        printf("\n[Detalles]\nCantidad de rondas: %d\nTiempo por ronda: %d\nTendrán un lapso de 7 segundos para prepararse antes de iniciar\n\n¡Éxitos a todos!\n\nPor favor, ingresen cualquier tecla para continuar",
                          juego.cantRondas,     juego.tiempoRonda);
        getch();
        system("cls");
        fflush(stdin);
        recorrerEnOrdenSimpleArbolBinBusq(&(juego.preguntas), &juego, crearColaRespuestas);
        iniciarTrivia(&juego);
        /// mapLista(&(juego.jugadores), calcularPuntajePorJugador, &juego);
        estado = imprimirResultados(&juego);
        vaciarLista(&(juego.jugadores));
        recorrerEnOrdenSimpleArbolBinBusq(&(juego.preguntas), &juego, liberarColaRespuestas);
        eliminarArbol(&(juego.preguntas));
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

    cargarJugadores(juego);
    if(juego->cantJugadores == 0)
        return SIN_JUGADORES;

    elegirDificultad(juego);

    if ((estado = cargarCURL(&cURL)) != OK)
        return estado;

    ///TODO: chequear las siguientes 3 lineas
    //    if((estado = verificarConectividad(&cURL)) != OK ){
    //        return estado;
    //    }

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

    fprintf(stdout, "Ingrese la dificultad deseada:\n");
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
    recorrerEnOrdenSimpleArbolBinBusq(&(juego->preguntas), juego, inicializarMenorTiempoPreguntas);

    mapLista(&(juego->jugadores), mostrarPreguntasAlJugador, juego);

    puts("¡Juego terminado! Ingresen cualquier tecla para ver los resultados");
    getch();
    system("cls");
}

int mostrarPreguntasAlJugador(void *jugador, void *recurso)
{
    tJugador *jug;
    tJuego *juego;

    if(!jugador || !recurso)
        return -32;

    juego = (tJuego *) recurso;
    jug = (tJugador *)jugador;

    juego->rondaActual = 1;

    system("cls");
    printf("Preparate %s, en 7 segundos comienza tu turno\n",
                jug->nombre);
    fflush(stdin); /// por si anteriormente ingresaron enter, ya que esta última tecla tiene doble acción sobre el buffer
    sleep(7);
    system("cls");
    printf("[Tu turno %s]", jug->nombre);

    recorrerEnOrdenSimpleArbolBinBusq((&juego->preguntas), juego, realizarPregunta);

    printf("\n\nFin de tu turno %s, ingresá cualquier tecla para continuar", jug->nombre);
    getch();
    fflush(stdin);
    system("cls");

    return TODO_OK;
}
