#include "simulador.h"

struct _simulador_t {
	hospital_t* hospital;
};

simulador_t* simulador_crear(hospital_t* hospital) {
	// Toma control del hospital, por lo tanto el hospital debe estar creado.
	if (!hospital)
		return NULL;

	simulador_t* simulador = calloc(1, sizeof(simulador_t));
	if (!simulador)
		return NULL;

	simulador->hospital = hospital;

	return simulador;
}

ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos) {
	return ExitoSimulacion;
}

void simulador_destruir(simulador_t* simulador) {
	if (!simulador)
		return;

	// Destruye el simulador y libera la memoria asociada (incluida la del hospital).
	hospital_destruir(simulador->hospital);
	free(simulador);
}
