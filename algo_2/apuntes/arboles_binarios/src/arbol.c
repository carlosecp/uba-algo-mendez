#include "arbol.h"

struct _abb_t {
	void* elemento;
	abb_t* izquierdo;
	abb_t* derecho;
};

abb_t*
abb_crear() {
	return NULL;
}

abb_t*
abb_insertar(abb_t* abb, void* elemento, int (comparador)(void*, void*)) {
	if (!abb) {
		abb_t* nuevo_nodo = calloc(1, sizeof(abb_t));
		if (!nuevo_nodo)
			return NULL;

		nuevo_nodo -> elemento = elemento;
		return nuevo_nodo;
	}

	int comparacion = comparador(elemento, abb -> elemento);
	if (comparacion <= 0)
		abb -> izquierdo = abb_insertar(abb -> izquierdo, elemento, comparador);
	else
		abb -> derecho = abb_insertar(abb -> derecho, elemento, comparador);

	return abb;
}

void*
abb_buscar(abb_t* abb, void* elemento, int (comparador)(void*, void*)) {
	if (!abb)
		return NULL;

	int comparacion = comparador(elemento, abb -> elemento);	
	if (comparacion == 0)
		return abb -> elemento;
	else if (comparacion < 0)
		return abb_buscar(abb -> izquierdo, elemento, comparador);
	else
		return abb_buscar(abb -> derecho, elemento, comparador);
}


abb_t*
abb_quitar(abb_t* abb, void* elemento, int (comparador)(void*, void*)) {
	if (!abb)
		return NULL;

	int comparacion = compardor(elemento, abb -> elemento);
	if (comparacion == 0) {
		// Tengo ambos hijos
		if (abb -> izquierdo && abb -> derecho) {
		}
		// Tengo solo un hijo
		else if (abb -> izquierdo || abb -> derecho) {
			abb_t* hijo = abb -> izquierdo ? abb -> izquierdo : abb -> derecho;
			free(abb);
			return hijo; // El hijo va a ser retornado al nodo que llamo abb_quitar con su izquiredo o derecho.
		}
		// No tengo hijos
		else {
			free(abb);
			return NULL;
		}
	}
	else if (comparacion < 0)
		abb -> izquierdo = abb_quitar(abb -> izquierdo, elemento, comparador);
	else
		abb -> derecho = abb_quitar(abb -> derecho, elemento, comparador);

	return abb;
}

size_t
abb_con_cada_elemento_preorden_aux(abb_t* abb, bool (*funcion)(void*, void*), void* aux) {
	if (!abb)
		return 0;
	
	funcion(abb -> elemento, aux);
	abb_con_cada_elemento_preorden_aux(abb -> izquierdo, funcion, aux);
	abb_con_cada_elemento_preorden_aux(abb -> derecho, funcion, aux);

	return 0;
}

size_t
abb_con_cada_elemento_inorden_aux(abb_t* abb, bool (*funcion)(void*, void*), void* aux) {
	if (!abb)
		return 0;
	
	abb_con_cada_elemento_inorden_aux(abb -> izquierdo, funcion, aux);
	funcion(abb -> elemento, aux);
	abb_con_cada_elemento_inorden_aux(abb -> derecho, funcion, aux);

	return 0;
}

size_t
abb_con_cada_elemento(abb_t* abb, recorrido_abb_t recorrido, bool (*funcion)(void*, void*), void* aux) {
	if (recorrido == PREORDEN)
		return abb_con_cada_elemento_preorden_aux(abb, funcion, aux);
	else if (recorrido == INORDEN)
		return abb_con_cada_elemento_inorden_aux(abb, funcion, aux);

	return 0;
}

void
abb_destruir(abb_t* abb) {
	return;
}