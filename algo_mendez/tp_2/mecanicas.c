#include <stdlib.h>

#include "osos_contra_reloj.h"
#include "mecanicas.h"
#include "mapa.h"

void mover_elemento(coordenada_t *posicion_actual, coordenada_t direccion_movimiento)
{
	if (es_movimiento_valido(*posicion_actual, direccion_movimiento))
	{
		posicion_actual->fil += direccion_movimiento.fil;
		posicion_actual->col += direccion_movimiento.col;
	}
}

bool es_movimiento_valido(coordenada_t posicion_actual, coordenada_t direccion_movimiento)
{
	int fila_objetivo = (posicion_actual.fil + direccion_movimiento.fil);
	int columna_objetivo = (posicion_actual.col + direccion_movimiento.col);

	return ((fila_objetivo >= 0 && fila_objetivo < CANTIDAD_FILAS) &&
			(columna_objetivo >= 0 && columna_objetivo < CANTIDAD_COLUMNAS));
}