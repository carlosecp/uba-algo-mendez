#include "juego.h"

#include <stdio.h>

void juego_inicializar(Juego* juego, hospital_t* hospital) {
	if (!juego || !hospital)
		return;

	// TODO: Verificar la creacion del simulador
    juego->simulador = simulador_crear(hospital);
    juego->jugando = true;

	// simulador_simular_evento(juego->simulador, AgregarDificultad, NULL);
}

void juego_titulo(const char* titulo) {
	printf("\x1b[38;5;0m\x1b[48;5;42m\x1b[1m %s \x1b[0m\n", titulo);
}

void juego_prompt_exito(const char* prompt, const char* mensaje) {
	printf("\x1b[38;5;42m\x1b[1m%s\x1b[0m: %s", prompt, mensaje);
}

void juego_terminar(Juego* juego) {
	if (!juego)
		return;

	juego->jugando = false;
}

void juego_destruir(Juego juego) {
	simulador_destruir(juego.simulador);
}
