#include "hash.h"
#include "casilla.h"
#include <stdlib.h>

#include <stdio.h>

#define ERROR -1

struct hash {
	casilla_t** casillas;
	size_t cantidad_casillas;
	size_t cantidad_elementos;
	hash_destruir_dato_t destruir_elemento;
};

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial) {
	if (!destruir_elemento)
		return NULL;

	hash_t* hash = malloc(sizeof(hash_t));

	if (!hash)
		return NULL;

	hash->cantidad_casillas  = capacidad_inicial >= 3 ? capacidad_inicial : 3;
	hash->cantidad_elementos = 0;
	hash->destruir_elemento  = destruir_elemento;

	hash->casillas = calloc(hash->cantidad_casillas, sizeof(casilla_t*));
	if (!(hash->casillas)) {
		free(hash);
		return NULL;
	}

	return hash;
}

int generar_valor_hash(const char* clave) {
	if (!clave)
		return ERROR;

	size_t indice_hash = 0;

	while (*clave)
		indice_hash += *(clave++);

	return indice_hash;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento) {
	if (!hash || !clave)
		return ERROR;

	int indice_clave = generar_valor_hash(clave);
	if (indice_clave == ERROR)
		return ERROR;

	indice_clave %= hash->cantidad_casillas;

	hash->casillas[indice_clave] =
		casilla_insertar(hash->casillas[indice_clave], clave, elemento);

	return 0;
}

size_t hash_cantidad(hash_t* hash) {
	if (!hash)
		return 0;

	return hash->cantidad_elementos;
}

void hash_destruir(hash_t* hash) {
	if (!hash)
		return;

	free(hash->casillas);
	free(hash);
}
