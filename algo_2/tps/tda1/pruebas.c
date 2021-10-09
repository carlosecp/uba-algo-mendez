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
}

void
alCrearUnaListaExitosamente_elTamanioEsIgualA0()
{
}

/* Lista -> Insercion */

void
dadaUnaLista_alInsertarUnElementoExitosamente_devuelveLaLista()
{
}

void
dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL()
{
}

void
dadaUnaLista_alInsertarUnElemento_seIncrementaLaCantidadDeElementos()
{
}

int
main()
{
	pa2m_nuevo_grupo("Pruebas creacion lista");
	alCrearUnaListaExitosamente_devuelveLaLista();
}
