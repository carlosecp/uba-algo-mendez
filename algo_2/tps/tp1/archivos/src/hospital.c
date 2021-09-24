#include <stdio.h>
#include <string.h>
#include "hospital.h"
#include "parser.h"

typedef struct entrenador {
	int   id;
	char* nombre;
} entrenador_t;

struct _hospital_pkm_t{
	size_t        cantidad_pokemon;
	size_t        cantidad_entrenador;
	pokemon_t*    vector_pokemones;
	entrenador_t* vector_entrenadores;
};

struct _pkm_t{
	char*  nombre;
	size_t nivel;
};

hospital_t*
hospital_crear(){
	hospital_t* hospital = malloc(sizeof(hospital_t));
	if (!hospital)
		return NULL;

	hospital -> cantidad_pokemon    = 0;
	hospital -> cantidad_entrenador = 0;
	hospital -> vector_pokemones    = NULL;
	hospital -> vector_entrenadores = NULL;

	return hospital;
}

pokemon_t*
crear_pokemon(char* nivel, char* nombre) {
	if (!nombre)
		return NULL;

	pokemon_t* nuevo_pokemon = malloc(sizeof(pokemon_t));
	if (!nuevo_pokemon)
		return NULL;

	nuevo_pokemon -> nivel = (size_t)atoi(nivel);
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

	hospital -> vector_pokemones = realloc(hospital -> vector_pokemones, (hospital -> cantidad_pokemon + 1) * sizeof(pokemon_t));
	hospital -> vector_pokemones[(hospital -> cantidad_pokemon)++] = *nuevo_pokemon;
}

void
free_pokemon(pokemon_t* pokemon) {
	if (!pokemon)
		return;

	free(pokemon -> nombre);
	free(pokemon);
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

	hospital -> vector_entrenadores = realloc(hospital -> vector_entrenadores, (hospital -> cantidad_entrenador + 1) * sizeof(entrenador_t));
	hospital -> vector_entrenadores[(hospital -> cantidad_entrenador)++] = *nuevo_entrenador;
}

void
free_entrenador(entrenador_t* entrenador) {
	if (!entrenador)
		return;

	free(entrenador -> nombre);
	free(entrenador);
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

	for (size_t i = 2; informacion_linea[i]; i += 2) {
		pokemon_t* nuevo_pokemon = crear_pokemon(informacion_linea[i + 1], informacion_linea[i]);
		// printf("Pokemon: {%s, %i}\n", nuevo_pokemon -> nombre, (int)(nuevo_pokemon -> nivel));
		free_pokemon(nuevo_pokemon);
	}

	free_vector_strings(informacion_linea);
	free(informacion_linea);
	free(nuevo_entrenador);

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
		printf("Linea: %s\n", linea);
		hospital_guardar_informacion(hospital, linea);
		free(linea);
		linea = leer_linea(archivo);
	}

	size_t cantidad_entrenador = hospital_cantidad_entrenadores(hospital);
	for (size_t i = 0; i < cantidad_entrenador; i++) {
		printf("Entrenador: {%s}\n", hospital -> vector_entrenadores[i].nombre);
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
hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
	return 0;
}

void
hospital_destruir(hospital_t* hospital){
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
	return 0;
}

const char*
pokemon_nombre(pokemon_t* pokemon){
	return NULL;
}
