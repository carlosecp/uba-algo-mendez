#include <string.h>
#include "hospital.h"
#include "split.h"
#include "parser.h"


struct _hospital_pkm_t{
	size_t cantidad_pokemon;
	pokemon_t* vector_pokemones;
};

struct _pkm_t{
	char* nombre;
	size_t nivel;
};

typedef struct entrenador {
	int id;
	char* nombre;
} entrenador_t;

hospital_t*
hospital_crear(){
	return NULL;
}

entrenador_t*
crear_entrenador(char* id, char* nombre) {
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
free_entrenador(entrenador_t* entrenador) {
	if (!entrenador)
		return;

	free(entrenador -> nombre);
	free(entrenador);
}

bool
hospital_guardar_informacion(hospital_t* hospital, char** lineas_archivo) {
	if (!lineas_archivo)
		return false;

	size_t cantidad_registros = parser_obtener_cantidad_registros(lineas_archivo);
	for (size_t i = 0; i < (cantidad_registros - 1); i++) {
		char** informacion_lineas = parser_obtener_informacion_linea(lineas_archivo[i]);

		// TODO: Okay, definitivamente esta aqui la fuga de memoria
		entrenador_t* nuevo_entrenador = crear_entrenador(informacion_lineas[0], informacion_lineas[1]);
		if (!nuevo_entrenador) {
			free_vector_strings(informacion_lineas);
			free(informacion_lineas);
			return false;
		}

		printf("Entrenador: {%i, %s}\n", nuevo_entrenador -> id, nuevo_entrenador -> nombre);

		free_vector_strings(informacion_lineas);
		free(informacion_lineas);
		free_entrenador(nuevo_entrenador);
	}

	return true;
}

bool
hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo){
	/* if (!hospital)
		return false; */

	FILE* archivo = fopen(nombre_archivo, "r");
	if (!archivo)
		return false;

	while (!feof(archivo)) {
		char buffer[MAX_LECTURA];
		char* linea_leida = leer_linea(buffer, MAX_LECTURA, archivo);
		printf("%s", linea_leida);
	}

	return false;
}

size_t
hospital_cantidad_pokemon(hospital_t* hospital){
	return 0;
}

size_t
hospital_cantidad_entrenadores(hospital_t* hospital){
	return 0;
}

size_t
hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
	return 0;
}

void
hospital_destruir(hospital_t* hospital){

}

size_t
pokemon_nivel(pokemon_t* pokemon){
	return 0;
}

const char*
pokemon_nombre(pokemon_t* pokemon){
	return NULL;
}
