#include "simulador.h"

#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "heap.h"
#include "lista.h"

#include "auxiliares_simulador.h"

#define CANTIDAD_DIFICULTADES_INICIAL 3

struct _simulador_t {
	hospital_t* hospital;
	InformacionPokemon pokemon_en_consultorio;
	EstadisticasSimulacion estadisticas;

	heap_t* recepcion;
	lista_iterador_t* entrenadores_sala_espera;
	lista_iterador_t* pokemones_sala_espera;

	// hash_t* dificultades;
};

// TODO: Documentacion de esta funcion
int comparador_nivel_pokemon(void* _pokemon_a, void* _pokemon_b) {
	pokemon_en_recepcion_t* pokemon_a = _pokemon_a;
	pokemon_en_recepcion_t* pokemon_b = _pokemon_b;

	if (pokemon_a->nivel > pokemon_b->nivel)
		return 1;
	else if (pokemon_a->nivel < pokemon_b->nivel)
		return -1;

	return 0;
}

void destructor_pokemon_en_recepcion(void* _pokemon) {
	pokemon_en_recepcion_t* pokemon = _pokemon;
	free(pokemon->nombre);
	free(pokemon->nombre_entrenador);
	free(pokemon);
}

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

	simulador->recepcion = heap_crear(comparador_nivel_pokemon);
	if (!(simulador->recepcion)) {
		free(simulador);
		return NULL;
	}

	simulador->entrenadores_sala_espera = lista_iterador_crear(hospital->entrenadores);
	if (!(simulador->entrenadores_sala_espera)) {
		heap_destruir(simulador->recepcion, destructor_pokemon_en_recepcion);
		free(simulador);
		return NULL;
	}

	simulador->pokemones_sala_espera = lista_iterador_crear(hospital->pokemones_orden_llegada);
	if (!(simulador->pokemones_sala_espera)) {
		heap_destruir(simulador->recepcion, destructor_pokemon_en_recepcion);
		free(simulador->entrenadores_sala_espera);
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
	if (!simulador)
		return ErrorSimulacion;

	entrenador_t* entrenador_en_recepcion = lista_iterador_elemento_actual(simulador->entrenadores_sala_espera);
	if (!entrenador_en_recepcion)
		return ErrorSimulacion;

	for (int i = 0; i < entrenador_en_recepcion->cantidad_pokemones; i++) {
		pokemon_t* pokemon_en_sala_de_espera = lista_iterador_elemento_actual(simulador->pokemones_sala_espera);

		if (pokemon_en_sala_de_espera) {
			pokemon_en_recepcion_t* pokemon_en_recepcion = preparar_pokemon_para_recepcion(pokemon_en_sala_de_espera, entrenador_en_recepcion->nombre);
			if (!pokemon_en_recepcion)
				return ErrorSimulacion;

			heap_insertar(simulador->recepcion, pokemon_en_recepcion);
		}

		lista_iterador_avanzar(simulador->pokemones_sala_espera);
	}

	if (!hay_pokemon_en_consultorio(simulador->pokemon_en_consultorio)) {
		pokemon_en_recepcion_t* pokemon_en_consultorio = heap_extraer_raiz(simulador->recepcion);
		atender_pokemon_de_menor_nivel(&(simulador->pokemon_en_consultorio), pokemon_en_consultorio);
		free(pokemon_en_consultorio->nombre);
		free(pokemon_en_consultorio->nombre_entrenador);
		free(pokemon_en_consultorio);
	}

	simulador->estadisticas.pokemon_en_espera = (unsigned)heap_tamanio(simulador->recepcion);
	simulador->estadisticas.entrenadores_atendidos++;

	lista_iterador_avanzar(simulador->entrenadores_sala_espera);

	return ExitoSimulacion;
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

	free((char*)simulador->pokemon_en_consultorio.nombre_pokemon);
	free((char*)simulador->pokemon_en_consultorio.nombre_entrenador);

	heap_destruir(simulador->recepcion, destructor_pokemon_en_recepcion);
	lista_iterador_destruir(simulador->entrenadores_sala_espera);
	lista_iterador_destruir(simulador->pokemones_sala_espera);

	hospital_destruir(simulador->hospital);

	free(simulador);
}
