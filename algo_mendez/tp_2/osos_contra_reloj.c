#include <stdlib.h>
#include <stdio.h>
#include "osos_contra_reloj.h"
#include "elementos_mapa.h"
#include "mapa.h"

#define CONTINUAR_JUEGO 0

void inicializar_juego(juego_t *juego, char tipo_personaje)
{
	generar_personaje(&(juego->personaje), tipo_personaje);
	generar_obstaculos(juego->obstaculos, &(juego->cantidad_obstaculos));

	coordenada_esta_ocupada(juego->personaje.posicion, *juego);

	char jugada;
	while (true)
	{
		mostrar_juego(*juego);
		printf("Realizar jugada: ");
		scanf(" %c", &jugada);
	}
}

int estado_juego(juego_t juego)
{
	return CONTINUAR_JUEGO;
}

void realizar_jugada(juego_t *juego, char jugada)
{
}

void mostrar_juego(juego_t juego)
{
	char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
	preparar_mapa_para_renderizado(mapa, juego);

	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			printf(" %c ", mapa[i][j]);
		}
		printf("\n");
	}
}

bool es_jugada_valida(char jugada)
{
	return true;
}
