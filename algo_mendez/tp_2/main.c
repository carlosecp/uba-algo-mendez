#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "osos_contra_reloj.h"

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

void dibujar_tablero()
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			printf(" . ");
		}
		printf("\n");
	}
}

coordenada_t generar_coordenada()
{
	srand((unsigned)time(NULL));
	int fila = rand() % CANTIDAD_FILAS;
	int columna = rand() % CANTIDAD_COLUMNAS;

	return (coordenada_t){fila, columna};
}

void ubicar_personaje(juego_t *juego)
{
	coordenada_t coordenada_personaje = generar_coordenada();
}

void inicializar_juego(juego_t *juego, char tipo_personaje)
{
}

int main()
{
	personaje_t Carlos;
	Carlos.tipo = 'C';

	dibujar_tablero();
	return 0;
}