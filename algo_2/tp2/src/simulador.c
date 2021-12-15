#include "simulador.h"

#include <stdio.h>
#include <string.h>

#include "abb.h"
#include "heap.h"
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

/* struct _pkm_t {
    char* nombre;
    size_t nivel;
}; */

struct _simulador_t {
    hospital_t* hospital;
    EstadisticasSimulacion estadisticas;
    lista_iterador_t* sala_de_espera;
    heap_t* recepcion_pokemones;
};

int comparador_pokemones_por_nivel(void* _pokemon_a, void* _pokemon_b) {
    pokemon_t* pokemon_a = _pokemon_a;
    pokemon_t* pokemon_b = _pokemon_b;

	size_t nivel_pokemon_a = pokemon_nivel(pokemon_a);
	size_t nivel_pokemon_b = pokemon_nivel(pokemon_b);

	if (nivel_pokemon_a > nivel_pokemon_b)
		return 1;
	else if (nivel_pokemon_a < nivel_pokemon_b)
		return -1;

	return 0;
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

    simulador->sala_de_espera = lista_iterador_crear(hospital->entrenadores);
	if (!(simulador->sala_de_espera)) {
		free(simulador);
		return NULL;
	}

    simulador->recepcion_pokemones = heap_crear(comparador_pokemones_por_nivel);
	if (!(simulador->recepcion_pokemones)) {
		lista_iterador_destruir(simulador->sala_de_espera);
		free(simulador);
		return NULL;
	}

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

bool pasar_pokemon_a_recepcion(void* _pokemon, void* _recepcion) {
	pokemon_t* pokemon = _pokemon;
	heap_t* recepcion = _recepcion;
	return heap_insertar(recepcion, pokemon) == 0 ? false : true;
}

ResultadoSimulacion atender_proximo_entrenador(simulador_t* simulador) {
    if (!simulador)
        return ErrorSimulacion;

    entrenador_t* entrenador_atendido = lista_iterador_elemento_actual(simulador->sala_de_espera);
    if (entrenador_atendido) {
		lista_con_cada_elemento(entrenador_atendido->pokemones, pasar_pokemon_a_recepcion, simulador->recepcion_pokemones);
		printf("TAMANIO: %li\n", heap_tamanio(simulador->recepcion_pokemones));

        simulador->estadisticas.entrenadores_atendidos++;
        lista_iterador_avanzar(simulador->sala_de_espera);

        return ExitoSimulacion;
    }

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
    lista_iterador_destruir(simulador->sala_de_espera);
	heap_destruir(simulador->recepcion_pokemones);

    free(simulador);
}
