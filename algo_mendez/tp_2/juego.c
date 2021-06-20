#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "estadisticas.h"
#include "mapa.h"

int main()
{
	system("clear");
	renderizar_introduccion();

	srand((unsigned)time(NULL));
	juego_t juego;
	char tipo_personaje = PARDO;
	inicializar_juego(&juego, tipo_personaje);

	return 0;
}
