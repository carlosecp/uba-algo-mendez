#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "osos_contra_reloj.h"

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

coordenada_t generar_coordenada_aleatoria();

void llenar_tablero(char tablero[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);

void posicionar_en_tablero(char tablero[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion_elemento, char representacion_elemento);

void mover_elemento(coordenada_t *posicion_actual, coordenada_t incremento_coordenadas);

bool coordenada_esta_ocupada(coordenada_t coordenada_buscada);

#endif