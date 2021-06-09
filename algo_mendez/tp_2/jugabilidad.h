#ifndef __MECANICAS_H__
#define __MECANICAS_H__

#include "osos_contra_reloj.h"

#define TECLA_MOVER_ARRIBA 'w'
#define TECLA_MOVER_ABAJO 's'
#define TECLA_MOVER_DERECHA 'd'
#define TECLA_MOVER_IZQUIERDA 'a'
#define SIMBOLO_SIN_MOVIMIENTOS ' '
#define SIMBOLO_MOVIMIENTO_INVALIDO 'x'

#define MAX_DESCRIPCION_MOVIMIENTO 10
#define DESCRIPCION_MOVIMIENTO_ARRIBA "Arriba"
#define DESCRIPCION_MOVIMIENTO_ABAJO "Abajo"
#define DESCRIPCION_MOVIMIENTO_DERECHA "Derecha"
#define DESCRIPCION_MOVIMIENTO_IZQUIERDA "Izquierda"

static const coordenada_t MOVER_ELEMENTO_ARRIBA = {.fil = -1, .col = 0};
static const coordenada_t MOVER_ELEMENTO_ABAJO = {.fil = 1, .col = 0};
static const coordenada_t MOVER_ELEMENTO_DERECHA = {.fil = 0, .col = 1};
static const coordenada_t MOVER_ELEMENTO_IZQUIERDA = {.fil = 0, .col = -1};

void mover_elemento(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento);

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada);

#endif
