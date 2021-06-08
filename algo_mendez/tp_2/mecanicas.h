#ifndef __MECANICAS_H__
#define __MECANICAS_H__

#include "osos_contra_reloj.h"

#define TECLA_MOVER_ARRIBA 'w'
#define TECLA_MOVER_ABAJO 's'
#define TECLA_MOVER_DERECHA 'd'
#define TECLA_MOVER_IZQUIERDA 'a'

static const coordenada_t mover_elemento_arriba = {.fil = -1,
												   .col = 0};
static const coordenada_t mover_elemento_abajo = {.fil = 1,
												  .col = 0};
static const coordenada_t mover_elemento_derecha = {.fil = 0,
													.col = 1};
static const coordenada_t mover_elemento_izquierda = {.fil = 0,
													  .col = -1};

/** 
 * Actualiza las coordenadas actuales de un elemento del mapa segun el incremento indicado (direccion indicada).
 * @param posicion_actual Referencia a la coordenada que representa la posicion actual del elemento antes de ser movido.
 * @param direccion_movimiento Valor coordenada que indica el incremento en filas e incremento en columnas (puede ser negativo si se desea retroceder). 
*/
void mover_elemento(coordenada_t *posicion_actual, coordenada_t direccion_movimiento);

/** 
 * Compara la coordenada a la que se pretende mover el elemento para ver si esta contenida dentro del mapa.
 * @param posicion_actual Ubicacion actual del elemento que se dese mover.
 * @param direccion_movimiento Valor coordenada que indica el incremento en filas e incremento en columnas (puede ser negativo si se desea retroceder). 
 * @return Dictamina si el valor esta contenido dentro del mapa.
*/
bool es_movimiento_valido(coordenada_t posicion_actual, coordenada_t direccion_movimiento);

#endif