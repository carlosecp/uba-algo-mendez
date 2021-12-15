#include "simulador.h"

#include <stdio.h>

#include "abb.h"
#include "hospital.h"
#include "lista.h"

struct _hospital_pkm_t {
    lista_t* entrenadores;
    abb_t* pokemones;
};

struct _entrenador_t {
    int id;
    char* nombre;
    lista_t* pokemones;
};

struct _pkm_t {
    char* nombre;
    size_t nivel;
};

struct _simulador_t {
    hospital_t* hospital;
    EstadisticasSimulacion estadisticas;
	lista_iterador_t* sala_de_espera;
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

	simulador->sala_de_espera = lista_iterador_crear(hospital->entrenadores);

    return simulador;
}

ResultadoSimulacion obtener_estadisticas(simulador_t simulador, EstadisticasSimulacion* e) {
    if (!e)
        return ErrorSimulacion;

    *e = (EstadisticasSimulacion){
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

	entrenador_t* entrenador_atendido = lista_iterador_elemento_actual(simulador->sala_de_espera);
	if (entrenador_atendido) {
		printf("Entrenador: {%s}\n", entrenador_atendido->nombre);
		lista_iterador_avanzar(simulador->sala_de_espera);
		simulador->estadisticas.entrenadores_atendidos++;
	}

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
    }

    return ErrorSimulacion;
}

void simulador_destruir(simulador_t* simulador) {
    if (!simulador)
        return;

    hospital_destruir(simulador->hospital);
	lista_iterador_destruir(simulador->sala_de_espera);

    free(simulador);
}
