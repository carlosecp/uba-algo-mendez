#include <stdlib.h>
#include <stdio.h>
#include "osos_contra_reloj.h"
#include "elementos_mapa.h"
#include "mapa.h"
#include "mecanicas.h"

#define CONTINUAR_JUEGO 0

void inicializar_juego(juego_t *juego, char tipo_personaje)
{
	generar_personaje(&(juego->personaje), tipo_personaje, *juego);
	generar_obstaculos(juego->obstaculos, &(juego->cantidad_obstaculos), *juego);

	char jugada;
	while (true)
	{
		system("clear");
		mostrar_juego(*juego);

		printf("Realizar jugada: ");
		scanf(" %c", &jugada);

		realizar_jugada(juego, jugada);
	}
}

int estado_juego(juego_t juego)
{
	return CONTINUAR_JUEGO;
}

void realizar_jugada(juego_t *juego, char jugada)
{
	coordenada_t direccion_movimiento = {.fil = 0,
		.col = 0};
	switch (jugada)
	{
		case TECLA_MOVER_ARRIBA:
			direccion_movimiento = mover_elemento_arriba;
			break;
		case TECLA_MOVER_ABAJO:
			direccion_movimiento = mover_elemento_abajo;
			break;
		case TECLA_MOVER_DERECHA:
			direccion_movimiento = mover_elemento_derecha;
			break;
		case TECLA_MOVER_IZQUIERDA:
			direccion_movimiento = mover_elemento_izquierda;
			break;
	}

	if (es_jugada_valida(jugada))
	mover_elemento(&(juego->personaje.posicion), direccion_movimiento);
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
	return ((jugada == TECLA_MOVER_ARRIBA) ||
	(jugada == TECLA_MOVER_ABAJO) ||
	(jugada == TECLA_MOVER_DERECHA) ||
	(jugada == TECLA_MOVER_IZQUIERDA));
}
