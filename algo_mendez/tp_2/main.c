#include <stdlib.h>
#include <stdio.h>

#include "osos_contra_reloj.h"
#include "mapa.h"

int main()
{
	coordenada_t coordenada = generar_coordenada_aleatoria();

	personaje_t personaje;
	personaje.posicion = coordenada;
	personaje.tipo = 'X';

	juego_t juego;
	juego.personaje = personaje;

	while (true)
	{
		char jugada;
		printf("Presione una tecla: ");
		scanf(" %c", &jugada);
		realizar_jugada(&juego, jugada);
	}

	return 0;
}
