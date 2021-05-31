#include <stdlib.h>
#include <stdio.h>
#include "osos_contra_reloj.h"
#include "mapa.h"

#define MOVER_ARRIBA 'w'
#define MOVER_ABAJO 's'
#define MOVER_DERECHA 'd'
#define MOVER_IZQUIERDA 'a'

void realizar_jugada(juego_t *juego, char jugada)
{
	switch (jugada)
	{
	case MOVER_ARRIBA:
		mover_elemento(&juego->personaje.posicion, 1, 0);
		break;
	case MOVER_ABAJO:
		mover_elemento(&juego->personaje.posicion, -1, 0);
		break;
	case MOVER_DERECHA:
		mover_elemento(&juego->personaje.posicion, 0, -1);
		break;
	case MOVER_IZQUIERDA:
		mover_elemento(&juego->personaje.posicion, 0, 1);
		break;
	}

	mostrar_juego(*juego);
}

void mostrar_juego(juego_t juego)
{
	system("clear");
	char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
	llenar_mapa(mapa);

	posicionar_en_mapa(mapa, juego.personaje.posicion, juego.personaje.tipo);

	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			printf(" %c ", mapa[i][j]);
		}
		printf("\n");
	}
}