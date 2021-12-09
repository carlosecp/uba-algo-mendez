#include "simulador.h"

#include <stdio.h>

struct _simulador_t {
	hospital_t* hospital;
	EstadisticasSimulacion estadisticas;
};

simulador_t* simulador_crear(hospital_t* hospital) {
	if (!hospital)
		return NULL;

	simulador_t* simulador = calloc(1, sizeof(simulador_t));
	if (!simulador)
		return NULL;

	simulador->hospital = hospital;
	simulador->estadisticas = (EstadisticasSimulacion){
		.entrenadores_atendidos = 0,
		.entrenadores_totales = 0,
		.pokemon_atendidos = 0,
		.pokemon_en_espera = 0,
		.pokemon_totales = 0,
		.puntos = 0,
		.cantidad_eventos_simulados = 0
	};

	return simulador;
}

ResultadoSimulacion obtener_estadisticas(simulador_t simulador) {
	EstadisticasSimulacion estadisticas = simulador.estadisticas;

	printf("\033[1m\033[4mEstadisticas:\033[0m\n");
	printf("Entrenadores Atendidos: %u\n", estadisticas.entrenadores_atendidos);
	printf("Entrenadores Totales: %u\n", estadisticas.entrenadores_totales);
	printf("Pokemon Atendidos: %u\n", estadisticas.pokemon_atendidos);
	printf("Pokemon En Espera: %u\n", estadisticas.pokemon_en_espera);
	printf("Pokemon Totales: %u\n", estadisticas.pokemon_totales);
	printf("Puntos: %u\n", estadisticas.puntos);
	printf("Cantidad Eventos Simulados: %u\n", estadisticas.cantidad_eventos_simulados);

	return ExitoSimulacion;
}

ResultadoSimulacion atender_proximo_entrenador() {
	return ExitoSimulacion;
}

ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos) {
	if (!simulador)
		return ErrorSimulacion;

	switch (evento) {
		case ObtenerEstadisticas:
			return obtener_estadisticas(*simulador);
		case AtenderProximoEntrenador:
			return atender_proximo_entrenador();
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

	// Destruye el simulador y libera la memoria asociada (incluida la del hospital).
	hospital_destruir(simulador->hospital);
	free(simulador);
}
