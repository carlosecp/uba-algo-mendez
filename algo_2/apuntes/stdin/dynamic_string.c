#include "dynamic_string.h"
#include "dynamic_string_aux.h"

string_t*
string_crear()
{
	string_t* string = malloc(sizeof(string_t));
	if (!string)
		return NULL;

	string -> cantidad_caracteres = 0;
	string -> max_caracteres = INITIAL_MAX;

	return string;
}

void
string_destruir(string_t* string)
{
	if (!string)
		return;

	free(string -> contenido);
	free(string);
}

size_t
string_cantidad_caracteres(string_t* string)
{
	if (!string)
		return 0;

	return string -> cantidad_caracteres;
}