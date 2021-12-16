#include "simulador.h"

#include <stdio.h>
#include <string.h>

#include "auxiliares_hospital.h"
#include "heap.h"
#include "hospital.h"

struct _simulador_t {
	hospital_t* hospital;
	InformacionPokemon pokemon_en_consultorio;
	EstadisticasSimulacion estadisticas;
};

simulador_t* simulador_crear(hospital_t* hospital) {
	if (!hospital)
		return NULL;

	simulador_t* simulador = malloc(sizeof(simulador_t));
	if (!simulador)
		return NULL;

	simulador->hospital = hospital;
	simulador->estadisticas = (EstadisticasSimulacion){
		0,
		.entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital),
		.pokemon_totales = (unsigned)hospital_cantidad_pokemon(hospital),
	};

	simulador->pokemon_en_consultorio = (InformacionPokemon){NULL};

	return simulador;
}

ResultadoSimulacion obtener_estadisticas(simulador_t simulador, EstadisticasSimulacion* e) {
	if (!e)
		return ErrorSimulacion;

	*e = (EstadisticasSimulacion){
		.entrenadores_atendidos     = simulador.estadisticas.entrenadores_atendidos,
		.entrenadores_totales       = simulador.estadisticas.entrenadores_totales,
		.pokemon_atendidos          = simulador.estadisticas.pokemon_atendidos,
		.pokemon_en_espera          = simulador.estadisticas.pokemon_en_espera,
		.pokemon_totales            = simulador.estadisticas.pokemon_totales,
		.puntos                     = simulador.estadisticas.puntos,
		.cantidad_eventos_simulados = simulador.estadisticas.cantidad_eventos_simulados,
	};

	return ExitoSimulacion;
}

ResultadoSimulacion atender_proximo_entrenador(simulador_t* simulador) {
	return ErrorSimulacion;
}

ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos) {
	ResultadoSimulacion res = ErrorSimulacion;

	if (!simulador)
		return res;

	switch (evento) {
		case ObtenerEstadisticas:
			res = obtener_estadisticas(*simulador, datos);
			break;
		case AtenderProximoEntrenador:
			res = atender_proximo_entrenador(simulador);
			break;
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
			return res;
	}

	simulador->estadisticas.cantidad_eventos_simulados++;
	return res;
}

void simulador_destruir(simulador_t* simulador) {
	if (!simulador)
		return;

	hospital_destruir(simulador->hospital);

	free(simulador);
}
