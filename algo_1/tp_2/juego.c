#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "estadisticas.h"
#include "mapa.h"
#include "test_de_personalidad.h"

int main()
{
	system("clear");
	srand((unsigned)time(NULL));

	juego_t juego;
	char tipo_personaje;
	test_de_personalidad(&tipo_personaje);
	inicializar_juego(&juego, tipo_personaje);

	while (estado_juego(juego) == 0)
	{
		system("clear");
		mostrar_juego(juego);
		char jugada;
		printf(" -> Registrar jugada: ");
		scanf(" %c", &jugada);
		realizar_jugada(&juego, jugada);
	}

	renderizar_resultados_juego(juego);

	return 0;
}
