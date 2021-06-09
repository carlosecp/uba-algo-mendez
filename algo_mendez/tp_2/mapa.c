#include <string.h>
#include "mapa.h"

/* ==== COORDENADAS ===== */

coordenada_t generar_coordenada() {
	int fila_aleatoria = rand() % CANTIDAD_FILAS;
	int columna_aleatoria = rand() % CANTIDAD_COLUMNAS;
	coordenada_t coordenada_aleatoria = {
		.fil = fila_aleatoria,
		.col = columna_aleatoria
	};

	return coordenada_aleatoria;
}

bool coordenadas_coinciden(coordenada_t coordenada_a, coordenada_t coordenada_b) {
	return ((coordenada_a.fil == coordenada_b.fil) &&
	(coordenada_a.col == coordenada_b.col));
}

/* ==== MAPA (TABLERO) ===== */

void inicializar_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]) {
	for (int i = 0; i < CANTIDAD_FILAS; i++) {
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++) {
			mapa[i][j] = ESPACIO_VACIO_MAPA;
		}
	}
}

void posicionar_elementos_del_juego_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego)  {
	inicializar_mapa(mapa);
	posicionar_elemento_del_tipo_en_mapa(mapa, juego.amiga_chloe, CHLOE);
	// for (int i = 0; i < juego.cantidad_obstaculos; i++) {
	// elemento_del_mapa_t obstaculo_a_posicionar = juego.obstaculos[i];
	// posicionar_elemento_del_tipo_en_mapa(mapa, obstaculo_a_posicionar.posicion, obstaculo_a_posicionar.tipo);
	// }
	// for (int i = 0; i < juego.cantidad_herramientas; i++) {
	// elemento_del_mapa_t herramienta_a_posicionar = juego.herramientas[i];
	// posicionar_elemento_del_tipo_en_mapa(mapa, herramienta_a_posicionar.posicion, herramienta_a_posicionar.tipo);
	// }
	posicionar_elemento_del_tipo_en_mapa(mapa, juego.personaje.posicion, juego.personaje.tipo);
}

void posicionar_elemento_del_tipo_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t coordenada_elemento, char tipo_elemento) {
	mapa[coordenada_elemento.fil][coordenada_elemento.col] = tipo_elemento;
}

void renderizar_bordes_mapa() {
	for (int i = 0; i < (CANTIDAD_COLUMNAS * 3); i++) {
		printf("■");
	}
	printf("\n");
}

void renderizar_estadisticas(double tiempo_actual, char *ultimo_movimiento) {
	// Ultimo movimiento, tiempo faltante
	// Cantidad herramientas, etc...
	printf(" » Segundos transcurrido: %.0fs\n", tiempo_actual);

	if ((*ultimo_movimiento) == SIMBOLO_SIN_MOVIMIENTOS) {
		printf(" » Ultimo movimiento: NO HAY MOVIMIENTOS\n");
	}
	else if ((*ultimo_movimiento) == SIMBOLO_MOVIMIENTO_INVALIDO) {
		printf(" » Ultimo movimiento: MOVIMIENTO INVALIDO\n");
	}
	else {
		mostrar_direccion_ultimo_movimiento(ultimo_movimiento);
	}
}

void mostrar_direccion_ultimo_movimiento(char *ultimo_movimiento) {
	char direccion_ultimo_movimiento[MAX_DESCRIPCION_MOVIMIENTO];

	switch(*ultimo_movimiento){
		case TECLA_MOVER_ARRIBA:
			strcpy(direccion_ultimo_movimiento, DESCRIPCION_MOVIMIENTO_ARRIBA);
			break;
		case TECLA_MOVER_ABAJO:
			strcpy(direccion_ultimo_movimiento, DESCRIPCION_MOVIMIENTO_ABAJO);
			break;
		case TECLA_MOVER_DERECHA:
			strcpy(direccion_ultimo_movimiento, DESCRIPCION_MOVIMIENTO_DERECHA);
			break;
		case TECLA_MOVER_IZQUIERDA:
			strcpy(direccion_ultimo_movimiento, DESCRIPCION_MOVIMIENTO_IZQUIERDA);
			break;
	}

	printf(" » Ultimo movimiento: %s\n", direccion_ultimo_movimiento);
}
