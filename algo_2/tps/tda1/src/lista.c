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

    nodo_t* nodo = calloc(1, sizeof(nodo_t));
    if (!nodo)
        return lista;

    nodo -> elemento = elemento;

    if (!(lista -> nodo_inicio))
        lista -> nodo_inicio = lista -> nodo_fin = nodo;
    else {
        lista -> nodo_fin -> siguiente = nodo;
        lista -> nodo_fin = nodo;
    }
    
    lista -> cantidad++;

    return lista;
}

lista_t*
lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion)
{
    return lista;
}

void*
lista_quitar(lista_t* lista)
{
    return NULL;
}

void*
lista_quitar_de_posicion(lista_t* lista, size_t posicion)
{
    return NULL;
}

void*
lista_elemento_en_posicion(lista_t* lista, size_t posicion)
{
    return NULL;
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
