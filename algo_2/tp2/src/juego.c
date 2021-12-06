#include "juego.h"

void inicializar_juego(Juego* juego, hospital_t* hospital) {
	if (!juego || !hospital)
		return;

    juego->simulador = simulador_crear(hospital);
    juego->jugando = true;
}

void terminar_juego(Juego* juego) {
	if (!juego)
		return;

	juego->jugando = false;
}

void destruir_juego(Juego juego) {
	simulador_destruir(juego.simulador);
}
