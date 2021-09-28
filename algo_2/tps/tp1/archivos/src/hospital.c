#include <stdio.h>
#include <string.h>
#include "hospital.h"
#include "parser.h"

typedef struct entrenador {
	int   id;
	char* nombre;
} entrenador_t;

struct _hospital_pkm_t {
	size_t        cantidad_pokemon;
	size_t        cantidad_entrenador;
	pokemon_t*    vector_pokemones;
	entrenador_t* vector_entrenadores;
};

struct _pkm_t {
	char*  nombre;
	size_t nivel;
};

hospital_t*
hospital_crear() {
	return calloc(1, sizeof(hospital_t));
}

pokemon_t*
crear_pokemon(char* nivel, char* nombre) {
	if (!nombre)
		return NULL;

	pokemon_t* nuevo_pokemon = malloc(sizeof(pokemon_t));
	if (!nuevo_pokemon)
		return NULL;

	nuevo_pokemon -> nivel  = (size_t)atoi(nivel);
	nuevo_pokemon -> nombre = malloc((strlen(nombre) + 1) * sizeof(char));
	if (!nuevo_pokemon -> nombre) {
		free(nuevo_pokemon);
		return NULL;
	}

	strcpy(nuevo_pokemon -> nombre, nombre);
	return nuevo_pokemon;
}

void
hospital_guardar_pokemon(hospital_t* hospital, pokemon_t* nuevo_pokemon) {
	if (!hospital || !nuevo_pokemon)
		return;

	size_t cantidad_pokemon      = hospital_cantidad_pokemon(hospital);
	hospital -> vector_pokemones = realloc(hospital -> vector_pokemones, (cantidad_pokemon + 1) * sizeof(pokemon_t));
	hospital -> vector_pokemones[(hospital -> cantidad_pokemon)++] = *nuevo_pokemon;
}

entrenador_t*
crear_entrenador(char* id, char* nombre) {
	if (!nombre)
		return NULL;

	entrenador_t* nuevo_entrenador = malloc(sizeof(entrenador_t));
	if (!nuevo_entrenador)
		return NULL;

	nuevo_entrenador -> id = atoi(id);
	nuevo_entrenador -> nombre = malloc((strlen(nombre) + 1) * sizeof(char));
	if (!nuevo_entrenador -> nombre) {
		free(nuevo_entrenador);
		return NULL;
	}

	strcpy(nuevo_entrenador -> nombre, nombre);
	return nuevo_entrenador;
}

void
hospital_guardar_entrenador(hospital_t* hospital, entrenador_t* nuevo_entrenador) {
	if (!hospital || !nuevo_entrenador)
		return;

	size_t cantidad_entrenador = hospital_cantidad_entrenadores(hospital);
	hospital -> vector_entrenadores = realloc(hospital -> vector_entrenadores, (cantidad_entrenador + 1) * sizeof(entrenador_t));
	hospital -> vector_entrenadores[(hospital -> cantidad_entrenador)++] = *nuevo_entrenador;
}

bool
hospital_guardar_informacion(hospital_t* hospital, char* linea_archivo) {
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

	hospital_guardar_entrenador(hospital, nuevo_entrenador);
	free(nuevo_entrenador);

	for (size_t i = 2; informacion_linea[i]; i += 2) {
		pokemon_t* nuevo_pokemon = crear_pokemon(informacion_linea[i + 1], informacion_linea[i]);
		if (!nuevo_pokemon) {
			free_vector_strings(informacion_linea);
			free(informacion_linea);
			return false;
		}

		hospital_guardar_pokemon(hospital, nuevo_pokemon);
		free(nuevo_pokemon);
	}

	free_vector_strings(informacion_linea);
	free(informacion_linea);

	return true;
}

bool
hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo){
	if (!hospital)
		return false;

	FILE* archivo = fopen(nombre_archivo, "r");
	if (!archivo)
		return false;

	char* linea = leer_linea(archivo);
	while (linea) {
		hospital_guardar_informacion(hospital, linea);
		free(linea);
		linea = leer_linea(archivo);
	}

	fclose(archivo);
	return true;
}

size_t
hospital_cantidad_pokemon(hospital_t* hospital){
	if (!hospital)
		return 0;

	return hospital -> cantidad_pokemon;
}

size_t
hospital_cantidad_entrenadores(hospital_t* hospital){
	if (!hospital)
		return 0;

	return hospital -> cantidad_entrenador;
}

size_t
encontrar_primer_pokemon(pokemon_t** vector_pokemones, size_t cantidad_pokemon) {
	size_t minimo = 0;
	for (size_t i = 0; i < cantidad_pokemon; i++) {
		if (strcmp((*vector_pokemones[i]).nombre, (*vector_pokemones[minimo]).nombre) < 0)
			minimo = i;
	}

	return minimo;
}

void
ordenar_pokemones(pokemon_t** vector_pokemones, size_t cantidad_pokemon) {
	if (!vector_pokemones || !cantidad_pokemon)
		return;

	size_t minimo = encontrar_primer_pokemon(vector_pokemones, cantidad_pokemon);
	pokemon_t* temp = vector_pokemones[minimo];
	vector_pokemones[minimo] = vector_pokemones[0];
	vector_pokemones[0] = temp;

	ordenar_pokemones(vector_pokemones + 1, cantidad_pokemon - 1);
}

size_t
hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
	if (!hospital || !funcion)
		return 0;

	size_t cantidad_pokemon = hospital_cantidad_pokemon(hospital);

	pokemon_t** pokemones_aux = malloc(cantidad_pokemon * sizeof(pokemon_t*));
	if (!pokemones_aux)
		return 0;

	for (size_t i = 0; i < cantidad_pokemon; i++)
		pokemones_aux[i] = &(hospital -> vector_pokemones[i]);

	ordenar_pokemones(pokemones_aux, cantidad_pokemon);

	size_t i = 0;
	while ((i < cantidad_pokemon) && funcion(pokemones_aux[i])) i++;

	free(pokemones_aux);

	return i;
}

void
hospital_destruir(hospital_t* hospital){
	if (!hospital)
		return;

	if (hospital -> vector_pokemones) {
		size_t cantidad_pokemon = hospital_cantidad_pokemon(hospital);
		for (size_t i = 0; i < cantidad_pokemon; i++)
			free(hospital -> vector_pokemones[i].nombre);
		
		free(hospital -> vector_pokemones);
	}

	if (hospital -> vector_entrenadores) {
		size_t cantidad_entrenador = hospital_cantidad_entrenadores(hospital);
		for (size_t i = 0; i < cantidad_entrenador; i++)
			free(hospital -> vector_entrenadores[i].nombre);
		
		free(hospital -> vector_entrenadores);
	}

	if (hospital)
		free(hospital);
}

size_t
pokemon_nivel(pokemon_t* pokemon){
	if (!pokemon)
		return 0;
	return pokemon -> nivel;
}

const char*
pokemon_nombre(pokemon_t* pokemon){
	if (!pokemon)
		return NULL;
	return pokemon -> nombre;
}
