#include <stdio.h>
#include "hospital.h"
#include "archivo.h"

struct _hospital_pkm_t {
    size_t cantidad_pokemon;
    size_t cantidad_entrenadores;
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

    size_t cantidad_registros = archivo_cantidad_registros(lineas_registros);
    for (size_t i = 0; i < cantidad_registros; i++) {
        char** data_registro_temp = archivo_data_registro(lineas_registros[i]);
        if (!data_registro_temp) {
            free_vector_strings(data_registro_temp);
            free(data_registro_temp);
        }

        entrenador_t entrenador_temp;
        entrenador_temp.id = atoi(data_registro_temp[0]);
        entrenador_temp.nombre = data_registro_temp[1];
        printf("%s:\n", entrenador_temp.nombre);

        for (size_t j = 2; data_registro_temp[j]; j += 2) {
            pokemon_t pokemon_temp;
            pokemon_temp.nombre = data_registro_temp[j];
            pokemon_temp.nivel = (size_t)atoi(data_registro_temp[j + 1]);
            printf("%s\n", pokemon_temp.nombre);
        }

        free_vector_strings(data_registro_temp);
        free(data_registro_temp);
    }
    
    free(lineas_registros[0]);
    free(lineas_registros[1]);
    free(lineas_registros[2]);

    free(contenido_archivo);
    free(lineas_registros);
    return true;
}

size_t
hospital_cantidad_pokemon(hospital_t* hospital) {
    return hospital->cantidad_pokemon;
}

size_t
hospital_cantidad_entrenadores(hospital_t* hospital) {
    return hospital->cantidad_entrenadores;
}

size_t
hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)) {
    return 0;
}

void
hospital_destruir(hospital_t* hospital) {
    size_t cantidad_pokemones = hospital_cantidad_pokemon(hospital);
    for (size_t i = 0; i < cantidad_pokemones; i++) {
        free(hospital->vector_pokemones[i].nombre);
    }
    free(hospital->vector_pokemones);
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
