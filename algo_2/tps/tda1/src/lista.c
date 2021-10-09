#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

lista_t*
lista_crear()
{
    return calloc(1, sizeof(lista_t));
}

lista_t*
lista_insertar(lista_t* lista, void* elemento)
{
    if (!lista)
        return NULL;

    nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
    if (!nodo_nuevo)
        return lista;

    nodo_nuevo -> elemento = elemento;

    if (!(lista -> nodo_inicio))
        lista -> nodo_inicio = lista -> nodo_fin = nodo_nuevo;
    else {
        lista -> nodo_fin -> siguiente = nodo_nuevo;
        lista -> nodo_fin = nodo_nuevo;
    }
    
    lista -> cantidad++;

    return lista;
}

lista_t*
lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion)
{
    if (!lista)
        return NULL;

    nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
    if (!nodo_nuevo)
        return NULL;

    nodo_nuevo -> elemento = elemento;

    if (posicion == 0) {
        nodo_nuevo -> siguiente = lista -> nodo_inicio;
        lista -> nodo_inicio = nodo_nuevo;
    }
    else if (posicion >= lista_tamanio(lista)) {
        lista -> nodo_fin -> siguiente = nodo_nuevo;
        lista -> nodo_fin = nodo_nuevo;
    }
    else {
        nodo_t* nodo_anterior_a_posicion = lista -> nodo_inicio;
        for (size_t i = 0; i < (posicion - 1); i++)
            nodo_anterior_a_posicion = nodo_anterior_a_posicion -> siguiente;

        nodo_nuevo -> siguiente = nodo_anterior_a_posicion -> siguiente;
        nodo_anterior_a_posicion -> siguiente = nodo_nuevo;
    }

    lista -> cantidad++;
    return lista;
}

void*
lista_quitar(lista_t* lista)
{
    if (!lista || !lista_tamanio(lista))
        return NULL;

    void* elemento_quitado =
        lista_elemento_en_posicion(lista, (lista_tamanio(lista) - 1));

    if (lista_tamanio(lista) == 1) {
        free(lista -> nodo_inicio);
        lista -> nodo_inicio = lista -> nodo_fin = NULL;
    }
    else {
        nodo_t* nodo_penultimo = lista -> nodo_inicio;
        for (size_t i = 0; i < (lista_tamanio(lista) - 2); i++)
            nodo_penultimo = nodo_penultimo -> siguiente;

        free(nodo_penultimo -> siguiente);
        nodo_penultimo -> siguiente = NULL;
        lista -> nodo_fin = nodo_penultimo;
    }

    lista -> cantidad--;
    return elemento_quitado;
}

void*
lista_quitar_de_posicion(lista_t* lista, size_t posicion)
{
    return NULL;
}

void*
lista_elemento_en_posicion(lista_t* lista, size_t posicion)
{
    if (!lista || posicion >= lista_tamanio(lista))
        return NULL;

    if (posicion == 0)
        return lista_primero(lista);

    if (posicion == (lista_tamanio(lista) - 1))
        return lista_ultimo(lista);

    nodo_t* nodo_en_posicion = lista -> nodo_inicio;
    for (size_t i = 0; (i < posicion) && nodo_en_posicion; i++)
        nodo_en_posicion = nodo_en_posicion -> siguiente;

    return nodo_en_posicion -> elemento;
}

void*
lista_primero(lista_t* lista)
{
    if (!lista || !(lista -> nodo_inicio))
        return NULL;

    return lista -> nodo_inicio -> elemento;
}

void*
lista_ultimo(lista_t* lista)
{
    if (!lista || !(lista -> nodo_fin))
        return NULL;

    return lista -> nodo_fin -> elemento;
}

bool
lista_vacia(lista_t* lista)
{
    if (!lista)
        return true;

    return lista_tamanio(lista) == 0;
}

size_t
lista_tamanio(lista_t* lista)
{
    if (!lista)
        return 0;

    return lista -> cantidad;
}

void
lista_destruir(lista_t* lista)
{
    if (!lista)
        return;

    while (lista -> nodo_inicio) {
        nodo_t* nodo_actual = lista -> nodo_inicio;
        lista -> nodo_inicio = nodo_actual -> siguiente;
        free(nodo_actual);
    }

    free(lista);
}

lista_iterador_t*
lista_iterador_crear(lista_t* lista)
{
    return NULL;
}

bool
lista_iterador_tiene_siguiente(lista_iterador_t* iterador)
{
    return false;
}

bool
lista_iterador_avanzar(lista_iterador_t* iterador)
{
    return false;
}

void*
lista_iterador_elemento_actual(lista_iterador_t* iterador)
{
    return NULL;
}

void
lista_iterador_destruir(lista_iterador_t* iterador)
{
}

size_t
lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto)
{
    return 0;
}
