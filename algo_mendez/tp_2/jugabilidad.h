#ifndef __MECANICAS_H__
#define __MECANICAS_H__

#include <string.h>
#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"

#define NINGUN_ELEMENTO_EN_USO -1
#define SIN_MOVIMIENTOS ' '
#define MOVIMIENTO_INVALIDO 'X'
#define TECLA_MOVER_ARRIBA 'W'
#define TECLA_MOVER_ABAJO 'S'
#define TECLA_MOVER_DERECHA 'D'
#define TECLA_MOVER_IZQUIERDA 'A'
#define TECLA_ENCENDER_LINTERNA LINTERNA
#define TECLA_ENCENDER_VELA VELA
#define TECLA_ENCENDER_BENGALA BENGALA
#define TECLA_VER_TIEMPO_RESTANTE 'T'

static const coordenada_t MOVER_PERSONAJE_ARRIBA = {.fil = -1, .col = 0};
static const coordenada_t MOVER_PERSONAJE_ABAJO = {.fil = 1, .col = 0};
static const coordenada_t MOVER_PERSONAJE_DERECHA = {.fil = 0, .col = 1};
static const coordenada_t MOVER_PERSONAJE_IZQUIERDA = {.fil = 0, .col = -1};

/* ==== MOVIMIENTO ===== */

void jugada_movimiento(juego_t *juego, char jugada);

void mover_personaje(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento);

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada);

/* ==== HERRAMIENTAS ===== */

void jugada_utilizar_herramienta(juego_t *juego, char jugada);

int buscar_herramienta_en_mochila(personaje_t personaje, char tipo_herramienta);

bool hay_herramienta_en_uso(personaje_t personaje);

void cantidad_herramientas_disponibles(personaje_t personaje, int *cantidad_linternas, int *cantidad_velas, int *cantidad_bengalas);

void seguir_utilizando_misma_herramienta(juego_t *juego);

/* ==== HERRAMIENTAS: LINTERNA ===== */

void utilizar_linterna(juego_t *juego, bool iluminar);

void iluminar_fila(juego_t *juego, bool revertir_direccion, bool iluminar);

void iluminar_columna(juego_t *juego, bool revertir_direccion, bool iluminar);

bool fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

bool columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

/* ==== ELEMENTOS DEL MAPA ===== */

void manejar_colision(juego_t *juego);

bool es_elemento_recolectable(char tipo_elemento);

void agregar_recolectable_a_mochila(personaje_t *personaje, char tipo_recolectable);

void remover_recolectable_del_mapa(int indice_elemento, juego_t *juego);

#endif
