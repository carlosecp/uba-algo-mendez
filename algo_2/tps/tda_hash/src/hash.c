#include "hash.h"
#include <stdlib.h>

struct hash {
	hash_destruir_dato_t destruir_elemento;
	size_t capacidad_maxima;
	size_t cantidad_elementos;
};

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial)
{
	hash_t* hash = malloc(sizeof(hash_t));

	if (!hash)
		return NULL;

	hash->destruir_elemento = destruir_elemento;
	hash->capacidad_maxima = capacidad_inicial >= 3 ? capacidad_inicial : 3;
	hash->cantidad_elementos = 0;

	return hash;
}

size_t hash_cantidad(hash_t* hash)
{
	if (!hash)
		return 0;

	return hash->cantidad_elementos;
}

void hash_destruir(hash_t* hash)
{
	if (!hash)
		return;

	free(hash);
}
