#include <stdlib.h>

typedef struct vector {
	void** elementos;
	size_t cantidad_elementos;
	size_t maximo_elementos;
} vector_t;

vector_t* vector_crear() {
	return calloc(sizeof(vector_t));
}

size_t vector_cantidad(vector* vector) {
	if (vector) return vector->cantidad_elementos;
}

vector_t* vector_agregar(vector_t* vector, void* elemento) {
	if (!vector) return NULL;

	void** vector_aux = realloc(vector->elementos, (sizeof(void*)) * vector->cantidad_elementos);
	if (!vector_aux) return NULL;

	vector->elementos = vector_aux;
	vector->elementos[vector->cantidad_elementos] = elemento;
	vector->cantidad_elementos++;

	return vector;
}

void vector_destruir(vector_t* vector) {
	if (vector) {
		free(vector->elementos);
		free(vector);
	}
}

void** vector_elementos(vector_t* vector) {
	if (!vector) return NULL;
	return vector->elementos;
}
