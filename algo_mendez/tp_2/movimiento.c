#include "movimiento.h"

/* ==== MOVIMIENTO ===== */

void jugada_movimiento(juego_t *juego, char jugada)
{
	juego->personaje.ultimo_movimiento = jugada;
	switch (jugada)
	{
	case TECLA_MOVER_ARRIBA:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_ARRIBA);
		break;
	case TECLA_MOVER_ABAJO:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_ABAJO);
		break;
	case TECLA_MOVER_DERECHA:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_DERECHA);
		break;
	case TECLA_MOVER_IZQUIERDA:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_IZQUIERDA);
		break;
	}

	manejar_colision(juego);
	utilizar_misma_herramienta(juego);
}

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

void manejar_colision(juego_t *juego)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->obstaculos[i].posicion))
		{
			accion_colision_con_obstaculo(&(juego->personaje), juego->obstaculos[i].tipo);
		}
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->herramientas[i].posicion))
		{
			accion_colision_con_herramienta(juego, i);
		}
	}
}

void accion_colision_con_obstaculo(personaje_t *personaje, char tipo_obstaculo)
{
	float tiempo_perdido_arbol = personaje->tipo == PARDO ? TIEMPO_PERDIDO_ARBOL_PARDO : TIEMPO_PERDIDO_ARBOL;
	float tiempo_perdido_piedra = personaje->tipo == POLAR ? TIEMPO_PERDIDO_PIEDRA_POLAR : TIEMPO_PERDIDO_PIEDRA;

	switch (tipo_obstaculo)
	{
	case ARBOL:
		personaje->tiempo_perdido += tiempo_perdido_arbol;
		break;
	case PIEDRA:
		personaje->tiempo_perdido += tiempo_perdido_piedra;
		break;
	case KOALA:
		personaje->posicion = generar_coordenada_impacto_koala();
		break;
	}
}

void accion_colision_con_herramienta(juego_t *juego, int indice_recolectable)
{
	char tipo_recolectable = juego->herramientas[indice_recolectable].tipo;
	switch (tipo_recolectable)
	{
	case PILA:
		agregar_pilas_a_linterna(juego, indice_recolectable);
		break;
	default:
		agregar_recolectable_a_mochila(&(juego->personaje), tipo_recolectable);
		remover_recolectable_del_mapa(juego, indice_recolectable);
	}
}

void agregar_recolectable_a_mochila(personaje_t *personaje, char tipo_recolectable)
{
	if (personaje->cantidad_elementos < MAX_HERRAMIENTAS)
	{
		agregar_herramienta_del_tipo_a_mochila(tipo_recolectable, 1, personaje->mochila, &(personaje->cantidad_elementos), personaje->tipo);
	}
}

void remover_recolectable_del_mapa(juego_t *juego, int indice_herramienta)
{
	for (int i = indice_herramienta; i < juego->cantidad_herramientas; i++)
	{
		juego->herramientas[i] = juego->herramientas[i + 1];
	}
	juego->cantidad_herramientas--;
}