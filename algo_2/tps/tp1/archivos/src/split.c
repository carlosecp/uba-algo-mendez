#include <stdlib.h>
#include <stdio.h>

size_t contar_substrings(const char* string, char separador) {
	if (!string)
		return 1;
	
	return (*string == separador ? 1 : 0) + contar_substrings(string, separador);
}

size_t contar_longitud_substring(const char* string, char separador) {
	if (*string == separador) 
		return 0;
	
	return 1 + contar_longitud_substring(string + 1, separador);
}

char* duplicar_substring(const char* string, size_t longitud_substring) {
	char* substring = malloc((longitud_substring + 1) * sizeof(char));
	if (!substring)
		return NULL;

	for (size_t i = 0; i < longitud_substring; i++)
		substring[i] = string[i];
	
	substring[longitud_substring] = 0;

	return substring;
}

void liberar_vector(char** vector_strings) {
	while (*vector_strings) {
		free(*vector_strings);
		vector_strings++;
	}
}

char** split(const char* string, char separador) {
	if (!string)
		return NULL;

	size_t cantidad_substrings = contar_substrings(string, separador);

	char** vector_substrings = malloc((cantidad_substrings + 1) * sizeof(char*));
	if (!vector_substrings)
		return NULL;

	for (size_t i = 0; i < cantidad_substrings; i++) {
		size_t longitud_substring = contar_longitud_substring(string, separador);
		char* substring = duplicar_substring(string, longitud_substring);
		if (!substring)
			liberar_vector(vector_substrings);

		vector_substrings[i] = substring;
		string += longitud_substring;
	}

	vector_substrings[cantidad_substrings] = NULL;

	return vector_substrings;
}