#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

/* PRUEBAS DE LISTA */

void
alCrearUnaLista_seCreaExitosamente()
{
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "La lista se crea exitosamente");
	pa2m_afirmar(lista -> nodo_inicio == NULL, "El nodo de inicio de la lista es igual a NULL");
	pa2m_afirmar(lista -> nodo_fin == NULL, "El nodo de fin de la lista es igual a NULL");

	lista_destruir(lista);
}

int
main()
{
  pa2m_nuevo_grupo("Pruebas de creacion de lista");
  alCrearUnaLista_seCreaExitosamente();

  return pa2m_mostrar_reporte();
}
