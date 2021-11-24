#include "hash.h"

#include <stdio.h>
#include <stdlib.h>

#include "casilla.h"

#define CAPACIDAD_MINIMA 3

struct hash {
    casilla_t** casillas;
    size_t cantidad_casillas;
    size_t cantidad_elementos;
    hash_destruir_dato_t destruir_elemento;
};

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash)
        return NULL;

    hash->cantidad_casillas = capacidad_inicial >= CAPACIDAD_MINIMA ? capacidad_inicial : CAPACIDAD_MINIMA;
    hash->cantidad_elementos = 0;
    hash->destruir_elemento = destruir_elemento;

    hash->casillas = calloc(hash->cantidad_casillas, sizeof(casilla_t*));
    if (!(hash->casillas)) {
        free(hash);
        return NULL;
    }

    return hash;
}

int generar_indice_hash(const char* clave) {
    if (!clave)
        return ERROR;

    size_t indice_hash = 0;

    while (*clave) indice_hash += *(clave++);

    return indice_hash;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento) {
    if (!hash || !clave)
        return ERROR;

    int indice_clave = generar_indice_hash(clave);
    if (indice_clave == ERROR)
        return ERROR;

    indice_clave %= hash->cantidad_casillas;
    hash->casillas[indice_clave] = casilla_insertar(hash->casillas[indice_clave], clave, elemento, &(hash->cantidad_elementos));
    return EXITO;
}

int hash_quitar(hash_t* hash, const char* clave) {
    if (!hash || !clave)
        return ERROR;

    int indice_clave = generar_indice_hash(clave);
    if (indice_clave == ERROR)
        return ERROR;

    indice_clave %= hash->cantidad_casillas;
    return casilla_quitar(&(hash->casillas[indice_clave]), clave, hash->destruir_elemento, &(hash->cantidad_elementos));
}

void* hash_obtener(hash_t* hash, const char* clave) {
    if (!hash || !clave)
        return NULL;

    int indice_clave = generar_indice_hash(clave);
    if (indice_clave == ERROR)
        return NULL;

    indice_clave %= hash->cantidad_casillas;
    return casilla_obtener(hash->casillas[indice_clave], clave);
}

bool hash_contiene(hash_t* hash, const char* clave) {
    if (!hash || !clave)
        return false;

    int indice_clave = generar_indice_hash(clave);
    if (indice_clave == ERROR)
        return false;

    indice_clave %= hash->cantidad_casillas;
    void* elemento = casilla_obtener(hash->casillas[indice_clave], clave);
    return elemento ? true : false;
}

size_t hash_cantidad(hash_t* hash) {
    if (!hash)
        return 0;

    return hash->cantidad_elementos;
}

void hash_destruir(hash_t* hash) {
    if (!hash)
        return;

    for (size_t i = 0; i < hash->cantidad_casillas; i++)
        casilla_destruir(hash->casillas[i], hash->destruir_elemento);

    free(hash->casillas);
    free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux) {
    if (!hash)
        return 0;

    for (size_t i = 0; i < hash->cantidad_casillas; i++)
        casilla_con_cada_clave(hash->casillas[i], hash, funcion, aux);

    return 0;
}
