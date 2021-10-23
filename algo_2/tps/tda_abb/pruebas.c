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
comparador(void* _elem_1, void* _elem_2)
{
	int elem_1 = *(int*)_elem_1;
	int elem_2 = *(int*)_elem_2;

	if (elem_1 == elem_2)
		return 0;

	return elem_1 < elem_2 ? -1 : 1;
}

void
dadoUnComparadorValido_puedoCrearYDestruirUnABB()
{
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
dadoUnABBVacio_alInsertarElPrimerElemento_eseElementoPasaASerLaRaiz()
{
	abb_t* arbol = abb_crear(comparador);
	double pi = 3.14159;
	arbol = abb_insertar(arbol, &pi);

	pa2m_afirmar(*(double*)(arbol -> nodo_raiz -> elemento) == pi, "Al insertar el primer elemento en un arbol vacio, ese elemento pasa a ser la raiz");

	abb_destruir(arbol);
}

void
dadoUnABB_alInsertarVariosElementos_seInsertanTodosLosElementos()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 100, elem_2 = 20, elem_3 = 200, elem_4 = 10, elem_5 = 30;

	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);

	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_1) == elem_1, "El elemento 100 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_2) == elem_2, "El elemento 20 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_3) == elem_3, "El elemento 200 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_4) == elem_4, "El elemento 10 se inserto en el arbol");
	pa2m_afirmar(*(int*)abb_buscar(arbol, &elem_5) == elem_5, "El elemento 30 se inserto en el arbol");

	abb_destruir(arbol);
}

void
dadoUnABBNULL_alRecorrerElABB_seRecorrenCeroElementos()
{
	abb_t* arbol = NULL;

	void* recorridos[10];
	size_t cantidad_recorridos = abb_recorrer(arbol, PREORDEN, recorridos, 10);

	pa2m_afirmar(cantidad_recorridos == 0, "Al recorrer un ABB NULL, se recorren 0 elementos");

	abb_destruir(arbol);
}

void
dadoUnABBVacio_alRecorrerElABB_seRecorrenCeroElementos()
{
	abb_t* arbol = abb_crear(comparador);

	void* recorridos[10];
	size_t cantidad_recorridos = abb_recorrer(arbol, PREORDEN, recorridos, 10);

	pa2m_afirmar(cantidad_recorridos == 0, "Al recorrer un ABB vacio, se recorren 0 elementos");

	abb_destruir(arbol);
}

void
dadaUnABBConVariosElementosYUnVectorNULL_alRecorrerElABB_seRecorrenCeroElementos()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 100, elem_2 = 20, elem_3 = 200, elem_4 = 10, elem_5 = 30;

	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);

	size_t cantidad_recorridos = abb_recorrer(arbol, PREORDEN, NULL, 5);

	pa2m_afirmar(cantidad_recorridos == 0, "Al recorrer un ABB con un vector NULL, se recorren 0 elementos");

	abb_destruir(arbol);
}

void
dadoUnABBConVariosElementos_alRecorrerElABB_seRecorrenLaCantidadDeElementosCorrecta()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 30, elem_2 = 18, elem_3 = 14, elem_4 = 15, elem_5 = 21,
		elem_6 = 19, elem_7 = 92, elem_8 = 71, elem_9 = 55, elem_10 = 79;

	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);
	arbol = abb_insertar(arbol, &elem_6);
	arbol = abb_insertar(arbol, &elem_7);
	arbol = abb_insertar(arbol, &elem_8);
	arbol = abb_insertar(arbol, &elem_9);
	arbol = abb_insertar(arbol, &elem_10);

	void* recorridos[10];
	size_t cantidad_recorridos = abb_recorrer(arbol, PREORDEN, recorridos, 10);

	pa2m_afirmar(cantidad_recorridos == 10, "Para un ABB de 10 elementos, se pueden recorrer todos los elementos");

	abb_destruir(arbol);
}

void
dadoUnABBConDiezElementos_alRecorrerCincoElementosDelABB_seRecorrenSolamenteCincoElementos()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 30, elem_2 = 18, elem_3 = 14, elem_4 = 15, elem_5 = 21,
		elem_6 = 19, elem_7 = 92, elem_8 = 71, elem_9 = 55, elem_10 = 79;

	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);
	arbol = abb_insertar(arbol, &elem_6);
	arbol = abb_insertar(arbol, &elem_7);
	arbol = abb_insertar(arbol, &elem_8);
	arbol = abb_insertar(arbol, &elem_9);
	arbol = abb_insertar(arbol, &elem_10);	

	void* recorridos[10];
	size_t cantidad_recorridos = abb_recorrer(arbol, PREORDEN, recorridos, 5);

	pa2m_afirmar(cantidad_recorridos == 5, "Para un ABB de 10 elementos, se pueden recorrer solo 5 elementos");

	abb_destruir(arbol);
}

void
dadoUnABBConDiezElementos_alRecorrerQuinceElementos_seRecorrenSolamenteDiezElementos()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 30, elem_2 = 18, elem_3 = 14, elem_4 = 15, elem_5 = 21,
		elem_6 = 19, elem_7 = 92, elem_8 = 71, elem_9 = 55, elem_10 = 79;

	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);
	arbol = abb_insertar(arbol, &elem_6);
	arbol = abb_insertar(arbol, &elem_7);
	arbol = abb_insertar(arbol, &elem_8);
	arbol = abb_insertar(arbol, &elem_9);
	arbol = abb_insertar(arbol, &elem_10);	

	void* recorridos[10];
	size_t cantidad_recorridos = abb_recorrer(arbol, PREORDEN, recorridos, 15);

	pa2m_afirmar(cantidad_recorridos == 10, "Para un ABB de 10 elementos, si se intentan recorrer 15 elementos, solo se recorren 10");

	abb_destruir(arbol);
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoHoja_seDevuelveEseElemento()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 30, elem_2 = 18, elem_3 = 14, elem_4 = 15, elem_5 = 21;

	arbol = abb_insertar(arbol, &elem_1);
	arbol = abb_insertar(arbol, &elem_2);
	arbol = abb_insertar(arbol, &elem_3);
	arbol = abb_insertar(arbol, &elem_4);
	arbol = abb_insertar(arbol, &elem_5);

	void* elemento_quitado = abb_quitar(arbol, &elem_3);

	pa2m_afirmar(*(int*)elemento_quitado == elem_3, "Al quitar un elemento, se devuelve ese elemento");

	abb_destruir(arbol);
}

void
dadoUnABBNULL_alQuitarUnElemento_seDevuelveNULL()
{
	abb_t* arbol = NULL;
	int elem_1 = 10;

	arbol = abb_insertar(arbol, &elem_1);

	void* elemento_quitado = abb_quitar(arbol, &elem_1);

	pa2m_afirmar(elemento_quitado == NULL, "Al quitar un elemento en un arbol NULL, se devuelve NULL");
	abb_destruir(arbol);
}

void
dadoUnABBVacio_alQuitarUnElemento_seDevuelveNULL()
{
	abb_t* arbol = abb_crear(comparador);
	int elem_1 = 10;

	void* elemento_quitado = abb_quitar(arbol, &elem_1);

	pa2m_afirmar(elemento_quitado == NULL, "Al quitar un elemento en un arbol vacio, se devuelve NULL");

	abb_destruir(arbol);
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConUnHijo_seDevuelveEseElemento()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConDosHijos_seDevuelveEseElemento()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConUnHijo_elABBSigueSiendoUnABB()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConDosHijos_elABBSigueSiendoUnABB()
{
}

void
dadoUnABBConCincoElementos_alQuitarUnElemento_elTamanioDelABBEsCuatro()
{
}

void
dadoUnABBConVariosElementos_alQuitarTodosLosElementos_elABBQuedaVacio()
{
}

int
main() {
    pa2m_nuevo_grupo("Pruebas de ABB: Creacion");
    dadoUnComparadorValido_puedoCrearYDestruirUnABB();
    dadoUnComparadorNULL_noPuedoCrearyDestruirUnABB();
    // TODO: Hacer la prueba de destruir todo

    pa2m_nuevo_grupo("Pruebas de ABB: Insertar");
    dadoUnABB_alInsetarUnElemento_seDevuelveElABB();
    dadoUnABBNULL_alInsertarUnElemento_seDevuelveNULL();
    dadoUnABBVacio_alInsertarElPrimerElemento_eseElementoPasaASerLaRaiz();
    dadoUnABB_alInsertarVariosElementos_seInsertanTodosLosElementos();

	pa2m_nuevo_grupo("Pruebas de ABB: Recorrer");
	dadoUnABBNULL_alRecorrerElABB_seRecorrenCeroElementos();
	dadoUnABBVacio_alRecorrerElABB_seRecorrenCeroElementos();
	dadaUnABBConVariosElementosYUnVectorNULL_alRecorrerElABB_seRecorrenCeroElementos();
	dadoUnABBConVariosElementos_alRecorrerElABB_seRecorrenLaCantidadDeElementosCorrecta();
	dadoUnABBConDiezElementos_alRecorrerCincoElementosDelABB_seRecorrenSolamenteCincoElementos();
	dadoUnABBConDiezElementos_alRecorrerQuinceElementos_seRecorrenSolamenteDiezElementos();

	pa2m_nuevo_grupo("Pruebas de ABB: Quitar");
	dadoUnABB_alQuitarUnElementoEnUnNodoHoja_seDevuelveEseElemento();
	// dadoUnABBNULL_alQuitarUnElemento_seDevuelveNULL();
	// dadoUnABBVacio_alQuitarUnElemento_seDevuelveNULL();

	// dadoUnABBConCincoElementos_alQuitarUnElemento_elTamanioDelABBEsCuatro();
	// dadoUnABBConVariosElementos_alQuitarTodosLosElementos_elABBQuedaVacio();

    return pa2m_mostrar_reporte();
}
