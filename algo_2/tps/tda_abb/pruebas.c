#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

/* Notas:
 * La sintaxis `typedef int (*abb_comparador)(void*, void*);`
 * Quiere decir que: el tipo abb_comparador, es una funcion que toma dos
 * punteros a void y retorna int. abb_comparador es el nombre del tipo.
 */

int
comparador(void* _elem_1, void* _elem_2) {
	int elem_1 = *(int*)_elem_1;
	int elem_2 = *(int*)_elem_2;

	if (elem_1 == elem_2)
		return 0;

	return elem_1 < elem_2 ? -1 : 1;
}

void
dadoUnComparadorValido_puedoCrearYDestruirUnABB() {
	abb_t* arbol = abb_crear(comparador);

	pa2m_afirmar(arbol -> nodo_raiz == NULL, "Para un arbol nuevo, la raiz es NULL");
	pa2m_afirmar(arbol -> comparador == comparador, "Para un arbol nuevo, el comparador es el correcto");
	pa2m_afirmar(abb_vacio(arbol), "Un arbol se crea vacio");

	abb_destruir(arbol);
}

void
dadoUnComparadorNULL_noPuedoCrearyDestruirUnABB() {
	abb_t* arbol = abb_crear(NULL);
	pa2m_afirmar(arbol == NULL, "No puedo crear un arbol con un comparador NULL");
	abb_destruir(arbol);
}

void
dadoUnABB_alInsetarUnElemento_seDevuelveElABB() {
    abb_t* arbol = abb_crear(comparador);
    pa2m_afirmar(abb_insertar(arbol, NULL), "Al insertar un elemento en el arbol, se devuelve el arbol");
    abb_destruir(arbol);
}

void
dadoUnABBNULL_alInsertarUnElemento_seDevuelveNULL() {
	abb_t* arbol = NULL;
	pa2m_afirmar(abb_insertar(NULL, NULL) == NULL, "Al insertar un elemento en un arbol NULL, se devuelve NULL");
	abb_destruir(arbol);
}

void
dadoUnABBVacio_alInsertarElPrimerElemento_eseElementoPasaASerLaRaiz() {
	abb_t* arbol = abb_crear(comparador);
	double pi = 3.14159;
	arbol = abb_insertar(arbol, &pi);

	pa2m_afirmar(*(double*)(arbol -> nodo_raiz -> elemento) == pi, "Al insertar el primer elemento en un arbol vacio, ese elemento pasa a ser la raiz");

	abb_destruir(arbol);
}

void
dadoUnABB_alInsertarVariosElementos_seInsertanTodosLosElementos() {
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 29498, elem_2 = 9093, elem_3 = 10707, elem_4 = 31646, elem_5 = 22646;
	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);

	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_1) == elem_1, "El elemento 29498 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_2) == elem_2, "El elemento 9093 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_3) == elem_3, "El elemento 10707 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_4) == elem_4, "El elemento 31646 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_5) == elem_5, "El elemento 22646 se inserto en el arbol");

	abb_destruir(arbol);
}

void
dadoUnABB_alInsertarVariosElementos_seInsertanEnLasPosicionesCorrectas() {
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 100, elem_2 = 20, elem_3 = 200, elem_4 = 10, elem_5 = 30,
		elem_6 = 150, elem_7 = 300;
	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);
	arbol = abb_insertar(arbol, &elem_6);
	arbol = abb_insertar(arbol, &elem_7);

	const size_t max_elementos = 7;
	void* elementos_preorden[max_elementos];
	abb_recorrer(arbol, PREORDEN, elementos_preorden, 7);
	for (size_t i = 0; i < max_elementos; i++)
		printf("Elemento: %i\n", *(int*)elementos_preorden[i]);

	printf("\n");

	void* elementos_inorden[max_elementos];
	abb_recorrer(arbol, INORDEN, elementos_inorden, 7);
	for (size_t i = 0; i < max_elementos; i++)
		printf("Elemento: %i\n", *(int*)elementos_inorden[i]);

	abb_destruir(arbol);
}

int
main(){
    pa2m_nuevo_grupo("Pruebas de ABB: Creacion");
    dadoUnComparadorValido_puedoCrearYDestruirUnABB();
    dadoUnComparadorNULL_noPuedoCrearyDestruirUnABB();
    // TODO: Hacer la prueba de destruir todo

    pa2m_nuevo_grupo("Pruebas de ABB: Insertar");
    // dadoUnABB_alInsetarUnElemento_seDevuelveElABB();
    // dadoUnABBNULL_alInsertarUnElemento_seDevuelveNULL();
    // dadoUnABBVacio_alInsertarElPrimerElemento_eseElementoPasaASerLaRaiz();
    // dadoUnABB_alInsertarVariosElementos_seInsertanTodosLosElementos();
    dadoUnABB_alInsertarVariosElementos_seInsertanEnLasPosicionesCorrectas();

    return pa2m_mostrar_reporte();
}
