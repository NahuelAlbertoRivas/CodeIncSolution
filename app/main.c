#include "../env/juego.h"

int main()
{
    char estado;
    srand(time(NULL));

    printf("%d", 100 & 1);

    estado = iniciarJuego();

    return estado;
}
