#ifndef __HERRAMIENTAS_H__
#define __HERRAMIENTAS_H__

#include "inicializar_elementos.h"

#define NINGUNA_HERRAMIENTA_EN_USO -1
#define TECLA_ENCENDER_LINTERNA LINTERNA
#define TECLA_ENCENDER_VELA VELA
#define TECLA_ENCENDER_BENGALA BENGALA

void jugada_utilizar_herramienta(juego_t *juego, char jugada);

int buscar_herramienta_en_mochila(personaje_t personaje, char tipo_herramienta);

void desactivar_herramienta(personaje_t *personaje, char tipo_herramienta);

bool herramienta_tiene_movimientos(elemento_mochila_t herramienta);

void consumir_uso_herramienta(personaje_t *personaje);

/* ==== LINTERNA ==== */

void utilizar_linterna(juego_t *juego);

void iluminar_fila(juego_t *juego, bool revertir_direccion, bool iluminar);

void iluminar_columna(juego_t *juego, bool revertir_direccion, bool iluminar);

bool fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

bool columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

#endif