#include "pila.h"
#define MAX_ELEMENTOS 10

struct _pila_t {
	void* elementos[MAX_ELEMENTOS];
	size_t cantidad_elementos;
};

pila_t* pila_crear(){
    return calloc(1, sizeof(pila_t));
}

pila_t* pila_apilar(pila_t* pila, void* elemento){
	if (pila -> cantidad_elementos >= MAX_ELEMENTOS)
		return NULL;

	pila -> elementos[pila -> cantidad_elementos] = elemento;
	return pila;
}

void* pila_desapilar(pila_t* pila){
    return NULL;
}

void* pila_tope(pila_t* pila){
	if (!pila || pila_vacia(pila))
		return NULL;

    return pila -> elementos[pila -> cantidad_elementos];
}

size_t pila_tamanio(pila_t* pila){
	if (!pila)
		return 0;

    return pila -> cantidad_elementos;
}

bool pila_vacia(pila_t* pila){
	if (!pila || !(pila -> cantidad_elementos))
		return true;

    return false;
}

void pila_destruir(pila_t* pila){
	if (!pila)
		return;

	free(pila);
}
