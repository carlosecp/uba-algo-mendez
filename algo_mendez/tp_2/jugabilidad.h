#ifndef __MECANICAS_H__
#define __MECANICAS_H__

#include "osos_contra_reloj.h"

#define TECLA_MOVER_ARRIBA 'w'
#define TECLA_MOVER_ABAJO 's'
#define TECLA_MOVER_DERECHA 'd'
#define TECLA_MOVER_IZQUIERDA 'a'

static const coordenada_t mover_elemento_arriba = {.fil = -1, .col = 0};
static const coordenada_t mover_elemento_abajo = {.fil = 1, .col = 0};
static const coordenada_t mover_elemento_derecha = {.fil = 0, .col = 1};
static const coordenada_t mover_elemento_izquierda = {.fil = 0, .col = -1};

#endif
