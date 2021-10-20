#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t* abb_crear(abb_comparador comparador){
	if (!comparador)
		return NULL;

	abb_t* arbol = calloc(1, sizeof(abb_t));
	if (!arbol)
		return NULL;

	arbol -> comparador = comparador;
    return arbol;
}

abb_t* abb_insertar(abb_t* arbol, void* elemento){
  return arbol;
}

void* abb_quitar(abb_t* arbol, void *elemento){
  return NULL;
}

void* abb_buscar(abb_t* arbol, void* elemento){
  return NULL;
}

bool abb_vacio(abb_t* arbol){
  return true;
}

size_t abb_tamanio(abb_t *arbol){
  return 0;
}

void abb_destruir(abb_t *arbol){
	if (!arbol)
		return;

	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){

}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
  return 0;
}

size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
  return 0;
}
