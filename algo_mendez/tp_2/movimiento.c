#include "movimiento.h"

/* ==== DESPLAZAMIENTO ===== */

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

/* ==== COLISIONES ==== */

void manejar_colision(juego_t *juego)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->obstaculos[i].posicion))
		{
			accion_colision_con_obstaculo(juego, juego->obstaculos[i].tipo);
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

void accion_colision_con_obstaculo(juego_t *juego, char tipo_obstaculo)
{
	float tiempo_perdido_arbol = juego->personaje.tipo == PARDO ? TIEMPO_PERDIDO_ARBOL_PARDO : TIEMPO_PERDIDO_ARBOL;
	float tiempo_perdido_piedra = juego->personaje.tipo == POLAR ? TIEMPO_PERDIDO_PIEDRA_POLAR : TIEMPO_PERDIDO_PIEDRA;

	if ((juego->personaje.tipo == PANDA) && (tipo_obstaculo == ARBOL) && !(juego->chloe_visible))
	{
		juego->chloe_visible = true;
	}

	switch (tipo_obstaculo)
	{
	case ARBOL:
		juego->personaje.tiempo_perdido += tiempo_perdido_arbol;
		break;
	case PIEDRA:
		juego->personaje.tiempo_perdido += tiempo_perdido_piedra;
		break;
	case KOALA:
		juego->personaje.posicion = generar_coordenada_colision_koala();
		break;
	}
}

/* ==== RECOLECCIÓN DE HERRAMIENTAS ==== */

void accion_colision_con_herramienta(juego_t *juego, int indice_herramienta)
{
	char tipo_herramienta = juego->herramientas[indice_herramienta].tipo;
	switch (tipo_herramienta)
	{
	case PILA:
		agregar_pilas_a_linterna(juego, indice_herramienta);
		break;
	default:
		agregar_herramienta_a_mochila(&(juego->personaje), tipo_herramienta);
		remover_herramienta_del_mapa(juego, indice_herramienta);
	}
}

void agregar_herramienta_a_mochila(personaje_t *personaje, char tipo_herramienta)
{
	if (personaje->cantidad_elementos < MAX_HERRAMIENTAS)
	{
		agregar_multiples_herramientas_del_tipo_a_mochila(tipo_herramienta, 1, personaje->mochila, &(personaje->cantidad_elementos), personaje->tipo);
	}
}

void remover_herramienta_del_mapa(juego_t *juego, int indice_herramienta)
{
	for (int i = indice_herramienta; i < juego->cantidad_herramientas; i++)
	{
		juego->herramientas[i] = juego->herramientas[i + 1];
	}
	juego->cantidad_herramientas--;
}

void agregar_pilas_a_linterna(juego_t *juego, int indice_pila)
{
	int indice_linterna = buscar_herramienta_en_mochila(juego->personaje, LINTERNA);
	int maximas_pilas_linterna = juego->personaje.tipo == PARDO ? DURACION_LINTERNA_PARDO : DURACION_LINTERNA;

	if ((juego->personaje.mochila[indice_linterna].movimientos_restantes + DURACION_PILA) <= maximas_pilas_linterna)
	{
		juego->personaje.mochila[indice_linterna].movimientos_restantes += DURACION_PILA;
		remover_herramienta_del_mapa(juego, indice_pila);
	}
}