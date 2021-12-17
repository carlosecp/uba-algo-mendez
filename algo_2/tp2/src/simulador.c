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
	pokemon_en_recepcion_t* pokemon_en_tratamiento;
	EstadisticasSimulacion estadisticas;

	heap_t* recepcion;
	lista_iterador_t* sala_espera_entrenadores;
	lista_iterador_t* sala_espera_pokemones;

	lista_t* dificultades;
};

simulador_t* simulador_crear(hospital_t* hospital) {
	if (!hospital)
		return NULL;

	simulador_t* simulador = malloc(sizeof(simulador_t));
	if (!simulador)
		return NULL;

	pokemon_en_recepcion_t* pokemon_en_tratamiento = calloc(1, sizeof(pokemon_en_recepcion_t));
	if (!pokemon_en_tratamiento) {
		free(simulador);
		return NULL;
	}

	EstadisticasSimulacion estadisticas = (EstadisticasSimulacion){
		0,
		.entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital),
		.pokemon_totales = (unsigned)hospital_cantidad_pokemon(hospital),
	};

	heap_t* recepcion = heap_crear(comparador_nivel_pokemon);
	if (!recepcion) {
		free(pokemon_en_tratamiento);
		free(simulador);
		return NULL;
	}

	lista_iterador_t* sala_espera_entrenadores = lista_iterador_crear(hospital->entrenadores);
	if (!sala_espera_entrenadores) {
		free(pokemon_en_tratamiento);
		heap_destruir(recepcion, destruir_pokemon_en_recepcion);
		free(simulador);
		return NULL;
	}

	lista_iterador_t* sala_espera_pokemones = lista_iterador_crear(hospital->pokemones_orden_llegada);
	if (!sala_espera_pokemones) {
		free(pokemon_en_tratamiento);
		heap_destruir(recepcion, destruir_pokemon_en_recepcion);
		lista_iterador_destruir(sala_espera_entrenadores);
		free(simulador);
		return NULL;
	}

	// TODO: Mejorar estas validaciones
	lista_t* dificultades = lista_crear();
	dificultades = agregar_dificultades_iniciales(dificultades);

	simulador->hospital = hospital;
	simulador->estadisticas = estadisticas;
	simulador->pokemon_en_tratamiento = pokemon_en_tratamiento;
	simulador->recepcion = recepcion;
	simulador->sala_espera_entrenadores = sala_espera_entrenadores;
	simulador->sala_espera_pokemones = sala_espera_pokemones;
	simulador->dificultades = dificultades;

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

	entrenador_t* proximo_entrenador = lista_iterador_elemento_actual(simulador->sala_espera_entrenadores);
	if (!proximo_entrenador)
		return ErrorSimulacion;

	bool recepcion_exitosa = agregar_pokemones_de_entrenador_a_recepcion(proximo_entrenador, simulador->sala_espera_pokemones, simulador->recepcion);
	if (!recepcion_exitosa)
		return ErrorSimulacion;

	actualizar_pokemon_en_tratamiento(simulador->pokemon_en_tratamiento, simulador->recepcion);

	simulador->estadisticas.pokemon_en_espera = (unsigned)heap_tamanio(simulador->recepcion);
	simulador->estadisticas.entrenadores_atendidos++;

	lista_iterador_avanzar(simulador->sala_espera_entrenadores);

	return ExitoSimulacion;
}

ResultadoSimulacion obtener_informacion_pokemon_en_tratamiento(simulador_t simulador, InformacionPokemon* informacion) {
	if (!informacion)
		return ErrorSimulacion;

	*informacion = (InformacionPokemon){
		.nombre_pokemon = simulador.pokemon_en_tratamiento->nombre_pokemon,
		.nombre_entrenador = simulador.pokemon_en_tratamiento->nombre_entrenador,
	};

	return ExitoSimulacion;
}

ResultadoSimulacion adivinar_nivel_pokemon(simulador_t* simulador, Intento* intento) {
	if (!simulador || !intento)
		return ErrorSimulacion;

	/* unsigned nivel_adivinado;
	bool es_correcto;
	const char* resultado_string; */

	pokemon_en_recepcion_t* pokemon_en_tratamiento = simulador->pokemon_en_tratamiento;
	intento->es_correcto = intento->nivel_adivinado == pokemon_en_tratamiento->nivel;

	if (!hay_pokemon_en_tratamiento(*pokemon_en_tratamiento))
		return ErrorSimulacion;

	if (!(intento->es_correcto)) {
		printf("Vuelve a intentar\n");
		return ExitoSimulacion;
	}

	return ExitoSimulacion;
}

ResultadoSimulacion agregar_dificultad(simulador_t* simulador, DatosDificultad* datos_dificultad) {
	return ErrorSimulacion;
}

ResultadoSimulacion obtener_informacion_dificultad(simulador_t* simulador, InformacionDificultad* info_dificultad) {
	return ErrorSimulacion;
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
			res = adivinar_nivel_pokemon(simulador, datos);
			break;
		case AgregarDificultad:
			res = agregar_dificultad(simulador, datos);
			break;
		case SeleccionarDificultad:
			break;
		case ObtenerInformacionDificultad:
			res = obtener_informacion_dificultad(simulador, datos);
			break;
		case FinalizarSimulacion:
			res = ExitoSimulacion;
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

	destruir_pokemon_en_recepcion(simulador->pokemon_en_tratamiento);
	heap_destruir(simulador->recepcion, destruir_pokemon_en_recepcion);

	lista_iterador_destruir(simulador->sala_espera_entrenadores);
	lista_iterador_destruir(simulador->sala_espera_pokemones);

	lista_con_cada_elemento(simulador->dificultades, destruir_dificultad, NULL);
	lista_destruir(simulador->dificultades);

	hospital_destruir(simulador->hospital);

	free(simulador);
}
