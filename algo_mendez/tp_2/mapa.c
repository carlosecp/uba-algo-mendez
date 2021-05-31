#include <stdio.h>
#include <stdlib.h>
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

void mover_elemento(coordenada_t *posicion_actual, int incremento_fila, int incremento_columna)
{
	posicion_actual->fil -= incremento_fila;
	posicion_actual->col -= incremento_columna;
}