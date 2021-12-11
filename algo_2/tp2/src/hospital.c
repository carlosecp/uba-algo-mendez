/* TODO: Agregar validaciones para las operaciones de guardado. */
#include "hospital.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "split.h"
#include "lista.h"

struct _pkm_t {
	char* nombre;
	size_t nivel;
};

struct _entrenador_t {
	int id;
	char* nombre;
	lista_t* pokemones;
};

struct _hospital_pkm_t {
	lista_t* entrenadores;
};

hospital_t* hospital_crear() {
	hospital_t* hospital = calloc(1, sizeof(hospital_t));
	if (!hospital)
		return NULL;

	hospital->entrenadores = lista_crear();

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
	return NULL;
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

	nuevo_entrenador->pokemones = lista_crear();
	if (!nuevo_entrenador->pokemones) {
		free(nuevo_entrenador);
		free(nuevo_entrenador->nombre);
		return NULL;
	}

	return nuevo_entrenador;
}

/**
 * Agrega un entrenador dado al vector de pokemones de un hospital (en la ultima posicion).
 * En caso de error no agrega el pokemon dado al hospital.
 */
void hospital_guardar_entrenador(hospital_t* hospital, entrenador_t* nuevo_entrenador) {
	if (!hospital || !nuevo_entrenador)
		return;

	lista_t* entrenadores = lista_insertar(hospital->entrenadores, nuevo_entrenador);
	if (!entrenadores)
		return;

	hospital->entrenadores = entrenadores;
	return;
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

		nuevo_entrenador->pokemones = lista_insertar(nuevo_entrenador->pokemones, nuevo_pokemon);
	}

	hospital_guardar_entrenador(hospital, nuevo_entrenador);

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

bool sumar_pokemones_por_entrenador(void* _entrenador, void* aux) {
	entrenador_t* entrenador = _entrenador;
	size_t* cantidad_pokemon = aux;

	*cantidad_pokemon += lista_tamanio(entrenador->pokemones);

	return true;
}

size_t hospital_cantidad_pokemon(hospital_t* hospital) {
	if (!hospital)
		return 0;

	size_t cantidad_pokemon = 0;
	lista_con_cada_elemento(hospital->entrenadores, sumar_pokemones_por_entrenador, &cantidad_pokemon);

	return cantidad_pokemon;
}

size_t hospital_cantidad_entrenadores(hospital_t* hospital) {
	if (!hospital)
		return 0;

	return lista_tamanio(hospital->entrenadores);
}

size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)) {
	return 0;
}

bool destruir_pokemon(void* pokemon, void* aux) {
	pokemon_t* tmp = pokemon;
	free(tmp->nombre);
	free(tmp);
	return true;
}

bool destruir_entrenador(void* entrenador, void* aux) {
	entrenador_t* tmp = entrenador;

	lista_con_cada_elemento(tmp->pokemones, destruir_pokemon, NULL);
	lista_destruir(tmp->pokemones);

	free(tmp->nombre);
	free(tmp);

	return true;
}

void hospital_destruir(hospital_t* hospital) {
	if (!hospital)
		return;

	lista_con_cada_elemento(hospital->entrenadores, destruir_entrenador, NULL);
	lista_destruir(hospital->entrenadores);

	free(hospital);

	return;
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
