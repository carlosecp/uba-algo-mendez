#ifndef __MAPA_H__
#define __MAPA_H__

#include "osos_contra_reloj.h"

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

#define ESPACIO_VACIO_MAPA '.'

coordenada_t generar_coordenada();

bool coordenadas_coinciden(coordenada_t coordenada_a, coordenada_t coordenada_b);

void inicializar_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);

void posicionar_elementos_del_juego_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego);

void posicionar_elemento_del_tipo_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t coordenada_elemento, char tipo_elemento);

void renderizar_bordes_mapa();

void renderizar_estadisticas(double tiempo_actual, char ultimo_movimiento);

#endif
