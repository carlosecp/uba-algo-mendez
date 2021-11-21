#ifndef __casilla_H__
#define __casilla_H__

#include "hash.h"
#include <stddef.h>

#define EXITO 0
#define ERROR -1

typedef struct casilla {
	const char* clave;
	void* elemento;
    struct casilla* siguiente;
} casilla_t;

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento, size_t* cantidad_elementos);

int casilla_quitar(casilla_t** casilla, const char* clave, hash_destruir_dato_t destruir_elemento, size_t* cantidad_elementos);

void casilla_destruir(casilla_t* casilla, hash_destruir_dato_t destructor);

#endif
