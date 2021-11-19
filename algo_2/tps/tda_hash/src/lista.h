#ifndef __LISTA_H__
#define __LISTA_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * Las siguientes estructuras deberían ser privadas y no está permitido el
 * acceso directo a los campos por fuera de la implementación.
 *
 * El motivo por el cual las estructuras son públicas es para asegurarnos de que
 * la implementación realizada es la pedida
 */
typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}nodo_t;

typedef struct lista{
    nodo_t* nodo_inicio;
    nodo_t* nodo_fin;
    size_t cantidad;
}lista_t;

/**
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear();

/**
 * Inserta un elemento al final de la lista.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t* lista_insertar(lista_t* lista, void* elemento);

/**
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t* lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);

/**
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 *
 * Devuelve el elemento removido de la lista o NULL en caso de error.
 */
void* lista_quitar(lista_t* lista);

/**
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento de la lista.
 *
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.
 *
 * Devuelve el elemento removido de la lista o NULL en caso de error.
 *
 */
void* lista_quitar_de_posicion(lista_t* lista, size_t posicion);

/**
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion);

/**
 * Devuelve la cantidad de elementos almacenados en la lista.
 * Una lista que no existe no puede tener elementos.
 */
size_t lista_tamanio(lista_t* lista);

/**
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista);

#endif /* __LISTA_H__ */
