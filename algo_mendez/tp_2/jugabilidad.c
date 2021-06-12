#include "jugabilidad.h"

void mover_elemento(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento)
{
	coordenada_t coordenada_objetivo = {
			.fil = coordenada_actual->fil + direccion_movimiento.fil,
			.col = coordenada_actual->col + direccion_movimiento.col};

	if (coordenada_esta_en_el_mapa(coordenada_objetivo))
	{
		coordenada_actual->fil = coordenada_objetivo.fil;
		coordenada_actual->col = coordenada_objetivo.col;
	}
}

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada)
{
	return ((coordenada_buscada.fil >= 0) && (coordenada_buscada.fil < CANTIDAD_FILAS)) && ((coordenada_buscada.col >= 0) && (coordenada_buscada.col < CANTIDAD_COLUMNAS));
}

/* ==== JUGADAS ===== */

void jugada_movimiento(juego_t *juego, char jugada)
{
	switch (jugada)
	{
	case TECLA_MOVER_ARRIBA:
		mover_elemento(&(juego->personaje.posicion), MOVER_ELEMENTO_ARRIBA);
		break;
	case TECLA_MOVER_ABAJO:
		mover_elemento(&(juego->personaje.posicion), MOVER_ELEMENTO_ABAJO);
		break;
	case TECLA_MOVER_DERECHA:
		mover_elemento(&(juego->personaje.posicion), MOVER_ELEMENTO_DERECHA);
		break;
	case TECLA_MOVER_IZQUIERDA:
		mover_elemento(&(juego->personaje.posicion), MOVER_ELEMENTO_IZQUIERDA);
		break;
	}
}