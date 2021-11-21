#include "casilla.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

casilla_t* casilla_crear() {
	return NULL;
}

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento, size_t* cantidad_elementos) {
    if (!casilla) {
        casilla_t* nueva_casilla = malloc(sizeof(casilla_t));
        if (!nueva_casilla)
            return NULL;

        nueva_casilla->clave = clave;
        nueva_casilla->elemento = elemento;
        nueva_casilla->siguiente = NULL;

		(*cantidad_elementos)++;

        return nueva_casilla;
    }

    if (strcmp(casilla->clave, clave) == 0) {
        free(casilla->elemento);
        casilla->elemento = elemento;
        return casilla;
    }
    else {
        casilla->siguiente =
            casilla_insertar(casilla->siguiente, clave, elemento, cantidad_elementos);
    }

    return casilla;
}

int casilla_quitar(casilla_t** casilla, const char* clave, hash_destruir_dato_t destruir_elemento, size_t* cantidad_elementos) {
    if (!casilla || !clave || !destruir_elemento)
        return ERROR;

    while (*casilla && strcmp((*casilla)->clave, clave)) {
        casilla = &((*casilla)->siguiente);
    }

    if (*casilla) {
		if (destruir_elemento)
			destruir_elemento((*casilla)->elemento);

        casilla_t* tmp = *casilla;
        *casilla = (*casilla)->siguiente;
        free(tmp);

		(*cantidad_elementos)--;
		return EXITO;
    }

    return ERROR;
}

void casilla_destruir(casilla_t* casilla, hash_destruir_dato_t destruir_elemento) {
    if (!casilla)
        return;

    if (destruir_elemento)
        destruir_elemento(casilla->elemento);

    casilla_t* siguiente = casilla->siguiente;
    free(casilla);

    casilla_destruir(siguiente, destruir_elemento);
}
