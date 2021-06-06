#ifndef __ELEMENTOS_H__
#define __ELEMENTOS_H__

#include "osos_contra_reloj.h"

#define CANTIDAD_ARBOLES 350
#define CANTIDAD_PIEDRAS 80

#define ARBOL 'A'
#define PIEDRA 'R'
#define KOALAS 'K'
#define LINTERNA 'L'
#define VELA 'V'
#define BENGALA 'E'
#define PILA 'B'

void generar_personaje(personaje_t *personaje, char tipo_personaje);

void generar_obstaculos(juego_t *juego);

void llenar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS]);

#endif
