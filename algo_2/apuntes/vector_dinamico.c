#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
	int* elem;
	size_t n;
	size_t max;
} vector_t;

void imprimir_vector(vector_t* vector) {
	printf("[");
	for (size_t i = 0; i < vector -> n; i++)
		printf(" %i", vector -> elem[i]);
	printf(" ]\n");
}

vector_t* inicializar_vector(int max) {
	vector_t* vector = malloc(sizeof(vector_t));
	vector -> elem = calloc(max, sizeof(int));
	vector -> max = max;
	vector -> n = 0;
	return vector;
}

void agregar_a_vector(vector_t* vector, int elem) {
	if (vector -> n == vector -> max) {
		vector -> max *= 2;
		vector -> elem = realloc(vector -> elem, (vector -> max) * sizeof(int));
	} 
	vector -> elem[vector->n] = elem;
	(vector -> n)++;
}

int main() {
	vector_t* vector = inicializar_vector(10);

	// Agregamos una cantidad que sepamos que alcanza
	for (size_t i = 0; i < 5; i++)
		agregar_a_vector(vector, i * i);
	printf("Vector[%li/%li]: ", vector -> n, vector -> max);
	imprimir_vector(vector);

	// Llenamos por complete el vector
	for (size_t i = vector -> n; i < vector -> max; i++)
		agregar_a_vector(vector, i * i);
	printf("Vector[%li/%li]: ", vector -> n, vector -> max);
	imprimir_vector(vector);

	// Sobrepasamos el maximo
	for (size_t i = vector -> n; i < 15; i++)
		agregar_a_vector(vector, i * i);
	printf("Vector[%li/%li]: ", vector -> n, vector -> max);
	imprimir_vector(vector);

	free(vector -> elem);
	free(vector);
}
