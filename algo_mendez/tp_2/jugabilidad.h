#ifndef __MECANICAS_H__
#define __MECANICAS_H__

#include <string.h>
#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"

#define MOVIMIENTO_INVALIDO 'X'
#define TECLA_MOVER_ARRIBA 'W'
#define TECLA_MOVER_ABAJO 'S'
#define TECLA_MOVER_DERECHA 'D'
#define TECLA_MOVER_IZQUIERDA 'A'
#define TECLA_ENCENDER_LINTERNA LINTERNA
#define TECLA_ENCENDER_VELA VELA
#define TECLA_ENCENDER_BENGALA BENGALA
#define TECLA_VER_TIEMPO_RESTANTE 'T'

static const coordenada_t mover_personaje_ARRIBA = {.fil = -1, .col = 0};
static const coordenada_t mover_personaje_ABAJO = {.fil = 1, .col = 0};
static const coordenada_t mover_personaje_DERECHA = {.fil = 0, .col = 1};
static const coordenada_t mover_personaje_IZQUIERDA = {.fil = 0, .col = -1};

void mover_personaje(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento);

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada);

void jugada_movimiento(juego_t *juego, char jugada);

void manejar_colision(juego_t *juego);

void jugada_encender_linterna(juego_t *juego);

void iluminar_fila(juego_t *juego, bool revertir_direccion);

void iluminar_columna(juego_t *juego, bool revertir_direccion);

bool fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

bool columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

#endif
