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

casilla_t* casilla_insertar(casilla_t* casilla, const char* clave, void* elemento, hash_destruir_dato_t destruir_elemento, size_t* cantidad_elementos);

int casilla_quitar(casilla_t** casilla, const char* clave, hash_destruir_dato_t destruir_elemento, size_t* cantidad_elementos);

void* casilla_obtener(casilla_t* casilla, const char* clave);

void casilla_destruir(casilla_t* casilla, hash_destruir_dato_t destructor);

void casilla_con_cada_clave(casilla_t* casilla, hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux, size_t* cantidad_recorridos);

void casilla_copiar_casillas(casilla_t* origen, hash_t* destino);

// BORRAR

struct hash {
	casilla_t** casillas;
	size_t cantidad_casillas;
	size_t cantidad_elementos;
	hash_destruir_dato_t destruir_elemento;
};

typedef struct {
	size_t padron;
	char* nombre;
} estudiante_t;

void imprimir_casilla(casilla_t* casilla);

void imprimir_hash(hash_t* hash);

#endif
