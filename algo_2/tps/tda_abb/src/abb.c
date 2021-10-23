#include "abb.h"

#include <stdio.h>
#include <string.h>

#include <stddef.h>
#include <stdlib.h>

nodo_abb_t* abb_insertar_recursivo_aux(nodo_abb_t* raiz, void* elemento, abb_comparador comparador);
nodo_abb_t* abb_quitar_recursivo_aux(nodo_abb_t* raiz, void* elemento, void** elemento_quitado, abb_comparador comparador);
nodo_abb_t* abb_encontrar_predecesor_inmediato_aux();
void* abb_buscar_recursivo_aux(nodo_abb_t* raiz, void* elemento, abb_comparador comparador);
size_t abb_recorrer_preorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array);
size_t abb_recorrer_inorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array);
size_t abb_recorrer_postorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array);
void abb_destruir_recursivo_aux(nodo_abb_t* raiz, void (*destructor)(void*));

abb_t*
abb_crear(abb_comparador comparador)
{
    if (!comparador)
        return NULL;

    abb_t* arbol = calloc(1, sizeof(abb_t));
    if (!arbol)
        return NULL;

    arbol -> comparador = comparador;
    return arbol;
}

abb_t*
abb_insertar(abb_t* arbol, void* elemento)
{
    if (!arbol)
        return NULL;

    arbol -> nodo_raiz = abb_insertar_recursivo_aux(arbol -> nodo_raiz, elemento, arbol -> comparador);

    return arbol;
}

void*
abb_quitar(abb_t* arbol, void* elemento)
{
	if (!arbol)
		return NULL;

	void* elemento_quitado = NULL;
	arbol -> nodo_raiz = abb_quitar_recursivo_aux(arbol -> nodo_raiz, elemento, &elemento_quitado, arbol -> comparador);

	return elemento_quitado;
}

void*
abb_buscar(abb_t* arbol, void* elemento)
{
	return abb_buscar_recursivo_aux(arbol -> nodo_raiz, elemento, arbol -> comparador);
}

bool
abb_vacio(abb_t* arbol)
{
	if (!arbol)
		return true;

    return arbol -> tamanio == 0;
}

size_t
abb_tamanio(abb_t* arbol)
{
	if (!arbol)
		return 0;

    return arbol -> tamanio;
}

void
abb_destruir(abb_t* arbol)
{
    abb_destruir_todo(arbol, NULL);
}

void
abb_destruir_todo(abb_t* arbol, void (*destructor)(void*))
{
    if (!arbol)
        return;

    abb_destruir_recursivo_aux(arbol -> nodo_raiz, destructor);
    free(arbol);
}

size_t
abb_con_cada_elemento(abb_t* arbol, abb_recorrido recorrido, bool (*funcion)(void*, void*), void* aux)
{
    return 0;
}

size_t
abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array)
{
	if (!arbol || !array)
		return 0;

	if (recorrido == PREORDEN)
		return abb_recorrer_preorden_aux(arbol -> nodo_raiz, array, tamanio_array);

	if (recorrido == INORDEN)
		return abb_recorrer_inorden_aux(arbol -> nodo_raiz, array, tamanio_array);
		
	if (recorrido == POSTORDEN)
		return abb_recorrer_postorden_aux(arbol -> nodo_raiz, array, tamanio_array);
		
	return 0;
}

nodo_abb_t*
abb_insertar_recursivo_aux(nodo_abb_t* raiz, void* elemento, abb_comparador comparador)
{
	if (!raiz) {
		nodo_abb_t* nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
		if (!nuevo_nodo)
			return NULL;

		nuevo_nodo -> elemento = elemento;
		return nuevo_nodo;
	}

	if (!comparador)
		return NULL;

	int comparacion = comparador(elemento, raiz -> elemento);
	if (comparacion <= 0)
		raiz -> izquierda = abb_insertar_recursivo_aux(raiz -> izquierda, elemento, comparador);

	else
		raiz -> derecha = abb_insertar_recursivo_aux(raiz -> derecha, elemento, comparador);
	
	return raiz;
}

nodo_abb_t*
abb_quitar_recursivo_aux(nodo_abb_t* raiz, void* elemento, void** elemento_quitado, abb_comparador comparador)
{
	if (!raiz || !comparador)
		return NULL;

	int comparacion = comparador(elemento, raiz -> elemento);
	if (comparacion == 0)
	{
		if (raiz -> izquierda && raiz -> derecha) {
		}
		else
		{
			nodo_abb_t* hijo = raiz -> derecha ? raiz -> derecha : raiz -> izquierda;
			*elemento_quitado = raiz -> elemento;
			free(raiz);
			return hijo;
		}
	}
	else if (comparacion < 0)
	{
		raiz -> izquierda = abb_quitar_recursivo_aux(raiz -> izquierda, elemento, elemento_quitado, comparador);
	}
	else
	{
		raiz -> derecha = abb_quitar_recursivo_aux(raiz -> derecha, elemento, elemento_quitado, comparador);
	}

	return raiz;
}

nodo_abb_t*
abb_encontrar_predecesor_inmediato_aux()
{
	return NULL;
}

void*
abb_buscar_recursivo_aux(nodo_abb_t* raiz, void* elemento, abb_comparador comparador)
{
	if (!raiz || !comparador)
		NULL;

	int comparacion = comparador(elemento, raiz -> elemento);
	if (comparacion == 0)
		return raiz -> elemento;

	else if (comparacion < 0)
		return abb_buscar_recursivo_aux(raiz -> izquierda, elemento, comparador);

	else
		return abb_buscar_recursivo_aux(raiz -> derecha, elemento, comparador);
}

size_t
abb_recorrer_preorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array)
{
	if (!raiz || !tamanio_array)
		return 0;

	size_t cantidad = 0;
	array[cantidad++] = raiz -> elemento;
	cantidad += abb_recorrer_preorden_aux(raiz -> izquierda, array + cantidad, tamanio_array - cantidad);
	cantidad += abb_recorrer_preorden_aux(raiz -> derecha, array + cantidad, tamanio_array - cantidad);
	
	return cantidad;
}

size_t
abb_recorrer_inorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array)
{
	if (!raiz)
		return 0;
	
	size_t cantidad = 0;
	cantidad += abb_recorrer_inorden_aux(raiz -> izquierda, array + cantidad, tamanio_array);
	array[cantidad++] = raiz -> elemento;
	cantidad += abb_recorrer_inorden_aux(raiz -> derecha, array + cantidad, tamanio_array);

	return cantidad;
}

size_t
abb_recorrer_postorden_aux(nodo_abb_t* raiz, void** array, size_t tamanio_array)
{
	if (!raiz)
		return 0;

	size_t cantidad = 0;
	cantidad += abb_recorrer_postorden_aux(raiz -> izquierda, array + cantidad, tamanio_array);
	cantidad += abb_recorrer_postorden_aux(raiz -> derecha, array + cantidad, tamanio_array);

	array[cantidad++] = raiz -> elemento;

	return cantidad;
}

void
abb_destruir_recursivo_aux(nodo_abb_t* raiz, void (*destructor)(void*))
{
    if (!raiz)
        return;

    abb_destruir_recursivo_aux(raiz -> izquierda, destructor);
    abb_destruir_recursivo_aux(raiz -> derecha, destructor);

    if (destructor)
        destructor(raiz -> elemento);

    free(raiz);
}
