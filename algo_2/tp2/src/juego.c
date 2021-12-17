#include "juego.h"

#include <stdio.h>
#include "simulador.h"

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

void juego_catch_error(const char* evento_simulado) {
	printf("\x1b[38;5;15m\x1b[48;5;160m\x1b[1m ERROR \x1b[0m\n");
	printf("Ha ocurrido un error durante la simulacion del evento \x1b[4m%s\x1b[0m.\n", evento_simulado);
	printf("Podes referirte al archivo eventos.txt para un listado de las posibles causas de error de este evento.\n");
}

void juego_terminar(Juego* juego) {
	if (!juego)
		return;

	juego->jugando = false;
}

void juego_destruir(Juego juego) {
	simulador_destruir(juego.simulador);
}
