#ifndef AUXILIARES_H_
#define AUXILIARES_H_

#include "abb.h"

nodo_abb_t* abb_insertar_recursivo_aux(nodo_abb_t* raiz, void* elemento, abb_comparador comparador, bool* insercion_exitosa);
nodo_abb_t* abb_quitar_recursivo_aux(nodo_abb_t* raiz, void* elemento, void** elemento_quitado, abb_comparador comparador);
nodo_abb_t* abb_maximo(nodo_abb_t** raiz); void* abb_buscar_recursivo_aux(nodo_abb_t* raiz, void* elemento, abb_comparador comparador);

size_t abb_recorrer_preorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array);
size_t abb_recorrer_inorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array);
size_t abb_recorrer_postorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array);

size_t abb_con_cada_elemento_preorden_aux(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* aux);
size_t abb_con_cada_elemento_inorden_aux(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* aux);
size_t abb_con_cada_elemento_postorden_aux(nodo_abb_t* raiz, bool (*funcion)(void*, void*), void* aux);

void abb_destruir_recursivo_aux(nodo_abb_t* raiz, void (*destructor)(void*));

#endif