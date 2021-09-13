#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
es_char_de_substring(char char_substring, char separador) {
	return char_substring != separador && char_substring != '\0';
}

char**
split(const char* string, char separador){
	if (!string) return NULL;

	size_t long_string = 0;
	size_t cant_substrings = 0;

	for (; string[long_string]; long_string++)
		if (string[long_string] == separador) cant_substrings++;

	cant_substrings++;

	char** vector_strings = malloc((cant_substrings + 1) * sizeof(char*));
	size_t long_substring = 0;

	for (size_t i = 0; i < cant_substrings; i++) {
		long_substring = 0;
		while (es_char_de_substring(string[long_substring], separador))
			long_substring++;

		vector_strings[i] = malloc((long_substring + 1) * sizeof(char));
		for (size_t j = 0; j < long_substring; j++)
			vector_strings[i][j] = string[j];

		vector_strings[i][long_substring] = '\0';
		string += (long_substring + 1);
	}

	vector_strings[cant_substrings] = NULL;
	return vector_strings;
}
