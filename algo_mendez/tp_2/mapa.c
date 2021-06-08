#include <stdlib.h>
#include <stdbool.h>
#include "osos_contra_reloj.h"
#include "mapa.h"

coordenada_t generar_coordenada(juego_t juego)
{
	int fila = rand() % CANTIDAD_FILAS;
	int columna = rand() % CANTIDAD_COLUMNAS;
	coordenada_t nueva_coordenada = {
		.fil = fila,
		.col = columna};

	if (!es_coordenada_ocupada(nueva_coordenada, juego))
		return nueva_coordenada;

	generar_coordenada(juego);
}

bool son_misma_coordenada(coordenada_t coordenada_a, coordenada_t coordenada_b)
{
	return ((coordenada_a.fil == coordenada_b.fil) &&
			(coordenada_a.col == coordenada_b.col));
}

bool es_coordenada_ocupada(coordenada_t coordenada_buscada, juego_t juego)
{
	bool coordenada_ocupada = false;

	if (son_misma_coordenada(coordenada_buscada, juego.amiga_chloe))
		coordenada_ocupada = true;

	int i = 0;
	while (!coordenada_ocupada && (i < juego.cantidad_obstaculos))
	{
		coordenada_t coordenada_obstaculo = juego.obstaculos[i].posicion;
		if (son_misma_coordenada(coordenada_buscada, coordenada_obstaculo))
			coordenada_ocupada = true;

		juego.cantidad_obstaculos--;
		i++;
	}

	return coordenada_ocupada;
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

void preparar_mapa_para_renderizado(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego)
{
	llenar_mapa(mapa);
	posicionar_en_mapa(mapa, juego.personaje.posicion, juego.personaje.tipo);
	for (int i = 0; i < MAX_OBSTACULOS; i++)
	{
		posicionar_en_mapa(mapa, juego.obstaculos[i].posicion, juego.obstaculos[i].tipo);
	}
}

void posicionar_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion_elemento, char tipo_elemento)
{
	mapa[posicion_elemento.fil][posicion_elemento.col] = tipo_elemento;
}