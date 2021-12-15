#include "heap.h"

#include <stdlib.h>

#define MAX_INICIAL 10

heap_t* heap_crear(heap_comparador comparador) {
    if (!comparador)
        return NULL;

    heap_t* heap = malloc(sizeof(heap_t));

    heap->tamanio = 0;
    heap->maximo = MAX_INICIAL;
    heap->comparador = comparador;

    heap->elementos = calloc(heap->maximo, sizeof(void*));
    if (!(heap->elementos)) {
        free(heap);
        return NULL;
    }

    return heap;
}

void swap(void** elementos, size_t pos_a, size_t pos_b) {
    void* tmp = elementos[pos_a];
    elementos[pos_a] = elementos[pos_b];
    elementos[pos_b] = tmp;
}

void sift_up(void** elementos, size_t pos_elemento, heap_comparador comparador) {
    if (pos_elemento == 0)
        return;

    size_t pos_padre = (pos_elemento - 1) / 2;

    void* elemento = elementos[pos_elemento];
    void* elemento_padre = elementos[pos_padre];

    int comparacion = comparador(elemento, elemento_padre);
    if (comparacion < 0) {
        swap(elementos, pos_elemento, pos_padre);
        sift_up(elementos, pos_padre, comparador);
    }
}

void sift_down(void** elementos, size_t pos_elemento, size_t tope, heap_comparador comparador) {
    size_t pos_izquierdo = (pos_elemento * 2) + 1;
    size_t pos_derecho = (pos_elemento * 2) + 2;
    size_t pos_intercambiar = pos_elemento;

    if (pos_izquierdo > tope)
        return;

    if (pos_derecho > tope)
        pos_derecho = pos_izquierdo;

    void* elemento = elementos[pos_elemento];
    void* elemento_izquierdo = elementos[pos_izquierdo];
    void* elemento_derecho = elementos[pos_derecho];

    int comparacion_izq_der = comparador(elemento_izquierdo, elemento_derecho);
    pos_intercambiar = comparacion_izq_der > 0 ? pos_derecho : pos_izquierdo;

    int comparacion = comparador(elemento, elementos[pos_intercambiar]);
    if (comparacion > 0) {
        swap(elementos, pos_elemento, pos_intercambiar);
        sift_down(elementos, pos_intercambiar, tope, comparador);
    }
}

size_t heap_insertar(heap_t* heap, void* elemento) {
    if (!heap)
        return 0;

    if (heap->tamanio >= heap->maximo) {
        size_t nuevo_maximo = heap->maximo * 2;
        void** elementos_aux = realloc(heap->elementos, nuevo_maximo * sizeof(void*));
        if (!elementos_aux)
            return 0;

        heap->elementos = elementos_aux;
        heap->maximo = nuevo_maximo;
    }

    heap->elementos[heap->tamanio++] = elemento;
    sift_up(heap->elementos, heap->tamanio - 1, heap->comparador);

    return heap->tamanio;
}

void* heap_extraer_raiz(heap_t* heap) {
    if (!heap)
        return NULL;

    if (heap->tamanio == 0)
        return NULL;

    void* elemento_extraido = heap->elementos[0];

    heap->tamanio--;
    heap->elementos[0] = heap->elementos[heap->tamanio];

    if (heap->tamanio > 0)
        sift_down(heap->elementos, 0, heap->tamanio, heap->comparador);

    return elemento_extraido;
}

void heapify(void** elementos, size_t cantidad) {
}

size_t heap_tamanio(heap_t* heap) {
    if (!heap)
        return 0;

    return heap->tamanio;
}

void heap_destruir(heap_t* heap) {
    if (!heap)
        return;

    free(heap->elementos);
    free(heap);
}
