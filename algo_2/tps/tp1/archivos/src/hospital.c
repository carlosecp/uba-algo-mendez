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

char* leer_archivo(FILE* archivo) {
	char* contenido_archivo = malloc(sizeof(char));
	if (!contenido_archivo)
		return NULL;
	
	size_t cantidad_caracteres = 0;

	char caracter_leido;
	while ((caracter_leido = fgetc(archivo)) != EOF) {
		char* contenido_archivo_aux = realloc(contenido_archivo, cantidad_caracteres + 1);
		if (!contenido_archivo_aux) {
			free(contenido_archivo);
			return NULL;
		}

		contenido_archivo[cantidad_caracteres] = caracter_leido;
		cantidad_caracteres++;
	}

	contenido_archivo[cantidad_caracteres] = 0;

	return contenido_archivo;
}

bool hospital_leer_archivo(hospital_t *hospital, const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, "r");
	if (!hospital || !archivo)
		return false;

	char* contenido_archivo = leer_archivo(archivo);
	if (!contenido_archivo)
		return false;

	printf("Contenido:\n%s", contenido_archivo);

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
