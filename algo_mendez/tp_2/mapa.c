#include <string.h>
#include "mapa.h"

/* ==== COORDENADAS ===== */

coordenada_t generar_coordenada(juego_t juego, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe)
{
	int fila_aleatoria = rand() % CANTIDAD_FILAS;
	int columna_aleatoria = rand() % CANTIDAD_COLUMNAS;
	coordenada_t coordenada_aleatoria = {
			.fil = fila_aleatoria,
			.col = columna_aleatoria};

	if (es_coordenada_ocupada(juego, coordenada_aleatoria, validar_coordenada_personaje, validar_coordenada_amiga_chloe))
		return generar_coordenada(juego, validar_coordenada_personaje, validar_coordenada_amiga_chloe);

	return coordenada_aleatoria;
}

bool es_coordenada_ocupada(juego_t juego, coordenada_t coordenada_buscada, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe)
{
	bool coordenada_ocupada = false;

	if (validar_coordenada_personaje)
		coordenada_ocupada = son_misma_coordenada(coordenada_buscada, juego.personaje.posicion);

	if (validar_coordenada_amiga_chloe)
		coordenada_ocupada = son_misma_coordenada(coordenada_buscada, juego.amiga_chloe);

	for (int i = 0; i < juego.cantidad_obstaculos; i++)
		coordenada_ocupada = son_misma_coordenada(coordenada_buscada, juego.obstaculos[i].posicion);

	for (int i = 0; i < juego.cantidad_herramientas; i++)
		coordenada_ocupada = son_misma_coordenada(coordenada_buscada, juego.herramientas[i].posicion);

	return coordenada_ocupada;
}

bool son_misma_coordenada(coordenada_t coordenada_a, coordenada_t coordenada_b)
{
	return ((coordenada_a.fil == coordenada_b.fil) &&
					(coordenada_a.col == coordenada_b.col));
}

/* ==== MAPA (BOSQUE) ===== */

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
	posicionar_personaje_en_mapa(mapa, juego.personaje);
	posicionar_amiga_chloe_en_mapa(mapa, juego.amiga_chloe);

	for (int i = 0; i < juego.cantidad_obstaculos; i++)
	{
		elemento_del_mapa_t obstaculo_a_posicionar = juego.obstaculos[i];
		posicionar_elemento_del_tipo_en_mapa(mapa, obstaculo_a_posicionar);
	}

	for (int i = 0; i < juego.cantidad_herramientas; i++)
	{
		elemento_del_mapa_t herramienta_a_posicionar = juego.herramientas[i];
		posicionar_elemento_del_tipo_en_mapa(mapa, herramienta_a_posicionar);
	}
}

/* ==== AUXILIARES POSICIONAMIENTO DE ELEMENTOS ===== */

void posicionar_personaje_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], personaje_t personaje)
{
	mapa[personaje.posicion.fil][personaje.posicion.col] = personaje.tipo;
}

void posicionar_amiga_chloe_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t amiga_chloe)
{
	mapa[amiga_chloe.fil][amiga_chloe.col] = CHLOE;
}

void posicionar_elemento_del_tipo_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], elemento_del_mapa_t elemento_a_posicionar)
{
	if (elemento_a_posicionar.visible)
	{
		mapa[elemento_a_posicionar.posicion.fil][elemento_a_posicionar.posicion.col] = elemento_a_posicionar.tipo;
	}
}

/* ==== EXTRA (DECORACIONES) ===== */

void renderizar_bordes_mapa()
{
	for (int i = 0; i < (CANTIDAD_COLUMNAS * 3); i++)
	{
		printf("■");
	}
	printf("\n");
}
