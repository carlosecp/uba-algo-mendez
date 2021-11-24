#include "casilla.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

casilla_t* casilla_crear() {
    return NULL;
}

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento, hash_destruir_dato_t destruir_elemento, size_t* cantidad_elementos) {
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
        if (destruir_elemento)
			destruir_elemento(casilla->elemento);

        casilla->elemento = elemento;
        return casilla;
    } else {
        casilla->siguiente = casilla_insertar(casilla->siguiente, clave, elemento, destruir_elemento, cantidad_elementos);
    }

    return casilla;
}

int casilla_quitar(casilla_t** casilla, const char* clave, hash_destruir_dato_t destruir_elemento, size_t* cantidad_elementos) {
    if (!casilla || !clave)
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

void* casilla_obtener(casilla_t* casilla, const char* clave) {
    if (!casilla || !clave)
        return NULL;

    if (strcmp(casilla->clave, clave) == 0)
        return casilla->elemento;

    return casilla_obtener(casilla->siguiente, clave);
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

void casilla_con_cada_clave(casilla_t* casilla, hash_t* hash, bool (*funcion)(hash_t*, const char*, void*), void* aux, size_t* cantidad_recorridos) {
    if (!casilla || !cantidad_recorridos)
        return;

    (*cantidad_recorridos)++;

    bool continuar_recorrido = true;
    if (funcion)
        continuar_recorrido = funcion(hash, casilla->elemento, aux);

    if (continuar_recorrido)
        casilla_con_cada_clave(casilla->siguiente, hash, funcion, aux, cantidad_recorridos);
}

void casilla_copiar_casillas(casilla_t* origen, hash_t* destino) {
	if (!origen || !destino)
		return;

	hash_insertar(destino, origen->clave, origen->elemento);

	casilla_copiar_casillas(origen->siguiente, destino);
}

// BORRAR

void imprimir_casilla(casilla_t* casilla) {
	if (!casilla)
		return;

	estudiante_t est = *(estudiante_t*)casilla->elemento;
	printf(" {%s: {%s, %li}} ", casilla->clave, est.nombre, est.padron);
	imprimir_casilla(casilla->siguiente);
}

void imprimir_hash(hash_t* hash) {
	for (size_t i = 0; i < hash->cantidad_casillas; i++) {
		printf("\t%li\t", i);
		if (hash->casillas[i] == NULL) {
			printf("---");
		} else {
			imprimir_casilla(hash->casillas[i]);
		}
		printf("\n");
	}
}

