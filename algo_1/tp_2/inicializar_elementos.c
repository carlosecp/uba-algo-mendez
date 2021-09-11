#include "inicializar_elementos.h"

/* ==== PERSONAJE ===== */

personaje_t inicializar_personaje(juego_t juego, char tipo_personaje)
{
	personaje_t personaje;

	personaje.tipo = tipo_personaje;
	personaje.posicion = generar_coordenada_personaje_aux(juego);
	personaje.cantidad_elementos = generar_mochila(personaje.mochila, tipo_personaje);
	personaje.elemento_en_uso = NINGUNA_HERRAMIENTA_EN_USO;
	personaje.tiempo_perdido = 0;
	personaje.ultimo_movimiento = TECLA_MOVER_DERECHA;

	return personaje;
}

/* ==== MOCHILA ===== */

int generar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char tipo_personaje)
{
	int cantidad_linternas = CANTIDAD_LINTERNAS_MOCHILA;
	int cantidad_velas = tipo_personaje == POLAR ? CANTIDAD_VELAS_POLAR : CANTIDAD_VELAS_MOCHILA;
	int cantidad_bengalas = tipo_personaje == PANDA ? CANTIDAD_BENGALAS_PANDA : CANTIDAD_BENGALAS_MOCHILA;

	int tope_mochila = 0;

	agregar_multiples_herramientas_del_tipo_a_mochila(LINTERNA, cantidad_linternas, mochila, &tope_mochila, tipo_personaje);

	agregar_multiples_herramientas_del_tipo_a_mochila(VELA, cantidad_velas, mochila, &tope_mochila, tipo_personaje);

	agregar_multiples_herramientas_del_tipo_a_mochila(BENGALA, cantidad_bengalas, mochila, &tope_mochila, tipo_personaje);

	return tope_mochila;
}

void agregar_multiples_herramientas_del_tipo_a_mochila(char tipo_herramienta, int cantidad_herramientas_del_tipo, elemento_mochila_t mochila[MAX_HERRAMIENTAS], int *tope_mochila, char tipo_personaje)
{
	for (int i = 0; i < cantidad_herramientas_del_tipo; i++)
	{
		mochila[(*tope_mochila)] = generar_una_herramienta_mochila(tipo_herramienta, tipo_personaje);
		(*tope_mochila)++;
	}
}

elemento_mochila_t generar_una_herramienta_mochila(char tipo_herramienta, char tipo_personaje)
{
	int movimientos_restantes;

	switch (tipo_herramienta)
	{
	case LINTERNA:
		movimientos_restantes = tipo_personaje == PARDO ? DURACION_LINTERNA_PARDO : DURACION_LINTERNA;
		break;
	case VELA:
		movimientos_restantes = DURACION_VELA;
		break;
	case BENGALA:
		movimientos_restantes = DURACION_BENGALA;
		break;
	}

	elemento_mochila_t herramienta = {
			.tipo = tipo_herramienta,
			.movimientos_restantes = movimientos_restantes};

	return herramienta;
}

/* ==== AMIGA CHLOE ==== */

coordenada_t inicializar_amiga_chloe(juego_t *juego)
{
	juego->chloe_visible = false;
	return generar_coordenada_amiga_chloe_aux(*juego);
}

/* ==== OBSTACULOS ==== */

void inicializar_obstaculos(juego_t *juego)
{
	juego->cantidad_obstaculos = 0;
	for (int i = 0; i < CANTIDAD_ARBOLES; i++)
	{
		juego->obstaculos[juego->cantidad_obstaculos] = agregar_elemento_del_tipo(*juego, ARBOL);
		juego->cantidad_obstaculos++;
	}

	for (int i = 0; i < CANTIDAD_PIEDRAS; i++)
	{
		juego->obstaculos[juego->cantidad_obstaculos] = agregar_elemento_del_tipo(*juego, PIEDRA);
		juego->cantidad_obstaculos++;
	}

	agregar_koala_nom_nom(juego);
}

void agregar_koala_nom_nom(juego_t *juego)
{
	juego->obstaculos[juego->cantidad_obstaculos] = agregar_elemento_del_tipo(*juego, KOALA);
	juego->cantidad_obstaculos++;
}

/* ==== HERRAMIENTAS ==== */

void inicializar_herramientas(juego_t *juego)
{
	juego->cantidad_herramientas = 0;
	for (int i = 0; i < CANTIDAD_PILAS_MAPA; i++)
	{
		juego->herramientas[juego->cantidad_herramientas] = agregar_elemento_del_tipo(*juego, PILA);
		juego->cantidad_herramientas++;
	}

	for (int i = 0; i < CANTIDAD_VELAS_MAPA; i++)
	{
		juego->herramientas[juego->cantidad_herramientas] = agregar_elemento_del_tipo(*juego, VELA);
		juego->cantidad_herramientas++;
	}

	for (int i = 0; i < CANTIDAD_BENGALAS_MAPA; i++)
	{
		juego->herramientas[juego->cantidad_herramientas] = agregar_elemento_del_tipo(*juego, BENGALA);
		juego->cantidad_herramientas++;
	}
}

elemento_del_mapa_t agregar_elemento_del_tipo(juego_t juego, char tipo_elemento)
{
	elemento_del_mapa_t elemento_generado = {
			.posicion = generar_coordenada_elemento_aux(juego),
			.tipo = tipo_elemento,
			.visible = false};

	return elemento_generado;
}

/* ==== AUXILIARES ===== */

coordenada_t generar_coordenada_personaje_aux(juego_t juego)
{
	return generar_coordenada(juego, true, false, false, false);
}

coordenada_t generar_coordenada_amiga_chloe_aux(juego_t juego)
{
	return generar_coordenada(juego, false, true, true, false);
}

coordenada_t generar_coordenada_elemento_aux(juego_t juego)
{
	return generar_coordenada(juego, false, true, true, true);
}
