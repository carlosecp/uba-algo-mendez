#include "hospital.h"
#include "split.h"
#include <stdio.h>
#include "parser_archivo.h"

struct _hospital_pkm_t {
	size_t cantidad_pokemon;
	pokemon_t* vector_pokemones;
	size_t cantidad_entrenadores;
};

struct _pkm_t {
	char* nombre;
	size_t nivel;
};

typedef struct _entrenador_t {
	int id;
	char* nombre;
} entrenador_t;

typedef struct _registro_t {
	entrenador_t entrenador;
	pokemon_t* vector_pokemones;
} registro_t;

hospital_t *hospital_crear() {
	return calloc(1, sizeof(hospital_t));
}

registro_t obtener_registro(char* registro_archivo) {
	char** data_registro_archivo = split(registro_archivo, ';');
	registro_t registro;

	registro.entrenador.id = atoi(data_registro_archivo[0]);
	registro.entrenador.nombre = data_registro_archivo[1];

	printf("Entrenador: {%i;%s}\n", registro.entrenador.id, registro.entrenador.nombre);
	for (size_t i = 2; data_registro_archivo[i]; i += 2) {
		printf("Pokemon: {%s; %s}\n", data_registro_archivo[i], data_registro_archivo[i + 1]);
	}
	printf("\n");

	return registro;
}

registro_t* obtener_vector_registros(char* contenido_archivo) {
	if (!contenido_archivo)
		return NULL;

	char**  listado_registros_archivo = split(contenido_archivo, '\n');
	if (!listado_registros_archivo)
		return NULL;

	size_t cantidad_registros = 0;
	while (listado_registros_archivo[cantidad_registros])
		cantidad_registros++;

	registro_t* vector_registros = malloc((cantidad_registros + 1) * sizeof(registro_t));
	if (!vector_registros)
		return NULL;

	for (size_t i = 0; i < cantidad_registros; i++) {
		obtener_registro(listado_registros_archivo[i]);
	}

	return vector_registros;
}

bool hospital_leer_archivo(hospital_t *hospital, const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, "r");
	if (!hospital || !archivo)
		return false;

	char* contenido_archivo = leer_contenido_archivo(archivo, 10);
	if (!contenido_archivo)
		return false;

	registro_t* listado_registros = obtener_vector_registros(contenido_archivo);
	if (!listado_registros) {
		free(contenido_archivo);
		return false;
	}

	free(contenido_archivo);
	free(listado_registros);
	return true;
}

size_t
hospital_cantidad_pokemon(hospital_t *hospital)
{
	return hospital -> cantidad_pokemon;
}

size_t
hospital_cantidad_entrenadores(hospital_t *hospital)
{
	return hospital -> cantidad_entrenadores;
}

size_t
hospital_a_cada_pokemon(hospital_t *hospital, bool (*funcion)(pokemon_t *p))
{
	return 0;
}

void hospital_destruir(hospital_t *hospital)
{
	size_t cantidad_pokemones = hospital_cantidad_pokemon(hospital);
	for (size_t i = 0; i < cantidad_pokemones; i++)
	{
		free(hospital -> vector_pokemones[i].nombre);
	}
	free(hospital -> vector_pokemones);
	free(hospital);
}

size_t
pokemon_nivel(pokemon_t *pokemon)
{
	if (!pokemon)
		return 0;
	
	return pokemon -> nivel;
}

const char *
pokemon_nombre(pokemon_t *pokemon)
{
	if (!pokemon)
		return NULL;

	return pokemon -> nombre;
}
