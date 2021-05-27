#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "osos_contra_reloj.h"
#include "tablero.h"

bool coordenada_esta_ocupada(tablero_t tablero, coordenada_t coordernada_a_buscar)
{
	int fila = coordernada_a_buscar.fil;
	int columna = coordernada_a_buscar.col;

	return tablero.casillas[fila][columna] != -1;
}

coordenada_t generar_coordernada_aleatoria()
{
	srand((unsigned)time(NULL));
	int nueva_fila = rand() % CANTIDAD_FILAS;
	int nueva_columna = rand() % CANTIDAD_COLUMNAS;

	coordenada_t coordenada_generada = {nueva_fila, nueva_columna};
	return coordenada_generada;
}

void inicializar_tablero(tablero_t *tablero)
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			tablero->casillas[i][j] = '.';
		}
	}
}

void imprimir_tablero(tablero_t tablero)
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			printf("%i", tablero.casillas[i][j]);
		}
	}
}