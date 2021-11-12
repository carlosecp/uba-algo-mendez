#include <stdlib.h>
#include <stdio.h>

#define MAX_ELEMENTOS 100

// Heap maximal
struct heap {
	int elementos[MAX_ELEMENTOS];
	size_t tamanio;
};

void
heap_inicializar(struct heap* heap)
{
	heap -> tamanio = 0;
}

void
swap(int elementos[MAX_ELEMENTOS], size_t pos_a, size_t pos_b)
{
	int temp = elementos[pos_a];
	elementos[pos_a] = elementos[pos_b];
	elementos[pos_b] = temp;
}

void
sift_up(int elementos[MAX_ELEMENTOS], size_t posicion_elemento)
{
	if (!posicion_elemento)
		return;

	int elemento = elementos[posicion_elemento];

	size_t posicion_padre = (posicion_elemento - 1)/2;
	int padre = elementos[posicion_padre];

	if (elemento > padre) {
		swap(elementos, posicion_elemento, posicion_padre);
		sift_up(elementos, posicion_padre); 
	}
}

size_t
heap_insertar(struct heap* heap, int elemento)
{
	if (!(heap -> tamanio))
		return 0;

	heap -> elementos[heap -> tamanio++] = elemento;

	sift_up(heap -> elementos, heap -> tamanio - 1);

	return heap -> tamanio;
}

void
sift_down(int elementos[MAX_ELEMENTOS], size_t posicion_elemento, size_t tope)
{
	size_t posicion_derecho = (posicion_elemento * 2) + 2;
	size_t posicion_izquierdo = (posicion_elemento * 2) + 1;

	if (posicion_izquierdo > tope)
		return;
	
	if (posicion_derecho > tope)
		posicion_derecho = posicion_izquierdo;

	int elemento = elementos[posicion_elemento];
	int derecho = elementos[posicion_derecho];
	int izquierdo = elementos[posicion_izquierdo];

	size_t posicion_intercambiar =
		derecho > izquierdo ? posicion_derecho : posicion_izquierdo;

	if (elementos[posicion_intercambiar] > elemento) {
		swap(elementos, posicion_elemento, posicion_intercambiar);
		sift_down(elementos, posicion_intercambiar, tope);
	}
}

int
heap_extraer_raiz(struct heap* heap)
{
	if (!(heap -> tamanio))
		return -1;

	int raiz = heap -> elementos[0];
	heap -> elementos[0] = heap -> elementos[--(heap -> tamanio)];

	sift_down(heap -> elementos, 0, heap -> tamanio);

	return raiz;
}

void
heapify(int elementos[MAX_ELEMENTOS], size_t cantidad)
{
	if (!cantidad)
		return;

	for (size_t pos = (cantidad - 2)/2; pos > 0; pos--)
		sift_down(elementos, pos, cantidad - 1);

	sift_down(elementos, 0, cantidad - 1);
}

void
heap_sort_recursivo_aux(int elementos[MAX_ELEMENTOS], size_t cantidad)
{
	if (cantidad <= 1)
		return;

	swap(elementos, 0, cantidad - 1);
	cantidad--;

	sift_down(elementos, 0, cantidad - 1);

	heap_sort_recursivo_aux(elementos, cantidad);
}

void
heap_sort(int elementos[MAX_ELEMENTOS], size_t cantidad)
{
	heapify(elementos, cantidad);
	heap_sort_recursivo_aux(elementos, cantidad);
}

int
main(int argc, char* argv[])
{
	const size_t cantidad_elementos = 10;
	int elementos[cantidad_elementos];

	for (size_t i = 0; i < cantidad_elementos; i++)
		elementos[i] = (int)i;

	printf("Original:  [");
	for (size_t i = 0; i < cantidad_elementos; i++)
		printf(" %i ", elementos[i]);
	printf("]\n");

	heapify(elementos, cantidad_elementos);

	printf("Heapified: [");
	for (size_t i = 0; i < cantidad_elementos; i++)
		printf(" %i ", elementos[i]);
	printf("]\n");

	heap_sort(elementos, cantidad_elementos);

	printf("Sorted:    [");
	for (size_t i = 0; i < cantidad_elementos; i++)
		printf(" %i ", elementos[i]);
	printf("]");

	return 0;
}
