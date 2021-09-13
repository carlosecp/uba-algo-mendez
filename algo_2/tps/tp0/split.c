#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split(const char* string, char separador){
	if (string == NULL) return NULL;

	size_t long_string = 0;
	size_t cant_substrings = 0;

	for (; string[long_string]; long_string++) {
		if (string[long_string] == separador) cant_substrings++;
		printf("string[%li]: %c\n", long_string, string[long_string]);
	}

	if (cant_substrings) cant_substrings++;
	printf("cant_substrings: %li\n", cant_substrings);

	char** vector_strings = malloc((cant_substrings + 1) * sizeof(char*));

	size_t long_substring = 0;
	for (size_t i = 0; i < cant_substrings; i++) {
		long_substring = 0;
		while (string[long_substring] != separador && string[long_substring] != '\0')
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

void imprimir_strings(char* vector_strings[]) {
	for (size_t i = 0; vector_strings[i]; i++) {
		for (size_t j = 0; vector_strings[i][j] != '\0'; j++)
			printf("vector_strings[%li]: %c", i, vector_strings[i][j]);
		printf("\n");
	}
}

int main() {
	char* string = ",";
	char** vector_strings = split(string, ',');
	imprimir_strings(vector_strings);
	free(vector_strings);
	return 0;
}
