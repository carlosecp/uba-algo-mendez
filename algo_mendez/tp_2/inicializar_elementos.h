#ifndef __INICIALIZAR_ELEMENTOS_H__
#define __INICIALIZAR_ELEMENTOS_H__

#include "osos_contra_reloj.h"

#define POLAR 'I'
#define PARDO 'G'
#define PANDA 'P'
#define CHLOE 'C'
#define KOALAS 'K'

#define LINTERNA 'L'
#define VELA 'V'
#define BENGALA 'E'
#define ARBOL 'A'
#define PIEDRA 'R'
#define PILA 'B'

#define DURACION_LINTERNA 10
#define DURACION_LINTERNA_PARDO 15
#define DURACION_VELA 5
#define DURACION_BENGALA 3

#define CANTIDAD_LINTERNAS_MOCHILA 1
#define CANTIDAD_VELAS_MOCHILA 4
#define CANTIDAD_VELAS_POLAR 6
#define CANTIDAD_BENGALAS_MOCHILA 0
#define CANTIDAD_BENGALAS_PANDA 2

#define CANTIDAD_ARBOLES 350
#define CANTIDAD_PIEDRAS 80
#define CANTIDAD_PILAS_MAPA 30
#define CANTIDAD_VELAS_MAPA 30
#define CANTIDAD_BENGALAS_MAPA 10

typedef struct coordenadas_a_validar
{
	bool personaje;
	bool chloe;
	bool obstaculos;
	bool herramientas;
} coordenadas_a_validar_t;

personaje_t inicializar_personaje(juego_t juego, char tipo_personaje);

int generar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char tipo_personaje);

elemento_mochila_t generar_herramienta(char tipo_herramienta, char tipo_personaje);

void agregar_herramienta_del_tipo(char tipo_herramienta, int cantidad_herramientas_del_tipo, elemento_mochila_t mochila[MAX_HERRAMIENTAS], int *tope_mochila, char tipo_personaje);

coordenada_t inicializar_amiga_chloe(juego_t juego);

void inicializar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos);

void inicializar_herramientas(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int *cantidad_herramientas);

elemento_del_mapa_t agregar_elemento_del_tipo(char tipo_obstaculo);
#endif
