#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "osos_contra_reloj.h"
#include "tablero.h"

bool coordenada_esta_ocupada(juego_t juego, coordenada_t coordernada_a_buscar)
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
				}
	}
}

coordenada_t generar_coordenada_aleatoria()
{
	srand((unsigned)time(NULL));
	int nueva_fila = rand() % CANTIDAD_FILAS;
	int nueva_columna = rand() % CANTIDAD_COLUMNAS;

	coordenada_t coordenada_generada = {nueva_fila, nueva_columna};
	return coordenada_generada;
}

void ubicar_en_tablero(personaje_t *personaje)
{
	coordenada_t nueva_coordenada = generar_coordenada_aleatoria();
	personaje->posicion = nueva_coordenada;
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
			printf(" %c ", tablero.casillas[i][j]);
		}
		printf("\n");
	}
}