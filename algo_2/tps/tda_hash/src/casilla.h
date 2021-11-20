#ifndef __casilla_H__
#define __casilla_H__

#include "hash.h"

#include <stddef.h>

typedef struct casilla {
	const char* clave;
	void* elemento;
    struct casilla* siguiente;
} casilla_t;

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento);

void casilla_destruir(casilla_t* casilla, hash_destruir_dato_t destructor);

#endif
