#include <stdio.h>
#include <string.h>
#include "hospital.h"
#include "archivo.h"
#include "split.h"

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

pokemon_t*
generar_vector_pokemones(char** lineas_registros) {
    pokemon_t* vector_pokemones = NULL;

    for (size_t i = 0; lineas_registros[i]; i++) {
        char** linea_registro = archivo_leer_linea_registro(lineas_registros[i]);
        if (!linea_registro)
            return NULL;

        free_vector_strings(linea_registro);
        free(linea_registro);
    }

    return vector_pokemones;
}

bool
hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!hospital || !archivo)
        return false;

    char* contenido_archivo = archivo_leer(archivo, 10);
    if (!contenido_archivo)
        return false;

    char** lineas_registros = split(contenido_archivo, '\n');
    free(contenido_archivo);
    if (!lineas_registros)
        return false;

    printf("%s", contenido_archivo);

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
