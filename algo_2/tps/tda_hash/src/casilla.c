#include "casilla.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

casilla_t* casilla_crear() {
    return NULL;
}

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento) {
	if (!casilla) {
		casilla_t* nueva_casilla = malloc(sizeof(casilla_t));
		if (!nueva_casilla)
			return NULL;

		nueva_casilla->clave = clave;
		nueva_casilla->elemento = elemento;
		nueva_casilla->siguiente = NULL;
		return nueva_casilla;
	}

	if (strcmp(casilla->clave, clave) == 0) {
		casilla -> elemento = elemento;
		return casilla;
	} else {
		casilla->siguiente = casilla_insertar(casilla->siguiente, clave, elemento);
	}

	return casilla;
}

