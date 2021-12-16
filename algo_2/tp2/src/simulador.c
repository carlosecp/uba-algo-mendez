#include "simulador.h"

#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "heap.h"
#include "hospital.h"
#include "auxiliares_hospital.h"
#include "lista.h"

#define CANTIDAD_DIFICULTADES_INICIAL 3

struct _simulador_t {
	hospital_t* hospital;
	InformacionPokemon pokemon_en_consultorio;
	EstadisticasSimulacion estadisticas;
	lista_iterador_t* entrenadores_sala_espera;
	// hash_t* dificultades;
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

	simulador->entrenadores_sala_espera = lista_iterador_crear(hospital->entrenadores);
	if (!(simulador->entrenadores_sala_espera)) {
		free(simulador);
		return NULL;
	}

	return simulador;
}

ResultadoSimulacion obtener_estadisticas(simulador_t simulador, EstadisticasSimulacion* estadisticas) {
	if (!estadisticas)
		return ErrorSimulacion;

	*estadisticas = (EstadisticasSimulacion){
		.entrenadores_atendidos = simulador.estadisticas.entrenadores_atendidos,
		.entrenadores_totales = simulador.estadisticas.entrenadores_totales,
		.pokemon_atendidos = simulador.estadisticas.pokemon_atendidos,
		.pokemon_en_espera = simulador.estadisticas.pokemon_en_espera,
		.pokemon_totales = simulador.estadisticas.pokemon_totales,
		.puntos = simulador.estadisticas.puntos,
		.cantidad_eventos_simulados = simulador.estadisticas.cantidad_eventos_simulados,
	};

	return ExitoSimulacion;
}

ResultadoSimulacion atender_proximo_entrenador(simulador_t* simulador) {
	/* NOTE: Necesito que el pokemon que queda en la recepcion tenga conocimiento
	   del entrenador al que pertence para luego poderlo mostrar en la
	   informacion */

	if (!simulador)
		return ErrorSimulacion;

	entrenador_t* entrenador_en_recepcion = lista_iterador_elemento_actual(simulador->entrenadores_sala_espera);

	if (entrenador_en_recepcion) {
		printf("%s\n", entrenador_en_recepcion->nombre);

		lista_iterador_avanzar(simulador->entrenadores_sala_espera);
	}

	return ErrorSimulacion;
}

ResultadoSimulacion obtener_informacion_pokemon_en_tratamiento(simulador_t simulador, InformacionPokemon* informacion) {
	if (!informacion)
		return ErrorSimulacion;

	*informacion = (InformacionPokemon){
		.nombre_pokemon = simulador.pokemon_en_consultorio.nombre_pokemon,
			.nombre_entrenador = simulador.pokemon_en_consultorio.nombre_entrenador,
	};

	return ExitoSimulacion;
}

ResultadoSimulacion agregar_dificultad(simulador_t* simulador, DatosDificultad* dificultad) {
	return ExitoSimulacion;
}

ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos) {
	ResultadoSimulacion res = ErrorSimulacion;

	if (!simulador)
		return res;

	simulador->estadisticas.cantidad_eventos_simulados++;

	switch (evento) {
		case ObtenerEstadisticas:
			res = obtener_estadisticas(*simulador, datos);
			break;
		case AtenderProximoEntrenador:
			res = atender_proximo_entrenador(simulador);
			break;
		case ObtenerInformacionPokemonEnTratamiento:
			res = obtener_informacion_pokemon_en_tratamiento(*simulador, datos);
			break;
		case AdivinarNivelPokemon:
			break;
		case AgregarDificultad:
			res = agregar_dificultad(simulador, datos);
			break;
		case SeleccionarDificultad:
			break;
		case ObtenerInformacionDificultad:
			break;
		case FinalizarSimulacion:
			break;
		default:
			// Para compensar el ++ anterior (en este caso se paso un numero invalido)
			simulador->estadisticas.cantidad_eventos_simulados--;
	}

	return res;
}

void simulador_destruir(simulador_t* simulador) {
	if (!simulador)
		return;

	lista_iterador_destruir(simulador->entrenadores_sala_espera);
	hospital_destruir(simulador->hospital);

	free(simulador);
}
