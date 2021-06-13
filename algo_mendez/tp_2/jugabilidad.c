#include "jugabilidad.h"

void mover_personaje(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento)
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
		mover_personaje(&(juego->personaje.posicion), mover_personaje_ARRIBA);
		break;
	case TECLA_MOVER_ABAJO:
		mover_personaje(&(juego->personaje.posicion), mover_personaje_ABAJO);
		break;
	case TECLA_MOVER_DERECHA:
		mover_personaje(&(juego->personaje.posicion), mover_personaje_DERECHA);
		break;
	case TECLA_MOVER_IZQUIERDA:
		mover_personaje(&(juego->personaje.posicion), mover_personaje_IZQUIERDA);
		break;
	}

	manejar_colision(juego);
}

void manejar_colision(juego_t *juego)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->obstaculos[i].posicion))
		{
			// tipo_elemento_colision = juego->obstaculos[i].tipo;
		}
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->herramientas[i].posicion))
		{
			// tipo_elemento_colision = juego->herramientas[i].tipo;
		}
	}
}

bool es_elemento_recolectable(char tipo_elemento)
{
	return ((tipo_elemento == VELA) ||
					(tipo_elemento == BENGALA) ||
					(tipo_elemento == PILA));
}

void agregar_recolectable_a_mochila(personaje_t *personaje, char tipo_recolectable)
{
	// if (cantidad_herramientas < MAX_HERRAMIENTAS)
	// {
	// 	agregar_herramienta_del_tipo_a_mochila(tipo_recolectable, 1, personaje->mochila, &(personaje->cantidad_elementos), personaje->tipo);
	// }
}

void jugada_encender_linterna(juego_t *juego)
{
	switch (juego->personaje.ultimo_movimiento)
	{
	case TECLA_MOVER_ARRIBA:
		iluminar_columna(juego, false);
		break;
	case TECLA_MOVER_ABAJO:
		iluminar_columna(juego, true);
		break;
	case TECLA_MOVER_DERECHA:
		iluminar_fila(juego, false);
		break;
	case TECLA_MOVER_IZQUIERDA:
		iluminar_fila(juego, true);
		break;
	}

	agregar_koala_nom_nom(juego);
}

/* ==== INTERACCION DEL PERSONAJE CON ELEMENTOS DEL MAPA ==== */

/* ==== AUXILIARES ILUMINACION RENGLONES ===== */

void iluminar_fila(juego_t *juego, bool revertir_direccion)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (fila_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion, revertir_direccion))
		{
			juego->obstaculos[i].visible = true;
		}
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (fila_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion, revertir_direccion))
		{
			juego->herramientas[i].visible = true;
		}
	}
}

void iluminar_columna(juego_t *juego, bool revertir_direccion)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (columna_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion, revertir_direccion))
		{
			juego->obstaculos[i].visible = true;
		}
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (columna_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion, revertir_direccion))
		{
			juego->herramientas[i].visible = true;
		}
	}
}

bool fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion)
{
	if (!revertir_direccion)
	{
		return ((posicion_elemento.col > posicion_personaje.col) && (posicion_elemento.fil == posicion_personaje.fil));
	}

	return ((posicion_elemento.col < posicion_personaje.col) && (posicion_elemento.fil == posicion_personaje.fil));
}

bool columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion)
{
	if (!revertir_direccion)
	{
		return ((posicion_elemento.fil < posicion_personaje.fil) && (posicion_elemento.col == posicion_personaje.col));
	}

	return ((posicion_elemento.fil > posicion_personaje.fil) && (posicion_elemento.col == posicion_personaje.col));
}