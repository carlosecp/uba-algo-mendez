#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"
#include "utiles.h"
#include "jugabilidad.h"

void inicializar_juego(juego_t *juego, char tipo_personaje) {
	juego->personaje = inicializar_personaje(tipo_personaje);
	juego->amiga_chloe = inicializar_amiga_chloe();
	inicializar_obstaculos(juego->obstaculos, &(juego->cantidad_obstaculos));
	inicializar_herramientas(juego->herramientas, &(juego->cantidad_herramientas));

	iniciar_cronometro();

	while(estado_juego(*juego) == 0) {
		system("clear");
		mostrar_juego(*juego);
		char jugada;
		printf(" » Registrar jugada: ");
		scanf(" %c", &jugada);
		realizar_jugada(juego, jugada);
	}
}

int estado_juego(juego_t juego) {
	return coordenadas_coinciden(juego.personaje.posicion, juego.amiga_chloe) ? -1 : 0;
}

void realizar_jugada(juego_t *juego, char jugada) {
	if (es_jugada_valida(jugada)) {
		coordenada_t direccion_movimiento = {
			.fil = 0,
			.col = 0
		};
		switch (jugada) {
			case TECLA_MOVER_ARRIBA:
				direccion_movimiento = MOVER_ELEMENTO_ARRIBA;
				break;
			case TECLA_MOVER_ABAJO:
				direccion_movimiento = MOVER_ELEMENTO_ABAJO;
				break;
			case TECLA_MOVER_DERECHA:
				direccion_movimiento = MOVER_ELEMENTO_DERECHA;
				break;
			case TECLA_MOVER_IZQUIERDA:
				direccion_movimiento = MOVER_ELEMENTO_IZQUIERDA;
				break;
		}
		juego->personaje.ultimo_movimiento = jugada;
		mover_elemento(&(juego->personaje.posicion), direccion_movimiento);
	}
	else {
		juego->personaje.ultimo_movimiento = SIMBOLO_MOVIMIENTO_INVALIDO;
	}
}

void mostrar_juego(juego_t juego) {
	char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
	posicionar_elementos_del_juego_en_mapa(mapa, juego);

	renderizar_bordes_mapa();
	renderizar_estadisticas(tiempo_actual(), &(juego.personaje.ultimo_movimiento));
	renderizar_bordes_mapa();
	for (int i = 0; i < CANTIDAD_FILAS; i++) {
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++) {
			printf(" %c ", mapa[i][j]);
		}
		printf("\n");
	}
	renderizar_bordes_mapa();
}

bool es_jugada_valida(char jugada) {
	return ((jugada == TECLA_MOVER_ARRIBA) ||
	(jugada == TECLA_MOVER_ABAJO) ||
	(jugada == TECLA_MOVER_DERECHA) ||
	(jugada == TECLA_MOVER_IZQUIERDA));
}
