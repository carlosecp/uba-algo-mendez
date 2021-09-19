#include "split.h"
#include <stdlib.h>
#include <string.h>

size_t
contar_substrings(const char* string, char separador) {
	if (!(*string))
		return 1;

	if (*string == separador)
		return 1 + contar_substrings(string + 1, separador);
	
	return contar_substrings(string + 1, separador);
}

size_t
contar_longitud_substring(const char* string, char separador) {
	size_t i = 0;
	while (string[i] != '\0' && string[i] != separador)
		i++;

	return i;
}

char*
duplicar_string(const char* string, size_t longitud) {
	char* nuevo_string = malloc((longitud + 1) * sizeof(char));
	if (!nuevo_string)
		return NULL;

	for (size_t i = 0; i < longitud; i++)
		nuevo_string[i] = string[i];

	nuevo_string[longitud] = 0;
	return nuevo_string;
}

char**
split(const char* string, char separador) {
	if (!string)
		return NULL;
	
	size_t cantidad_substrings = contar_substrings(string, separador);
	char** vector_substrings = calloc((cantidad_substrings + 1), sizeof(void*));
	if (!vector_substrings)
		return NULL;
	
	for (size_t i = 0; i < cantidad_substrings; i++) {
		size_t longitud_substring = contar_longitud_substring(string, separador);
		char* substring = duplicar_string(string, longitud_substring);

		vector_substrings[i] = substring;
		string += longitud_substring + 1;
	}

	return vector_substrings;
}