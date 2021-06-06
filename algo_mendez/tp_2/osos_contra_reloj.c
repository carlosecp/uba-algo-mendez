#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "osos_contra_reloj.h"
#include "tablero.h"
#include "elementos.h"

#define JUGADA_ARRIBA 'w'
#define JUGADA_ABAJO 's'
#define JUGADA_DERECHA 'd'
#define JUGADA_IZQUIERDA 'a'

const coordenada_t MOVER_ARRIBA = {1, 0};
const coordenada_t MOVER_ABAJO = {-1, 0};
const coordenada_t MOVER_DERECHA = {0, 1};
const coordenada_t MOVER_IZQUIERDA = {0, -1};

void inicializar_juego(juego_t *juego, char tipo_personaje)
{
	generar_obstaculos(juego);
	generar_personaje(&(juego->personaje), tipo_personaje);

	printf("%i", juego->cantidad_obstaculos);

	while (true)
	{
		mostrar_juego(*juego);
		char jugada;
		printf("Realizar jugada: ");
		scanf(" %c", &jugada);
		realizar_jugada(juego, jugada);
		system("clear");
	}
}

void realizar_jugada(juego_t *juego, char jugada)
{
	switch (jugada)
	{
	case JUGADA_ARRIBA:
		mover_elemento(&juego->personaje.posicion, MOVER_ARRIBA);
		break;
	case JUGADA_ABAJO:
		mover_elemento(&juego->personaje.posicion, MOVER_ABAJO);
		break;
	case JUGADA_DERECHA:
		mover_elemento(&juego->personaje.posicion, MOVER_DERECHA);
		break;
	case JUGADA_IZQUIERDA:
		mover_elemento(&juego->personaje.posicion, MOVER_IZQUIERDA);
		break;
	}

	mostrar_juego(*juego);
}

void mostrar_juego(juego_t juego)
{
	/* system("clear"); */
	char tablero[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
	llenar_tablero(tablero);

	posicionar_en_tablero(tablero, juego.personaje.posicion, juego.personaje.tipo);

	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			printf(" %c ", tablero[i][j]);
		}
		printf("\n");
	}
}