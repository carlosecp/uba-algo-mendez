#ifndef __MOVIMIENTO_H__
#define __MOVIMIENTO_H__

#include <string.h>
#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"

#define SIN_MOVIMIENTOS ' '
#define MOVIMIENTO_INVALIDO 'X'
#define TECLA_MOVER_ARRIBA 'W'
#define TECLA_MOVER_ABAJO 'S'
#define TECLA_MOVER_DERECHA 'D'
#define TECLA_MOVER_IZQUIERDA 'A'
#define TECLA_VER_TIEMPO_RESTANTE 'T'

static const coordenada_t MOVER_PERSONAJE_ARRIBA = {.fil = -1, .col = 0};
static const coordenada_t MOVER_PERSONAJE_ABAJO = {.fil = 1, .col = 0};
static const coordenada_t MOVER_PERSONAJE_DERECHA = {.fil = 0, .col = 1};
static const coordenada_t MOVER_PERSONAJE_IZQUIERDA = {.fil = 0, .col = -1};

void jugada_movimiento(juego_t *juego, char jugada);

void mover_personaje(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento);

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada);

void manejar_colision(juego_t *juego);

void agregar_recolectable_a_mochila(personaje_t *personaje, char tipo_recolectable);

void remover_recolectable_del_mapa(int indice_elemento, juego_t *juego);

#endif