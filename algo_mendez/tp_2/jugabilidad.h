#ifndef __MECANICAS_H__
#define __MECANICAS_H__

#include "osos_contra_reloj.h"
#include "mapa.h"

#define TECLA_MOVER_ARRIBA 'w'
#define TECLA_MOVER_ABAJO 's'
#define TECLA_MOVER_DERECHA 'd'
#define TECLA_MOVER_IZQUIERDA 'a'
#define TECLA_ENCENDER_LINTERNA 'l'
#define TECLA_ENCENDER_VELA 'v'
#define TECLA_VER_TIEMPO_RESTANTE 't'

#define SIMBOLO_SIN_MOVIMIENTOS ' '
#define SIMBOLO_MOVIMIENTO_INVALIDO 'x'

static const coordenada_t MOVER_ELEMENTO_ARRIBA = {.fil = -1, .col = 0};
static const coordenada_t MOVER_ELEMENTO_ABAJO = {.fil = 1, .col = 0};
static const coordenada_t MOVER_ELEMENTO_DERECHA = {.fil = 0, .col = 1};
static const coordenada_t MOVER_ELEMENTO_IZQUIERDA = {.fil = 0, .col = -1};

void mover_elemento(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento);

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada);

void jugada_movimiento(juego_t *juego, char jugada);

void jugada_encender_linterna(juego_t *juego);

void iluminar_renglon_arriba_aux(juego_t *juego);

void iluminar_renglon_abajo_aux(juego_t *juego);

void iluminar_renglon_derecha_aux(juego_t *juego);

void iluminar_renglon_izquierda_aux(juego_t *juego);

#endif
