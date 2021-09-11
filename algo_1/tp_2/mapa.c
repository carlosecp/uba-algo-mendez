#include <string.h>
#include "mapa.h"

/* ==== COORDENADAS ==== */

coordenada_t generar_coordenada(juego_t juego, bool posicion_inicial_personaje, bool validar_coordenada, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe)
{
	int fila_aleatoria = rand() % CANTIDAD_FILAS;
	int columna_aleatoria = posicion_inicial_personaje ? 0 : rand() % CANTIDAD_COLUMNAS;
	coordenada_t coordenada_aleatoria = {
			.fil = fila_aleatoria,
			.col = columna_aleatoria};

	if (validar_coordenada && es_coordenada_ocupada(juego, coordenada_aleatoria, validar_coordenada_personaje, validar_coordenada_amiga_chloe))
	{
		return generar_coordenada(juego, posicion_inicial_personaje, validar_coordenada, validar_coordenada_personaje, validar_coordenada_amiga_chloe);
	}

	return coordenada_aleatoria;
}

bool es_coordenada_ocupada(juego_t juego, coordenada_t coordenada_buscada, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe)
{
	bool coordenada_ocupada = false;

	if (validar_coordenada_personaje && son_misma_coordenada(coordenada_buscada, juego.personaje.posicion))
		coordenada_ocupada = true;

	if (validar_coordenada_amiga_chloe && son_misma_coordenada(coordenada_buscada, juego.amiga_chloe))
		coordenada_ocupada = true;

	for (int i = 0; i < juego.cantidad_obstaculos; i++)
	{
		if (son_misma_coordenada(coordenada_buscada, juego.obstaculos[i].posicion))
			coordenada_ocupada = true;
	}

	for (int i = 0; i < juego.cantidad_herramientas; i++)
	{
		if (son_misma_coordenada(coordenada_buscada, juego.herramientas[i].posicion))
			coordenada_ocupada = true;
	}

	return coordenada_ocupada;
}

bool son_misma_coordenada(coordenada_t coordenada_a, coordenada_t coordenada_b)
{
	return ((coordenada_a.fil == coordenada_b.fil) &&
					(coordenada_a.col == coordenada_b.col));
}

/* ==== MAPA (BOSQUE) ==== */

void inicializar_mapa_vacio(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS])
{
	for (int i = 0; i < CANTIDAD_FILAS; i++)
	{
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			mapa[i][j] = ESPACIO_VACIO_MAPA;
		}
	}
}

void posicionar_todos_elementos_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego)
{
	inicializar_mapa_vacio(mapa);
	posicionar_amiga_chloe_en_mapa_aux(mapa, juego.amiga_chloe, juego.chloe_visible);

	for (int i = 0; i < juego.cantidad_obstaculos; i++)
	{
		elemento_del_mapa_t obstaculo_a_posicionar = juego.obstaculos[i];
		posicionar_elemento_del_tipo_en_mapa_aux(mapa, obstaculo_a_posicionar);
	}

	for (int i = 0; i < juego.cantidad_herramientas; i++)
	{
		elemento_del_mapa_t herramienta_a_posicionar = juego.herramientas[i];
		posicionar_elemento_del_tipo_en_mapa_aux(mapa, herramienta_a_posicionar);
	}

	posicionar_personaje_en_mapa_aux(mapa, juego.personaje);
}

/* ===== AUXILIARES ==== */

void posicionar_personaje_en_mapa_aux(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], personaje_t personaje)
{
	mapa[personaje.posicion.fil][personaje.posicion.col] = personaje.tipo;
}

void posicionar_amiga_chloe_en_mapa_aux(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t amiga_chloe, bool amiga_chloe_es_visible)
{
	if (amiga_chloe_es_visible)
	{
		mapa[amiga_chloe.fil][amiga_chloe.col] = CHLOE;
	}
}

void posicionar_elemento_del_tipo_en_mapa_aux(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], elemento_del_mapa_t elemento_a_posicionar)
{
	if (elemento_a_posicionar.visible)
	{
		mapa[elemento_a_posicionar.posicion.fil][elemento_a_posicionar.posicion.col] = elemento_a_posicionar.tipo;
	}
}

coordenada_t generar_coordenada_colision_koala()
{
	int fila_aleatoria = rand() % CANTIDAD_FILAS;
	coordenada_t coordenada_aleatoria = {
			.fil = fila_aleatoria,
			.col = 0};

	return coordenada_aleatoria;
}
