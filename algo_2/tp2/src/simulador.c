#include "simulador.h"

#include <stdio.h>
#include <string.h>

#include "aux_simulador_atencion_pokemon.h"
#include "aux_simulador_dificultades.h"

#define CANTIDAD_DIFICULTADES_INICIAL 3

struct _simulador_t {
	hospital_t* hospital;
	PokemonEnRecepcion* pokemon_en_tratamiento;
	EstadisticasSimulacion estadisticas;

	heap_t* recepcion;
	lista_iterador_t* sala_espera_entrenadores;
	lista_iterador_t* sala_espera_pokemones;

	abb_t* dificultades;
	DatosDificultadConId dificultad_en_uso;
};

/**
  * Pre: Recibe un simulador con todas sus estructuras de datos inicializadas
  * por sus respetivos constructores. En caso contrario se esta enviando
  * memoria invalida, lo que ocasiona un error en la liberacion.
  *
  * Libera la memoria de las estructuras de datos que componen
  * un simulador en caso de que alguna de estas tenga un fallo durante
  * su creacion.
  */
void simulador_destruir_en_fallo(simulador_t* simulador) {
	if (!simulador)
		return;

	destruir_pokemon_en_recepcion(simulador->pokemon_en_tratamiento);
	heap_destruir(simulador->recepcion, destruir_pokemon_en_recepcion);
	lista_iterador_destruir(simulador->sala_espera_entrenadores);
	lista_iterador_destruir(simulador->sala_espera_pokemones);

	// TODO: liberar correctamente estas dificultades
	simulador->dificultades = crear_dificultades_iniciales();
}

simulador_t* simulador_crear(hospital_t* hospital) {
	if (!hospital)
		return NULL;

	simulador_t* simulador = malloc(sizeof(simulador_t));
	if (!simulador)
		return NULL;

	bool error_creacion = false;

	simulador->hospital = hospital;

	simulador->pokemon_en_tratamiento = calloc(1, sizeof(PokemonEnRecepcion));
	if (!(simulador->pokemon_en_tratamiento))
		error_creacion = true;

	simulador->estadisticas = (EstadisticasSimulacion){
		0,
		.entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital),
		.pokemon_totales = (unsigned)hospital_cantidad_pokemon(hospital),
	};

	simulador->recepcion = heap_crear(comparador_nivel_pokemon);
	if (!(simulador->recepcion))
		error_creacion = true;

	simulador->sala_espera_entrenadores = lista_iterador_crear(hospital->entrenadores);
	if (!(simulador->sala_espera_entrenadores))
		error_creacion = true;

	simulador->sala_espera_pokemones = lista_iterador_crear(hospital->pokemones_orden_llegada);
	if (!(simulador->sala_espera_pokemones))
		error_creacion = true;

	simulador->dificultades = crear_dificultades_iniciales();
	if (!(simulador->dificultades))
		error_creacion = true;

	if (error_creacion) {
		simulador_destruir_en_fallo(simulador);
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

	PokemonEnRecepcion* pokemon_en_tratamiento = simulador->pokemon_en_tratamiento;
	intento->es_correcto = intento->nivel_adivinado == pokemon_en_tratamiento->nivel;

	if (!hay_pokemon_en_tratamiento(*pokemon_en_tratamiento))
		return ErrorSimulacion;

	// TODO: Tengo que cambiar esto a la interfaz en si
	if (!(intento->es_correcto)) {
		printf("Vuelve a intentar\n");
		return ExitoSimulacion;
	}

	return ExitoSimulacion;
}

ResultadoSimulacion agregar_dificultad(simulador_t* simulador, DatosDificultad* datos_dificultad) {
	return ErrorSimulacion;
}

ResultadoSimulacion obtener_informacion_dificultad(simulador_t* simulador, InformacionDificultad* dificultad_buscada) {
	if (!simulador || !dificultad_buscada)
		return ErrorSimulacion;

	DatosDificultadConId* datos_dificultad_buscada = calloc(1, sizeof(DatosDificultadConId));
	if (!datos_dificultad_buscada)
		return ErrorSimulacion;

	datos_dificultad_buscada->id = dificultad_buscada->id;

	DatosDificultadConId* dificultad_encontrada = abb_buscar(simulador->dificultades, datos_dificultad_buscada);
	if (!dificultad_encontrada) {
		dificultad_buscada->nombre_dificultad = dificultad_encontrada->datos_dificultad.nombre;
		dificultad_buscada->en_uso = dificultad_esta_en_uso(simulador->dificultad_en_uso, *dificultad_encontrada);
	}

	free(datos_dificultad_buscada);

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

	abb_destruir_todo(simulador->dificultades, destruir_dificultad);

	hospital_destruir(simulador->hospital);

	free(simulador);
}
