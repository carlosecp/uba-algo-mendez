#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

/* Lista: Creacion */

void
puedoCrearYDestruirUnaLista()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Crear lista devuelve la lista")
	pa2m_afirmar(lista_primero(lista) == NULL, "Nodo inicial apunta a NULL");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "Nodo final apunta a NULL");
	pa2m_afirmar(lista_vacia(lista), "Lista se crea vacia");

	lista_destruir(lista);
}

/* Lista: Insercion */

void
dadaUnaListaVacia_alInsertarUnElementoExitosamente_devuelveLaLista()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		"Insertar devuelve la lista");

	lista_destruir(lista);
}

void
dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL()
{
	lista_t* lista = NULL;

	pa2m_afirmar(lista_insertar(lista, NULL) == NULL,
		"Insertar en lista NULL devuelve NULL");
}

void
dadaUnaListaVacia_alInsertarUnElementoExitosamente_laListaQuedaConTamanio1()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);

	pa2m_afirmar(lista_tamanio(lista) == 1,
		"Para lista con 1 elemento el tamanio es 1")

	lista_destruir(lista);
}

void
dadaUnaListaCon1Elemento_alPedirElPrimeroYUltimoElemento_devuelveElMismoElemento()
{
	lista_t* lista = lista_crear();

	double elemento = 3.14159;
	lista = lista_insertar(lista, &elemento);

	pa2m_afirmar(*(double*)lista_primero(lista) == elemento,
		"Para lista con 1 elemento, ese elemento es el primero");
	pa2m_afirmar(*(double*)lista_ultimo(lista) == elemento,
		"Para lista con 1 elemento, ese elemento es el ultimo");

	lista_destruir(lista);
}

void
dadaUnaListaVacia_alInsertar10ElementosExitosamente_laListaQuedaConTamanio10()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);

	pa2m_afirmar(lista_tamanio(lista) == 10,
		"Para lista con 10 elementos el tamanio es 10")

	lista_destruir(lista);
}

void
dadaUnaListaVacia_alInsertarMultiplesElementos_seAgreganExitosamente()
{
	lista_t* lista = lista_crear();

	char a = 'a', b = 'b', c = 'c';

	lista = lista_insertar(lista, &a);
	lista = lista_insertar(lista, &b);
	lista = lista_insertar(lista, &c);

	pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 0) == a, 
		"Primer elemento insertado en posicion 0 es 'a'");
	pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 1) == b, 
		"Segundo elemento insertado en posicion 1 es 'b'");
	pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 2) == c, 
		"Tercer elemento insertado en posicion 2 es 'c'");

	lista_destruir(lista);
}

/* Lista: Insercion en Posicion Especifica */

void
dadaUnaListaNULL_alIntentarInsertarUnElementoEnUnaPosicionEspecifica_devuelveNULL()
{
	lista_t* lista = NULL;

	pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 0) == NULL,
		"Insertar elemento en posicion especifica en lista NULL devuelve NULL");

	lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alInsertarUnElementoEnLaPosicion0_seAgregaAlInicio()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);

	double elemento = 3.14159;
	lista = lista_insertar_en_posicion(lista, &elemento, 0);

	pa2m_afirmar(*(double*)lista_primero(lista) == elemento,
		"Insertar elemento en posicion 0 ubica el elemento al inicio");

	lista_destruir(lista);
}

void
dadaUnaLista_alInsertarUnElementoEnUnaPosicionInvalida_seAgregaAlFinal()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);

	double elemento = 3.14159;
	lista = lista_insertar_en_posicion(lista, &elemento, 10);

	pa2m_afirmar(*(double*)lista_ultimo(lista) == elemento,
		"Nodo final es igual a 3.14159");

	lista_destruir(lista);
}

void
dadaUnaListaCon10Elementos_alInsertarUnElementoEnLaPosicion5_seAgregaExitosamente()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);

	double elemento = 3.14159;
	lista = lista_insertar_en_posicion(lista, &elemento, 5);

	pa2m_afirmar(*(double*)lista_elemento_en_posicion(lista, 5) == elemento,
		"Elemento insertado en posicion 5 es 3.14159");

	lista_destruir(lista);
}

/* Lista: Eliminacion */

void
dadaUnaListaNULL_alIntentarQuitalUnElemento_devuelveNULL()
{
	lista_t* lista = NULL;

	pa2m_afirmar(lista_quitar(lista) == NULL,
		"Quitar elemento de lista NULL devuelve NULL");

	lista_destruir(lista);
}

void
dadaUnaListaVacia_alIntentarQuitalUnElemento_devuelveNULL()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_quitar(lista) == NULL,
		"Quitar elemento de lista vacia devuelve NULL");

	lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alQuitarElUltimoElementoExitosamente_devuelveElElemento()
{
	lista_t* lista = lista_crear();

	double elemento = 3.14159;
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, &elemento);

	pa2m_afirmar(*(double*)lista_quitar(lista) == elemento,
		"Quitar elemento devuelve el elemento");

	lista_destruir(lista);
}

void
dadaUnaListaCon1Elemento_alQuitarElElemento_elNodoInicialYFinalApuntanANULL()
{
	lista_t* lista = lista_crear();

	double elemento = 3.14159;
	lista = lista_insertar(lista, &elemento);
	lista_quitar(lista);

	pa2m_afirmar(lista_primero(lista) == NULL,
		"Para lista con 1 elemento, al quitar el elemento nodo inicial apunta a NULL");
	pa2m_afirmar(lista_ultimo(lista) == NULL,
		"Para lista con 1 elemento, al quitar el elemento nodo final apunta a NULL");

	lista_destruir(lista);
}

void
dadaUnaListaCon5Elementos_alQuitarLos2UltimosElementosExitosamente_laListaQuedaConTamanio3()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista_quitar(lista);
	lista_quitar(lista);

	pa2m_afirmar(lista_tamanio(lista) == 3,
		"Para lista con 5 elementos, al quitar los 2 ultimos elementos el tamanio es 3");

	lista_destruir(lista);
}

/* Lista: Eliminacion en Posicion Especifica */

/* Lista: Acceso Elementos */

void
dadaUnaListaNULL_alAccederAUnElemento_devuelveNULL()
{
	lista_t* lista = NULL;

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		"Acceder lista NULL devuelve NULL");

	lista_destruir(lista);
}

void
dadaUnaListaVacia_alAccederAUnElemento_devuelveNULL()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		"Acceder lista vacia devuelve NULL");

	lista_destruir(lista);
}

void
dadaUnaLista_alAccederAUnElementoEnUnaPosicionInvalida_devuelveNULL()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_elemento_en_posicion(lista, 5) == NULL,
		"Acceder posicion invalida devuelve NULL");

	lista_destruir(lista);
}

void
dadaUnaListaCon3Elementos_alAccederAlElementoEnLaPosicion1_devuelveElElemento()
{
	lista_t* lista = lista_crear();

	double elemento = 3.14159;
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, &elemento);
	lista = lista_insertar(lista, NULL);

	pa2m_afirmar(*(double*)lista_elemento_en_posicion(lista, 1) == elemento,
		"Segundo elemento es 3.14159")

	lista_destruir(lista);
}

int
main()
{
	pa2m_nuevo_grupo("Lista: Creacion");
	puedoCrearYDestruirUnaLista();

	pa2m_nuevo_grupo("Lista: Insercion");
	dadaUnaListaVacia_alInsertarUnElementoExitosamente_devuelveLaLista();
	dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL();
	dadaUnaListaVacia_alInsertarUnElementoExitosamente_laListaQuedaConTamanio1();
	dadaUnaListaCon1Elemento_alPedirElPrimeroYUltimoElemento_devuelveElMismoElemento();
	dadaUnaListaVacia_alInsertar10ElementosExitosamente_laListaQuedaConTamanio10();
	dadaUnaListaVacia_alInsertarMultiplesElementos_seAgreganExitosamente();

	pa2m_nuevo_grupo("Lista: Insercion en Posicion Especifica");
	dadaUnaListaNULL_alIntentarInsertarUnElementoEnUnaPosicionEspecifica_devuelveNULL();
	dadaUnaListaConVariosElementos_alInsertarUnElementoEnLaPosicion0_seAgregaAlInicio();
	dadaUnaLista_alInsertarUnElementoEnUnaPosicionInvalida_seAgregaAlFinal();
	dadaUnaListaCon10Elementos_alInsertarUnElementoEnLaPosicion5_seAgregaExitosamente();

	pa2m_nuevo_grupo("Lista: Eliminacion");
	dadaUnaListaNULL_alIntentarQuitalUnElemento_devuelveNULL();
	dadaUnaListaVacia_alIntentarQuitalUnElemento_devuelveNULL();
	dadaUnaListaConVariosElementos_alQuitarElUltimoElementoExitosamente_devuelveElElemento();
	dadaUnaListaCon1Elemento_alQuitarElElemento_elNodoInicialYFinalApuntanANULL();
	dadaUnaListaCon5Elementos_alQuitarLos2UltimosElementosExitosamente_laListaQuedaConTamanio3();

	pa2m_nuevo_grupo("Lista: Eliminacion en Posicion Especifica");

	pa2m_nuevo_grupo("Lista: Acceso Elementos");
	dadaUnaListaNULL_alAccederAUnElemento_devuelveNULL();
	dadaUnaListaVacia_alAccederAUnElemento_devuelveNULL();
	dadaUnaLista_alAccederAUnElementoEnUnaPosicionInvalida_devuelveNULL();
	dadaUnaListaCon3Elementos_alAccederAlElementoEnLaPosicion1_devuelveElElemento();
}
