#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

/* Notas:
 * La sintaxis `typedef int (*abb_comparador)(void*, void*);`
 * Quiere decir que: el tipo abb_comparador, es una funcion que toma dos
 * punteros a void y retorna int. abb_comparador es el nombre del tipo.
 */

int comparador(void* _elem_1, void* _elem_2) {
	int* elem_1 = _elem_1;
	int* elem_2 = _elem_2;
	return *elem_1 - *elem_2;
}

void dadoUnComparadorValido_puedoCrearYDestruirUnABB() {
	abb_t* arbol = abb_crear(comparador);

	pa2m_afirmar(arbol -> nodo_raiz == NULL, "Para un arbol nuevo, la raiz es NULL");
	pa2m_afirmar(arbol -> comparador == comparador, "Para un arbol nuevo, el comparador es el correcto");
	pa2m_afirmar(arbol -> tamanio == 0, "Un arbol se crea vacio");

	abb_destruir(arbol);
}

void dadoUnComparadorNULL_noPuedoCrearyDestruirUnABB() {
	abb_t* arbol = abb_crear(NULL);

	pa2m_afirmar(arbol == NULL, "No puedo crear un arbol con un comparador NULL");

	abb_destruir(arbol);
}

void dadoUnABB_alInsetarUnElemento_seDevuelveElABB() {
    abb_t* arbol = abb_crear(comparador);

    pa2m_afirmar(abb_insertar(arbol, NULL), "Al insertar un elemento en el arbol, se devuelve el arbol");

    abb_destruir(arbol);
}

void dadoUnABB_alInsertarVariosElementos_todosSeInsertanCorrectamente() {
	abb_t* arbol = abb_crear(comparador);

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	arbol = abb_insertar(arbol, &a);
	arbol = abb_insertar(arbol, &b);
	arbol = abb_insertar(arbol, &c);
	arbol = abb_insertar(arbol, &d);
	arbol = abb_insertar(arbol, &e);

	abb_destruir(arbol);
}

int main(){
  pa2m_nuevo_grupo("Pruebas de ABB: Creacion");
  dadoUnComparadorValido_puedoCrearYDestruirUnABB();
  dadoUnComparadorNULL_noPuedoCrearyDestruirUnABB();

  pa2m_nuevo_grupo("Pruebas de ABB: Insertar");
  dadoUnABB_alInsetarUnElemento_seDevuelveElABB();
  dadoUnABB_alInsertarVariosElementos_todosSeInsertanCorrectamente();

  return pa2m_mostrar_reporte();
}
