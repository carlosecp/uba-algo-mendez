#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

/* PRUEBAS DE LISTA */
/* CREACION */

void
alCrearUnaLista_seCreaExitosamente()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "La lista se crea exitosamente");
	pa2m_afirmar(lista -> nodo_inicio == NULL, "El nodo de inicio de la lista es igual a NULL");
	pa2m_afirmar(lista -> nodo_fin == NULL, "El nodo de fin de la lista es igual a NULL");
	pa2m_afirmar(lista -> cantidad == 0, "La cantidad de nodos igual a 0");

	lista_destruir(lista);
}

/* INSERCION */

void
dadaUnaLista_alInsertarUnElemento_retornaLaLista()
{
	lista_t* lista = lista_crear();

	int elemento = 0;
	pa2m_afirmar(lista_insertar(lista, &elemento), "Al insertar un nodo exitosamente");

	lista_destruir(lista);
}

void
dadaUnaListaNULL_alInsertarUnElemento_retornaNULL()
{
	lista_t* lista = lista_crear();

	lista_destruir();
}


int
main()
{
  pa2m_nuevo_grupo("Pruebas de creacion de lista");
  alCrearUnaLista_seCreaExitosamente();

  return pa2m_mostrar_reporte();
}
