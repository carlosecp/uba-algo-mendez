#include "simulador.h"

#include <stdio.h>

#include "abb.h"
#include "hospital.h"
#include "lista.h"

struct _simulador_t {
    hospital_t* hospital;
    EstadisticasSimulacion estadisticas;
};

simulador_t* simulador_crear(hospital_t* hospital) {
	if (!hospital)
		return NULL;

	simulador_t* simulador = malloc(sizeof(simulador_t));
	if (!simulador)
		return NULL;

	simulador->hospital = hospital;

	return simulador;
}

ResultadoSimulacion obtener_estadisticas(simulador_t simulador, void* estadisticas) {
    // printf("\033[1m\033[4mEstadisticas:\033[0m\n");
    return ExitoSimulacion;
}

ResultadoSimulacion atender_proximo_entrenador(simulador_t* simulador) {
	return ExitoSimulacion;
}

ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos) {
    if (!simulador)
        return ErrorSimulacion;

    switch (evento) {
        case ObtenerEstadisticas:
            return obtener_estadisticas(*simulador, datos);
        case AtenderProximoEntrenador:
            return atender_proximo_entrenador(simulador);
        case ObtenerInformacionPokemonEnTratamiento:
            break;
        case AdivinarNivelPokemon:
            break;
        case AgregarDificultad:
            break;
        case SeleccionarDificultad:
            break;
        case ObtenerInformacionDificultad:
            break;
        case FinalizarSimulacion:
            break;
        default:
            return ErrorSimulacion;
    }

    return ExitoSimulacion;
}

void simulador_destruir(simulador_t* simulador) {
    if (!simulador)
        return;

    hospital_destruir(simulador->hospital);
    free(simulador);
}
