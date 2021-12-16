#include "hospital.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"
#include "auxiliares_hospital.h"
#include "lista.h"
#include "parser_hospital.h"
#include "split.h"

struct _hospital_pkm_t {
	lista_t* entrenadores;
	abb_t* pokemones;
};

struct _entrenador_t {
	int id;
	char* nombre;
};

struct _pkm_t {
	char* nombre;
	size_t nivel;
};

/*
 * Destructor utilizado para liberar un entrenador de memoria cuando se
 * elimina del hospital.
 */
bool destruir_entrenador(void* _entrenador, void* aux) {
	entrenador_t* entrenador = _entrenador;

	free(entrenador->nombre);
	free(entrenador);

	return true;
}

/*
 * Destructor utilizado para liberar un pokemon de memoria cuando se
 * elimina del hospital.
 */
void destruir_pokemon(void* _pokemon) {
	pokemon_t* pokemon = _pokemon;
	free(pokemon->nombre);
	free(pokemon);
}

int abb_comparador_pokemones_por_nombre(void* _p1, void* _p2) {
	pokemon_t* p1 = _p1;
	pokemon_t* p2 = _p2;
	return strcmp(p1->nombre, p2->nombre);
}

// TODO: Esta struct y la funcion que le sigue son las que utilizo
// para recorrer los pokemones utilizando el iterador de ABB.
typedef struct {
	bool (*funcion)(pokemon_t* p);
} wrapper_funcion_aux;

bool funcion_aux(void* _pokemon, void* _aux) {
	pokemon_t* pokemon = _pokemon;
	wrapper_funcion_aux* aux_funcion = _aux;
	return aux_funcion->funcion(pokemon);
}

hospital_t* hospital_crear() {
	hospital_t* hospital = calloc(1, sizeof(hospital_t));
	if (!hospital)
		return NULL;

	hospital->entrenadores = lista_crear();
	if (!hospital->entrenadores) {
		free(hospital);
		return NULL;
	}

	hospital->pokemones = abb_crear(abb_comparador_pokemones_por_nombre);
	if (!hospital->pokemones) {
		lista_destruir(hospital->entrenadores);
		free(hospital);
		return NULL;
	}

	return hospital;
}

/**
 * Crea un nuevo pokemon con el nivel y nombre correspondientes.
 * En caso de error devuelve NULL. Caso contrario, un puntero al nuevo pokemon creado.
 */
pokemon_t* crear_pokemon(char* nivel, char* nombre) {
	if (!nombre)
		return NULL;

	pokemon_t* nuevo_pokemon = malloc(sizeof(pokemon_t));
	if (!nuevo_pokemon)
		return NULL;

	nuevo_pokemon->nivel = (size_t)atoi(nivel);
	nuevo_pokemon->nombre = malloc((strlen(nombre) + 1) * sizeof(char));
	if (!nuevo_pokemon->nombre) {
		free(nuevo_pokemon);
		return NULL;
	}

	strcpy(nuevo_pokemon->nombre, nombre);
	return nuevo_pokemon;
}

/**
 * Crea un nuevo entrenador con el ID y nombre correspondientes.
 * En caso de error devuelve NULL. Caso contrario, un puntero al nuevo entrenador creado.
 */
entrenador_t* crear_entrenador(char* id, char* nombre) {
	if (!nombre)
		return NULL;

	entrenador_t* nuevo_entrenador = malloc(sizeof(entrenador_t));
	if (!nuevo_entrenador)
		return NULL;

	nuevo_entrenador->id = atoi(id);
	nuevo_entrenador->nombre = malloc((strlen(nombre) + 1) * sizeof(char));
	if (!nuevo_entrenador->nombre) {
		free(nuevo_entrenador);
		return NULL;
	}

	strcpy(nuevo_entrenador->nombre, nombre);
	return nuevo_entrenador;
}

/**
 * Toma una linea leida del archivo de texto dado, obteniene la informacion de dicha linea
 * y finalmente se encarga de guardar toda la informacion de ese registro en el hospital.
 *
 * Devuelve true si pudo guardarlo o false en caso de error.
 */
bool hospital_guardar_informacion(hospital_t* hospital, char* linea_archivo) {
	if (!hospital || !linea_archivo)
		return false;

	char** informacion_linea = obtener_informacion_linea(linea_archivo);
	if (!informacion_linea)
		return false;

	entrenador_t* nuevo_entrenador = crear_entrenador(informacion_linea[0], informacion_linea[1]);
	if (!nuevo_entrenador) {
		free(informacion_linea);
		return false;
	}

	for (size_t i = 2; informacion_linea[i]; i += 2) {
		pokemon_t* nuevo_pokemon = crear_pokemon(informacion_linea[i + 1], informacion_linea[i]);
		if (!nuevo_pokemon) {
			free_vector_strings(informacion_linea);
			free(informacion_linea);
			return false;
		}

		hospital->pokemones = abb_insertar(hospital->pokemones, nuevo_pokemon);
	}

	hospital->entrenadores = lista_insertar(hospital->entrenadores, nuevo_entrenador);

	free_vector_strings(informacion_linea);
	free(informacion_linea);

	return true;
}

bool hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo) {
	if (!hospital)
		return false;

	FILE* archivo = fopen(nombre_archivo, "r");
	if (!archivo)
		return false;

	char* linea = leer_linea(archivo);
	bool continuar_guardando_informacion = true;

	while (linea && continuar_guardando_informacion) {
		continuar_guardando_informacion = hospital_guardar_informacion(hospital, linea);
		free(linea);
		linea = leer_linea(archivo);
	}

	fclose(archivo);
	return true;
}

size_t hospital_cantidad_pokemon(hospital_t* hospital) {
	if (!hospital)
		return 0;

	return abb_tamanio(hospital->pokemones);
}

size_t hospital_cantidad_entrenadores(hospital_t* hospital) {
	if (!hospital)
		return 0;

	return lista_tamanio(hospital->entrenadores);
}

size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)) {
	if (!hospital || !funcion)
		return 0;

	wrapper_funcion_aux aux = {funcion};
	size_t cantidad_recorridos = abb_con_cada_elemento(hospital->pokemones, INORDEN, funcion_aux, &aux);
	return cantidad_recorridos;
}

void hospital_destruir(hospital_t* hospital) {
	if (!hospital)
		return;

	lista_con_cada_elemento(hospital->entrenadores, destruir_entrenador, NULL);
	lista_destruir(hospital->entrenadores);
	abb_destruir_todo(hospital->pokemones, destruir_pokemon);

	free(hospital);
}

size_t pokemon_nivel(pokemon_t* pokemon) {
	if (!pokemon)
		return 0;
	return pokemon->nivel;
}

const char* pokemon_nombre(pokemon_t* pokemon) {
	if (!pokemon)
		return NULL;
	return pokemon->nombre;
}
