#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

/* Lista -> Creacion */

void
alCrearUnaListaExitosamente_devuelveLaLista()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Crear una lista devuelve la lista")

	lista_destruir(lista);
}

void
alCrearUnaListaExitosamente_elNodoInicialYFinalApuntanANULL()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_primero(lista) == NULL, "Nodo inicial apunta a NULL");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "Nodo final apunta a NULL");

	lista_destruir(lista);
}

void
alCrearUnaListaExitosamente_elTamanioEsIgualA0()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_vacia(lista), "Lista se crea vacia");

	lista_destruir(lista);
}

/* Lista -> Insercion */

void
dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL()
{
	pa2m_afirmar(lista_insertar(NULL, NULL) == NULL,
		"Insertar en lista NULL devuelve NULL");
}

void
dadaUnaLista_alInsertarUnElementoExitosamente_devuelveLaLista()
{
	lista_t* lista = lista_crear();

	lista = lista_insertar(lista, NULL);
	pa2m_afirmar(lista != NULL, "Insertar devuelve la lista");

	lista_destruir(lista);
}

void
dadaUnaLista_alInsertarUnElemento_seAgregaElElementoAlFinalDeLaLista()
{
	lista_t* lista = lista_crear();

	double elemento = 3.14159;
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, NULL);
	lista = lista_insertar(lista, &elemento);

	pa2m_afirmar(*(double*)lista_ultimo(lista) == elemento,
		"El ultimo elemento es 3.14159");

	lista_destruir(lista);
}

void
dataUnaLista_alInsertarMultiplesElementos_seAgreganExitosamente()
{
	lista_t* lista = lista_crear();

	double elemento_1 = 3.14159;
	double elemento_2 = 2.71828;
	double elemento_3 = 0.83463;

	lista = lista_insertar(lista, &elemento_1);
	lista = lista_insertar(lista, &elemento_2);
	lista = lista_insertar(lista, &elemento_3);

	lista_destruir(lista);
}

void
dadaUnaLista_alInsertarUnElemento_seIncrementaLaCantidadDeElementos()
{
}

int
main()
{
	pa2m_nuevo_grupo("Pruebas Creacion Lista");
	alCrearUnaListaExitosamente_devuelveLaLista();
	alCrearUnaListaExitosamente_elNodoInicialYFinalApuntanANULL();
	alCrearUnaListaExitosamente_elTamanioEsIgualA0();

	pa2m_nuevo_grupo("Pruebas Insercion Lista");
	dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL();
	dadaUnaLista_alInsertarUnElementoExitosamente_devuelveLaLista();
	dadaUnaLista_alInsertarUnElemento_seAgregaElElementoAlFinalDeLaLista();

	pa2m_nuevo_grupo("Pruebas Multiple Insercion Lista");
}
