#include "simulador.h"

#include <stdio.h>
#include <string.h>

#include "aux_simulador_atencion_pokemon.h"
#include "aux_simulador_dificultades.h"
#include "hospital.h"

#define CANTIDAD_DIFICULTADES_INICIAL 3
#define RESULTADO_CORRECTO 0

struct _simulador_t {
	hospital_t* hospital;
	EstadisticasSimulacion estadisticas;

	heap_t* recepcion;
	lista_iterador_t* sala_espera_entrenadores;
	lista_iterador_t* sala_espera_pokemones;
	PokemonEnRecepcion* pokemon_en_tratamiento;

	abb_t* dificultades;
	DatosDificultadConId dificultad_en_uso;
	unsigned intentos_actuales;
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
	abb_destruir_todo(simulador->dificultades, destruir_dificultad);
}

simulador_t* simulador_crear(hospital_t* hospital) {
	if (!hospital)
		return NULL;

	simulador_t* simulador = calloc(1, sizeof(simulador_t));
	if (!simulador)
		return NULL;

	bool exito = true;

	simulador->hospital = hospital;
	simulador->pokemon_en_tratamiento = NULL;
	simulador->estadisticas = (EstadisticasSimulacion){
		0,
		.entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital),
		.pokemon_totales = (unsigned)hospital_cantidad_pokemon(hospital),
	};

	simulador->recepcion = heap_crear(comparador_nivel_pokemon);
	if (!(simulador->recepcion))
		exito = false;

	simulador->sala_espera_entrenadores = lista_iterador_crear(hospital->entrenadores);
	if (!(simulador->sala_espera_entrenadores))
		exito = false;

	simulador->sala_espera_pokemones = lista_iterador_crear(hospital->pokemones_orden_llegada);
	if (!(simulador->sala_espera_pokemones))
		exito = false;

	simulador->dificultades = crear_dificultades_iniciales(&(simulador->dificultad_en_uso));
	if (!(simulador->dificultades))
		exito = false;

	if (!exito) {
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

/**
*/
ResultadoSimulacion atender_proximo_entrenador(simulador_t* simulador) {
	if (!simulador)
		return ErrorSimulacion;

	entrenador_t* proximo_entrenador = lista_iterador_elemento_actual(simulador->sala_espera_entrenadores);
	if (!proximo_entrenador)
		return ErrorSimulacion;

	bool recepcion_exitosa = agregar_pokemones_de_entrenador_a_recepcion(proximo_entrenador, simulador->sala_espera_pokemones, simulador->recepcion);
	if (!recepcion_exitosa)
		return ErrorSimulacion;

	actualizar_pokemon_en_tratamiento(&(simulador->pokemon_en_tratamiento), simulador->recepcion);
	actualizar_cantidad_pokemones_en_recepcion(&(simulador->estadisticas), simulador->recepcion);

	simulador->estadisticas.entrenadores_atendidos++;
	lista_iterador_avanzar(simulador->sala_espera_entrenadores);

	return ExitoSimulacion;
}

ResultadoSimulacion obtener_informacion_pokemon_en_tratamiento(simulador_t simulador, InformacionPokemon* informacion) {
	if (!informacion)
		return ErrorSimulacion;

	PokemonEnRecepcion* pokemon_en_tratamiento = simulador.pokemon_en_tratamiento;
	char* nombre_pokemon = pokemon_en_tratamiento ? pokemon_en_tratamiento->nombre_pokemon : NULL;
	char* nombre_entrenador = pokemon_en_tratamiento ? pokemon_en_tratamiento->nombre_entrenador : NULL;

	*informacion = (InformacionPokemon){
		.nombre_pokemon = nombre_pokemon,
		.nombre_entrenador = nombre_entrenador,
	};

	return ExitoSimulacion;
}

bool avanzar_pokemon_atendido(simulador_t* simulador) {
	if (!simulador)
		return false;

	PokemonEnRecepcion* pokemon_adivinado = heap_extraer_raiz(simulador->recepcion);
	if (!pokemon_adivinado)
		return true;

	destruir_pokemon_en_recepcion(pokemon_adivinado);

	bool exito = actualizar_cantidad_pokemones_en_recepcion(&(simulador->estadisticas), simulador->recepcion);
	if (!exito)
		return false;

	simulador->pokemon_en_tratamiento = NULL;
	exito = actualizar_pokemon_en_tratamiento(&(simulador->pokemon_en_tratamiento), simulador->recepcion);
	simulador->estadisticas.pokemon_atendidos++;

	return exito;
}

ResultadoSimulacion adivinar_nivel_pokemon(simulador_t* simulador, Intento* intento) {
	if (!simulador || !intento)
		return ErrorSimulacion;

	PokemonEnRecepcion* pokemon_en_tratamiento = simulador->pokemon_en_tratamiento;
	if (!pokemon_en_tratamiento)
		return ErrorSimulacion;

	int (*verificar_nivel)(unsigned, unsigned) = simulador->dificultad_en_uso.verificar_nivel;
	int resultado = verificar_nivel(intento->nivel_adivinado, (unsigned)pokemon_en_tratamiento->nivel);
	intento->es_correcto = resultado == RESULTADO_CORRECTO;

	if (intento->es_correcto) {
		avanzar_pokemon_atendido(simulador);
		simulador->intentos_actuales = 0;
	} else {
		simulador->intentos_actuales++;
	}

	intento->resultado_string = simulador->dificultad_en_uso.verificacion_a_string(resultado);

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
	if (dificultad_encontrada) {
		dificultad_buscada->nombre_dificultad = dificultad_encontrada->nombre;
		dificultad_buscada->en_uso = dificultad_esta_en_uso(simulador->dificultad_en_uso, *dificultad_encontrada);
	}

	free(datos_dificultad_buscada);

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
			simulador->estadisticas.cantidad_eventos_simulados--;
	}

	return res;
}

void simulador_destruir(simulador_t* simulador) {
	if (!simulador)
		return;

	heap_destruir(simulador->recepcion, destruir_pokemon_en_recepcion);
	lista_iterador_destruir(simulador->sala_espera_entrenadores);
	lista_iterador_destruir(simulador->sala_espera_pokemones);
	abb_destruir_todo(simulador->dificultades, destruir_dificultad);
	hospital_destruir(simulador->hospital);

	free(simulador);
}
