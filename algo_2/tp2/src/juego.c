#include "juego.h"

void inicializar_juego(Juego* juego, hospital_t* hospital) {
    juego->simulador = simulador_crear(hospital);
    juego->jugando = true;
}

void destruir_juego(Juego juego) {
	simulador_destruir(juego.simulador);
}
