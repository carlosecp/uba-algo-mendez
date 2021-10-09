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

	pa2m_afirmar(lista -> nodo_inicio == NULL, "Nodo inicial apunta a NULL");
	pa2m_afirmar(lista -> nodo_fin == NULL, "Nodo final apunta a NULL");

	lista_destruir(lista);
}

void
alCrearUnaListaExitosamente_elTamanioEsIgualA0()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_tamanio(lista) == 0, "Lista se crea vacia");

	lista_destruir(lista);
}

/* Lista -> Insercion */

void
dadaUnaLista_alInsertarUnElementoExitosamente_devuelveLaLista()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "Insertar devuelve la lista");

	lista_destruir(lista);
}

void
dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL()
{
	pa2m_afirmar(lista_insertar(NULL, NULL) == NULL,
		"Insertar en lista NULL devuelve NULL");
}

void
dataUnaLista_alInsertarUnElemento_seAgregaElElementoAlFinalDeLaLista()
{
	lista_t* lista = lista_crear();


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
	dadaUnaLista_alInsertarUnElementoExitosamente_devuelveLaLista();
	dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL();
	// dataUnaLista_alInsertarUnElemento_seAgregaElElementoAlFinalDeLaLista();
}
