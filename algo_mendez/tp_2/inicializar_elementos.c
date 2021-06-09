#include "inicializar_elementos.h"
#include "osos_contra_reloj.h"
#include "mapa.h"

/* ==== PERSONAJE ===== */

personaje_t inicializar_personaje(char tipo_personaje)
{
	personaje_t personaje;

	personaje.tipo = tipo_personaje;
	personaje.posicion = generar_coordenada();
	personaje.cantidad_elementos = generar_mochila(personaje.mochila, tipo_personaje);
	personaje.elemento_en_uso = -1;
	personaje.tiempo_perdido = 0;
	personaje.ultimo_movimiento = SIMBOLO_SIN_MOVIMIENTOS;

	return personaje;
}

/* ==== MOCHILA ===== */

int generar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char tipo_personaje)
{
	int cantidad_linternas = CANTIDAD_LINTERNAS_MOCHILA;
	int cantidad_velas = tipo_personaje == POLAR ? CANTIDAD_VELAS_POLAR : CANTIDAD_VELAS_MOCHILA;
	int cantidad_bengalas = tipo_personaje == PANDA ? CANTIDAD_BENGALAS_PANDA : CANTIDAD_BENGALAS_MOCHILA;

	int tope_mochila = 0;
	agregar_herramienta_del_tipo(LINTERNA, cantidad_linternas, mochila, &tope_mochila, tipo_personaje);
	agregar_herramienta_del_tipo(VELA, cantidad_velas, mochila, &tope_mochila, tipo_personaje);
	agregar_herramienta_del_tipo(BENGALA, cantidad_bengalas, mochila, &tope_mochila, tipo_personaje);

	return tope_mochila;
}

elemento_mochila_t generar_herramienta(char tipo_herramienta, char tipo_personaje)
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

void agregar_herramienta_del_tipo(char tipo_herramienta, int cantidad_herramientas_del_tipo, elemento_mochila_t mochila[MAX_HERRAMIENTAS], int *tope_mochila, char tipo_personaje)
{
	for (int i = 0; i < cantidad_herramientas_del_tipo; i++)
	{
		mochila[(*tope_mochila)] = generar_herramienta(BENGALA, tipo_personaje);
		(*tope_mochila)++;
	}
}

/* ==== AMIGA CHLOE ===== */

coordenada_t inicializar_amiga_chloe()
{
	return generar_coordenada();
}

/* ==== OBSTACULOS && HERRAMIENTAS ===== */

void inicializar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos)
{
	(*cantidad_obstaculos) = 0;
	for (int i = 0; i < CANTIDAD_ARBOLES; i++) {
		obstaculos[(*cantidad_obstaculos)] = agregar_elemento_del_tipo(ARBOL);
		(*cantidad_obstaculos)++;
	}

	for (int i = 0; i < CANTIDAD_PIEDRAS; i++) {
		obstaculos[(*cantidad_obstaculos)] = agregar_elemento_del_tipo(PIEDRA);
		(*cantidad_obstaculos)++;
	}
}

void inicializar_herramientas(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int *cantidad_herramientas)
{
	(*cantidad_herramientas) = 0;
	for (int i = 0; i < CANTIDAD_PILAS_MAPA; i++) {
		herramientas[(*cantidad_herramientas)] = agregar_elemento_del_tipo(PILA);
		(*cantidad_herramientas)++;
	}

	for (int i = 0; i < CANTIDAD_VELAS_MAPA; i++) {
		herramientas[(*cantidad_herramientas)] = agregar_elemento_del_tipo(VELA);
		(*cantidad_herramientas)++;
	}

	for (int i = 0; i < CANTIDAD_BENGALAS_MAPA; i++) {
		herramientas[(*cantidad_herramientas)] = agregar_elemento_del_tipo(BENGALA);
		(*cantidad_herramientas)++;
	}
}

elemento_del_mapa_t agregar_elemento_del_tipo(char tipo_elemento) {
	elemento_del_mapa_t elemento_generado = {
		.posicion = generar_coordenada(),
		.tipo = tipo_elemento,
		.visible = false
	};
	return elemento_generado;
}

