#include <stdio.h>
#include "hospital.h"
#include "split.h"

struct _hospital_pkm_t
{
	size_t cantidad_pokemon;
	pokemon_t *vector_pokemones;
};

struct _pkm_t
{
	char *nombre;
	size_t nivel;
};

hospital_t *hospital_crear()
{
	return calloc(1, sizeof(hospital_t));
}

typedef struct _string_t {
	char* contenido;
	size_t cantidad_caracteres;
	size_t max_caracteres;
} string_t;

string_t* string_crear(size_t max_caracteres_inicial) {
	string_t* string = malloc(sizeof(string));
	if (!string) 
		return NULL;

	string -> cantidad_caracteres = 0;
	string -> max_caracteres = max_caracteres_inicial;
	string -> contenido = calloc(string -> max_caracteres + 1, sizeof(char));
	if (!(string -> contenido))
		return NULL;

	return string;
}

bool hospital_leer_archivo(hospital_t *hospital, const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, "r");
	if (!hospital || !archivo)
		return false;

	string_t* string_registros = string_crear(10);
	if (!string_registros)
		return false;

	char char_leido;
	while ((char_leido = fgetc(archivo)) != EOF) {
		if (string_registros -> cantidad_caracteres >= string_registros -> max_caracteres) {
			string_registros -> max_caracteres *= 2;
			string_registros -> contenido = realloc(string_registros -> contenido, string_registros -> max_caracteres);
		}
		string_registros -> contenido[string_registros -> cantidad_caracteres++] = char_leido;
	}

	printf("%s", string_registros -> contenido);
	fclose(archivo);

	// Ahora parseo la string

	return true;
}

size_t
hospital_cantidad_pokemon(hospital_t *hospital)
{
	return 0;
}

size_t
hospital_cantidad_entrenadores(hospital_t *hospital)
{
	return 0;
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
		free(hospital->vector_pokemones[i].nombre);
	}
	free(hospital->vector_pokemones);
	free(hospital);
}

size_t
pokemon_nivel(pokemon_t *pokemon)
{
	return 0;
}

const char *
pokemon_nombre(pokemon_t *pokemon)
{
	return NULL;
}
