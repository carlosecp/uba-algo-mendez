#ifndef __MAPA_H__
#define __MAPA_H__

#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "jugabilidad.h"

#define CANTIDAD_FILAS 5
#define CANTIDAD_COLUMNAS 5

#define ESPACIO_VACIO_MAPA '.'

coordenada_t generar_coordenada(juego_t juego, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe);

bool es_coordenada_ocupada(juego_t juego, coordenada_t coordenada_buscada, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe);

bool coordenada_coincide_con_elemento(juego_t juego, coordenada_t coordenada_buscada);

bool son_misma_coordenada(coordenada_t coordenada_a, coordenada_t coordenada_b);

void inicializar_mapa_vacio(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);

void posicionar_todos_elementos_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego);

void posicionar_personaje_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], personaje_t personaje);

void posicionar_amiga_chloe_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t amiga_chloe);

void posicionar_elemento_del_tipo_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], elemento_del_mapa_t elemento_a_posicionar);

void renderizar_bordes_mapa();

void renderizar_estadisticas(double tiempo_actual, char *ultimo_movimiento);

void mostrar_direccion_ultimo_movimiento(char *ultimo_movimiento);

#endif
