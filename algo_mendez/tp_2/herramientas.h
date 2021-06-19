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

#endif