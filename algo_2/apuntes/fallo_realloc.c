#include <stdlib.h>
#include <stdio.h>

int main() {
	int* vector = calloc(5, sizeof(int));
	if (!vector) return EXIT_FAILURE;

	// ... supongamos que llenamos el vector ...
	int* vector_aux = realloc(vector, 10 * sizeof(int));
	if (!vector_aux) { // Por si el realloc falla
		free(vector); // Hago free solo al original, porque el otro es NULL
		return EXIT_FAILURE;
	}

	// Si realloc no falla, de un solo libera el bloque anterior
	vector = vector_aux;

	// ...
	free(vector);

	return EXIT_SUCCESS;
}
