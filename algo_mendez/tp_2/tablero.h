#ifndef __TABLERO_H__
#define __TABLERO_H__

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

typedef struct tablero
{
	char casillas[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
} tablero_t;

bool coordenada_esta_ocupada(tablero_t tablero, coordenada_t coordernada_a_buscar);

coordenada_t generar_coordernada_aleatoria();

void inicializar_tablero(tablero_t *tablero);

void imprimir_tablero(tablero_t tablero);

#endif /* TABLERO_H */