#include <stdlib.h>

/* size_t cantidad_substrings(const char* string, char separador) {
	size_t contador = 0;
	for (size_t i = 0; i < strlen(string); i++) {
		// ... Esta implementacion seria n^2, porque strlen(string) se corre en cada iteracion
	}
} */

size_t cantidad_substrings(const char* string, char separador) {
	size_t contador = 0;
	size_t i = 0;

	while (string[i]) {
		if (string[i] == separador) contador++;
		i++;
	}

	return contador;
}

char** split(const char* string, char separador) {
	if (!string) return NULL;

	size_t ocurrencias = cantidad_substrings(string, separador);
	size_t substrings = ocurrencias + 1;

	char** vector = calloc(substrings + 1, sizeof(void*));
	if (!vector) return NULL;

	for (size_t n = 0; n < substring; n++) {
	}

	return NULL;
}
