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

bool
hospital_guardar_informacion(hospital_t* hospital, char** lineas_archivo) {
	if (!lineas_archivo)
		return false;

	size_t cantidad_registros = parser_obtener_cantidad_registros(lineas_archivo);
	for (size_t i = 0; i < (cantidad_registros - 1); i++) {
		char** informacion_lineas = parser_obtener_informacion_linea(lineas_archivo[i]);

		entrenador_t* entrenador = malloc(sizeof(entrenador_t));
		entrenador -> id = atoi(informacion_lineas[0]);
		strcpy(entrenador -> nombre, informacion_lineas[1]);

		printf("Entrenador: {%i, %s}\n", entrenador -> id, entrenador -> nombre);

		free(informacion_lineas);
		free(entrenador);
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

	buffer_t* buffer = buffer_leer(archivo);
	if (!buffer)
		return false;

	char** lineas_archivo = parser_obtener_lineas_archivo(buffer);
	if (!lineas_archivo) {
		free(buffer);
		return false;
	}

	hospital_guardar_informacion(hospital, lineas_archivo);

	free_vector_strings(lineas_archivo);
	free(lineas_archivo);
	free(buffer -> contenido);
	free(buffer);

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
