#ifndef __casilla_H__
#define __casilla_H__

#include <stddef.h>

typedef struct casilla {
	const char* clave;
	void* elemento;
    struct casilla* siguiente;
} casilla_t;

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento);

#endif
