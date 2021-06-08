#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"

void inicializar_juego(juego_t *juego, char tipo_personaje) {
	juego->personaje = inicializar_personaje(tipo_personaje);
	juego->amiga_chloe = inicializar_amiga_chloe();
	inicializar_obstaculos(juego->obstaculos, &(juego->cantidad_obstaculos));
	inicializar_herramientas(juego->herramientas, &(juego->cantidad_herramientas));

	while(estado_juego(*juego) == 0) {
		char jugada;
		printf("Registrar jugada: ");
		scanf(" %c", &jugada);
	}
}

int estado_juego(juego_t juego) {
	return coordenadas_coinciden(juego.personaje.posicion, juego.amiga_chloe) ? -1 : 0;
}

void realizar_jugada(juego_t *juego, char jugada) {

}

void mostrar_juego(juego_t juego) {
	char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
	posicionar_elementos_del_juego_en_mapa(mapa, juego);

	for (int i = 0; i < CANTIDAD_FILAS; i++) {
		for (int j = 0; j < CANTIDAD_COLUMNAS; j++) {
			printf(" %c ", mapa[i][j]);
		}
		printf("\n");
	}
}

bool es_jugada_valida(char jugada) {
	return true;
}
