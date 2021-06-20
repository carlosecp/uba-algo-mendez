#ifndef __ESTADISTICAS_H__
#define __ESTADISTICAS_H__

#include "osos_contra_reloj.h"
#include "utiles.h"
#include "herramientas.h"

void renderizar_estadisticas(juego_t juego);

void renderizar_tiempo_elapsado(personaje_t personaje);

void renderizar_ultimo_movimiento(char ultimo_movimiento);

void renderizar_mochila(personaje_t personaje);

void renderizar_gps(juego_t juego);

#endif