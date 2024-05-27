#include "../env/juego.h"

int main()
{
    char estado;
    srand(time(NULL));

    estado = iniciarJuego();

    return estado;
}
