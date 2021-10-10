#include "lista.h"
#include "nodo.h"
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

    nodo_t* nodo = nodo_crear(elemento);
    if (!nodo)
        return NULL;

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
    if (!lista)
        return NULL;

    nodo_t* nodo = nodo_crear(elemento);
    if (!nodo)
        return NULL;

    if (!(lista -> nodo_inicio))
        lista -> nodo_inicio = lista -> nodo_fin = nodo;

    if (posicion == 0) {
        nodo -> siguiente = lista -> nodo_inicio;
        lista -> nodo_inicio = nodo;
    }

    else if (posicion >= lista_tamanio(lista)) {
        lista -> nodo_fin -> siguiente = nodo;
        lista -> nodo_fin = nodo;
    }

    else {
        nodo_t* nodo_anterior_al_insertado =
            nodo_anterior_a_posicion_aux(lista -> nodo_inicio, posicion);
        if (!nodo_anterior_al_insertado)
            return NULL;

        nodo -> siguiente = nodo_anterior_al_insertado -> siguiente;
        nodo_anterior_al_insertado -> siguiente = nodo;
    }

    lista -> cantidad++;
    return lista;
}

void*
lista_quitar(lista_t* lista)
{
    size_t tamanio = 0;
    void* elemento_quitado = NULL;

    if (!lista || !(tamanio = lista_tamanio(lista)))
        return NULL;

    if (tamanio == 1) {
        elemento_quitado = lista_primero(lista);
        free(lista -> nodo_inicio);

        lista -> nodo_inicio = lista -> nodo_fin = NULL;
    }

    else {
        nodo_t* nodo_penultimo = nodo_penultimo_aux(lista -> nodo_inicio);
        if (!nodo_penultimo)
            return NULL;

        elemento_quitado = nodo_penultimo -> siguiente -> elemento;
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
    size_t tamanio = 0;
    void* elemento_quitado = NULL;

    if (!lista || !lista_tamanio(lista))
        return NULL;
    
    if (posicion == 0) {
        printf("QUE BONITA QUE ES LA VIDA");
    }

    else if (posicion >= lista_tamanio(lista)) {
    }

    else {
        nodo_t* nodo_anterior_al_quitado =
            nodo_anterior_a_posicion_aux(lista -> nodo_inicio, posicion);
        if (!nodo_anterior_al_quitado)
            return NULL;

        nodo_t* nodo_quitado = nodo_anterior_al_quitado -> siguiente;
        elemento_quitado = nodo_quitado -> elemento;

        nodo_anterior_al_quitado -> siguiente = nodo_quitado -> siguiente;
        free(nodo_quitado);
    }

    lista -> cantidad--;
    return elemento_quitado;
}

void*
lista_elemento_en_posicion(lista_t* lista, size_t posicion)
{
    size_t tamanio = 0;

    if (!lista || posicion >= (tamanio = lista_tamanio(lista)))
        return NULL;

    if (posicion == 0)
        return lista_primero(lista);

    if (posicion == (tamanio - 1))
        return lista_ultimo(lista);

    nodo_t* nodo = nodo_en_posicion(lista -> nodo_inicio, posicion);
    if (!nodo)
        return NULL;

    return nodo -> elemento;
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
