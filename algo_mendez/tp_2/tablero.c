#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "osos_contra_reloj.h"
#include "tablero.h"

coordenada_t generar_coordenada_aleatoria()
{
	srand((unsigned)time(NULL));
	int fila_generada = rand() % CANTIDAD_FILAS;
	int columna_generada = rand() % CANTIDAD_COLUMNAS;

	coordenada_t coordenada_generada = {fila_generada, columna_generada};
	return coordenada_generada;
}

void llenar_tablero(char tablero[CANTIDAD_FILAS][CANTIDAD_COLUMNAS])
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			tablero[i][j] = '.';
		}
	}
}

void posicionar_en_tablero(char tablero[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion_elemento, char representacion_elemento)
{
	tablero[posicion_elemento.fil][posicion_elemento.col] = representacion_elemento;
}

void mover_elemento(coordenada_t *posicion_actual, coordenada_t incremento_coordenadas)
{
	posicion_actual->fil -= incremento_coordenadas.fil;
	posicion_actual->col += incremento_coordenadas.col;
}

bool coordenada_esta_ocupada(coordenada_t coordenada_buscada)
{
	/* coordenada_t coordenadas_obstaculos[MAX_OBSTACULOS];
	coordenada_t coordenadas_herramientas[MAX_HERRAMIENTAS]; */

	return true;
}