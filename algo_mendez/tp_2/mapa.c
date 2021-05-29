#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "osos_contra_reloj.h"
#include "mapa.h"

coordenada_t generar_coordenada_aleatoria()
{
	srand((unsigned)time(NULL));
	int fila_generada = rand() % CANTIDAD_FILAS;
	int columna_generada = rand() % CANTIDAD_COLUMNAS;

	coordenada_t coordenada_generada = {fila_generada, columna_generada};
	return coordenada_generada;
}

void asignar_posicion_inicial(coordenada_t *elemento_a_ubicar)
{
	coordenada_t coordenada_generada = generar_coordenada_aleatoria();
	elemento_a_ubicar->fil = coordenada_generada.fil;
	elemento_a_ubicar->col = coordenada_generada.col;
}

void llenar_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS])
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			mapa[i][j] = '.';
		}
	}
}

void posicionar_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion_elemento, char representacion_elemento)
{
	mapa[posicion_elemento.fil][posicion_elemento.col] = representacion_elemento;
}

void renderizar_mapa(juego_t juego)
{
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