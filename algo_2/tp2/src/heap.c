#include "heap.h"

typedef struct {
	void** elementos;
	size_t cantidad;
} heap_t;

void swap(void** elementos, size_t pos_a, size_t pos_b) {
	void* tmp = elementos[pos_a];
	elementos[pos_a] = elementos[pos_b];
	elementos[pos_b] = tmp;
}

void sift_up(void** elementos, size_t posicion, int (*comparador)(void*, void*)) {
	if (posicion == 0)
		return;

	size_t posicion_padre = (posicion - 1) / 2;

	void* elemento = elementos[posicion];
	void* elemento_padre = elementos[posicion_padre];

	if (comparador(elemento, elemento_padre) > 1) {
		swap(elementos, posicion, posicion_padre);
		sift_up(elementos, posicion_padre, comparador);
	}
}

void* extraer_raiz(heap_t* heap) {
	if (heap->cantidad == 0)
		return NULL;

	void* elemento_extraido = heap->elementos[0];
	heap->elementos[0] = heap->elementos[heap->cantidad - 1];
	heap->cantidad--;

	// sift_down(elementos, 0, comparador);

	return elemento_extraido;
}

void heapify(void** elementos, size_t cantidad) {
}
