#include <stdio.h>
#include "hospital.h"
#include "archivo.h"

struct _hospital_pkm_t {
    size_t cantidad_pokemon;
    size_t cantidad_entrenador;
    pokemon_t* vector_pokemones;
    entrenador_t* vector_entrenadores;
};

struct _pkm_t {
    char* nombre;
    size_t nivel;
};

hospital_t*
hospital_crear() {
    return calloc(1, sizeof(hospital_t));
}

entrenador_t
entrenador_crear(char** data_registro) {
	entrenador_t entrenador;
	entrenador.id = atoi(data_registro[0]);
	entrenador.nombre = data_registro[1];
	return entrenador;
}

pokemon_t
pokemon_crear(char** data_registro) {
	pokemon_t pokemon;
	pokemon.nombre = data_registro[0];
	pokemon.nivel = (size_t)atoi(data_registro[1]);
	return pokemon;
}

hospital_t*
agregar_pokemon(hospital_t* hospital, pokemon_t pokemon) {
    if (!hospital)
        return NULL;

    pokemon_t* vector_pokemones_aux =
        realloc(hospital->vector_pokemones, (hospital->cantidad_pokemon + 1) * sizeof(pokemon_t));
    
    if (!vector_pokemones_aux)
        return NULL;
    
    hospital->vector_pokemones = vector_pokemones_aux;
    hospital->vector_pokemones[hospital->cantidad_pokemon++] = pokemon;
    return hospital;
}

hospital_t*
agregar_entrenador(hospital_t* hospital, entrenador_t entrenador) {
    if (!hospital)
        return NULL;

    entrenador_t* vector_entrenadores_aux =
        realloc(hospital->vector_entrenadores, (hospital->cantidad_entrenador + 1) * sizeof(entrenador_t));
    
    if (!vector_entrenadores_aux)
        return NULL;
    
    hospital->vector_entrenadores = vector_entrenadores_aux;
    hospital->vector_entrenadores[hospital->cantidad_entrenador++] = entrenador;
    return hospital;
}

hospital_t*
hospital_guardar_registros(hospital_t* hospital, char** lineas_registros) {
    if (!hospital)
        return NULL;

    size_t cantidad_registros = archivo_cantidad_registros(lineas_registros);
    for (size_t i = 0; i < cantidad_registros; i++) {
        char** data_registro = archivo_data_registro(lineas_registros[i]);
        if (!data_registro) {
            free_vector_strings(data_registro);
            free(data_registro);
            return hospital;
        }

        entrenador_t entrenador = entrenador_crear(data_registro);
        hospital_t* hospital_aux = agregar_entrenador(hospital, entrenador);
        if (!hospital_aux) {
            free_vector_strings(data_registro);
            free(data_registro);
            return hospital;
        }

        for (size_t j = 2; data_registro[j]; j += 2) {
            pokemon_t pokemon = pokemon_crear(data_registro + j);
            hospital_aux = agregar_pokemon(hospital, pokemon);
            if (!hospital_aux) {
                free_vector_strings(data_registro);
                free(data_registro);
                return hospital;
            }
        }

        free_vector_strings(data_registro);
        free(data_registro);
    }

    return hospital;
}

bool
hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!hospital || !archivo)
        return false;

    char* contenido_archivo = archivo_leer(archivo, 10);
    if (!contenido_archivo)
        return false;

    char** lineas_registros = archivo_lineas_registros(contenido_archivo);
    if (!lineas_registros) {
        free(contenido_archivo);
        return false;
	}

    hospital_t* hospital_aux = hospital_guardar_registros(hospital, lineas_registros);
    if (!hospital_aux) {
        free(contenido_archivo);
        free_vector_strings(lineas_registros);
        free(lineas_registros);
        return false;
    }

    hospital = hospital_aux;

    free(contenido_archivo);
    free_vector_strings(lineas_registros);
    free(lineas_registros);

    return true;
}

size_t
hospital_cantidad_pokemon(hospital_t* hospital) {
    return hospital->cantidad_pokemon;
}

size_t
hospital_cantidad_entrenadores(hospital_t* hospital) {
    return hospital->cantidad_entrenador;
}

size_t
hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)) {
    return 0;
}

void
hospital_destruir(hospital_t* hospital) {
    size_t cantidad_pokemon = hospital_cantidad_pokemon(hospital);
    size_t cantidad_entrenador = hospital_cantidad_pokemon(hospital);

    for (size_t i = 0; i < cantidad_pokemon; i++) {
        // free(hospital->vector_pokemones[i].nombre);
    }

    for (size_t i = 0; i < cantidad_entrenador; i++) {
        // free(hospital->vector_entrenadores[i].nombre);
    }

    free(hospital);
}

size_t
pokemon_nivel(pokemon_t* pokemon) {
    if (!pokemon)
        return 0;

    return pokemon->nivel;
}

const char*
pokemon_nombre(pokemon_t* pokemon) {
    if (!pokemon)
        return NULL;

    return pokemon->nombre;
}
