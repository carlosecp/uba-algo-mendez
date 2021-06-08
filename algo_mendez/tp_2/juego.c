#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "osos_contra_reloj.h"
#include "mapa.h"

int main()
{
	// system("clear");
	srand((unsigned)time(NULL));

	juego_t juego;
	char tipo_personaje = 'X';

	inicializar_juego(&juego, tipo_personaje);

	return 0;
}
