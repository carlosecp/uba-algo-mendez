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
	if (!archivo)
		return NULL;

	fseek(archivo, 0, SEEK_END);
	size_t longitud_archivo = ftell(archivo);
	rewind(archivo);

	char* contenido = malloc((longitud_archivo + 1) * sizeof(char));
	size_t leidos = fread(contenido, 1, longitud_archivo, archivo);
	if (!leidos) {
		free(contenido);
		return NULL;
	}

	contenido[longitud_archivo] = 0;
	fclose(archivo);

	return contenido;
}

bool hospital_leer_archivo(hospital_t *hospital, const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, "r");
	if (!hospital || !archivo)
		return false;

	char* contenido_archivo = leer_archivo(archivo);
	if (!contenido_archivo)
		return false;

	char** registros = split(contenido_archivo, '\n');

	free(contenido_archivo);
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
