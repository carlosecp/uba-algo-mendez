#include <stdio.h>
#include <stdlib.h>

#include "pa2mm.h"
#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"

/* Lista: Creacion */

void
puedoCrearYDestruirUnaLista() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista != NULL, "Crear lista devuelve la lista");
    pa2m_afirmar(lista_primero(lista) == NULL, "Nodo inicial apunta a NULL");
    pa2m_afirmar(lista_ultimo(lista) == NULL, "Nodo final apunta a NULL");
    pa2m_afirmar(lista_vacia(lista), "Lista se crea vacia");

    lista_destruir(lista);
}

/* Lista: Insercion */

void
dadaUnaListaVacia_alInsertarUnElementoExitosamente_devuelveLaLista() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
                 "Insertar devuelve la lista");

    lista_destruir(lista);
}

void
dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(lista_insertar(lista, NULL) == NULL,
                 "Insertar en lista NULL devuelve NULL");
}

void
dadaUnaListaVacia_alInsertarUnElementoExitosamente_laListaQuedaConTamanio1() {
    lista_t* lista = lista_crear();

    lista = lista_insertar(lista, NULL);

    pa2m_afirmar(lista_tamanio(lista) == 1,
                 "Para lista con 1 elemento el tamanio es 1")

        lista_destruir(lista);
}

void
dadaUnaListaCon1Elemento_alPedirElPrimeroYUltimoElemento_devuelveElMismoElemento() {
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
dadaUnaListaVacia_alInsertar10ElementosExitosamente_laListaQuedaConTamanio10() {
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
dadaUnaListaVacia_alInsertarMultiplesElementos_seAgreganExitosamente() {
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
dadaUnaListaNULL_alIntentarInsertarUnElementoEnUnaPosicionEspecifica_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(
        lista_insertar_en_posicion(lista, NULL, 0) == NULL,
        "Insertar elemento en posicion especifica en lista NULL devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alInsertarUnElementoEnLaPosicion0_seAgregaAlInicio() {
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
dadaUnaLista_alInsertarUnElementoEnUnaPosicionInvalida_seAgregaAlFinal() {
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
dadaUnaListaCon10Elementos_alInsertarUnElementoEnLaPosicion5_seAgregaExitosamente() {
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
dadaUnaListaConVariosElementos_alQuitarElUltimoElementoExitosamente_devuelveElElemento() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);

    pa2m_afirmar(*(char*)lista_quitar(lista) == c,
                 "Quitar elemento devuelve el elemento");
    pa2m_afirmar(*(char*)lista_ultimo(lista) == b,
                 "Al quitar un elemento, el nuevo elemento final es el que era "
                 "el penultimo");

    lista_destruir(lista);
}

void
dadaUnaListaNULL_alIntentarQuitarUnElemento_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(lista_quitar(lista) == NULL,
                 "Quitar elemento de lista NULL devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaVacia_alIntentarQuitarUnElemento_devuelveNULL() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_quitar(lista) == NULL,
                 "Quitar elemento de lista vacia devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaCon1Elemento_alQuitarElElemento_elNodoInicialYFinalApuntanANULL() {
    lista_t* lista = lista_crear();

    double elemento = 3.14159;
    lista = lista_insertar(lista, &elemento);
    lista_quitar(lista);

    pa2m_afirmar(lista_primero(lista) == NULL,
                 "Para lista con 1 elemento, al quitar el elemento, el nodo "
                 "inicial apunta a NULL");
    pa2m_afirmar(lista_ultimo(lista) == NULL,
                 "Para lista con 1 elemento, al quitar el elemento, el nodo "
                 "final apunta a NULL");

    lista_destruir(lista);
}

void
dadaUnaListaCon5Elementos_alQuitarLos2UltimosElementosExitosamente_laListaQuedaConTamanio3() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar(lista, &e);
    lista_quitar(lista);
    lista_quitar(lista);

    pa2m_afirmar(lista_tamanio(lista) == 3,
                 "Para lista con 5 elementos, al quitar los 2 ultimos "
                 "elementos el tamanio es 3");
    pa2m_afirmar(*(char*)lista_ultimo(lista) == c,
                 "Para lista con 5 elementos, al quitar los 2 ultimos "
                 "elementos el elemento final es el que era el tercero");

    lista_destruir(lista);
}

void
dadaUnaListaCon5Elementos_alQuitarLos5UltimosElementosExitosamente_laListaQuedaVacia() {
    lista_t* lista = lista_crear();

    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);

    pa2m_afirmar(lista_vacia(lista),
                 "Al quitar todos los elementos de la lista queda vacia");

    lista_destruir(lista);
}

/* Lista: Eliminacion en Posicion Especifica */

void
dadaUnaListaConVariosElementos_alQuitarUnElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento()
{
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar(lista, &e);

    pa2m_afirmar(*(char*)lista_quitar_de_posicion(lista, 2) == c,
                 "Quitar de posicion devuelve el elemento");

    lista_destruir(lista);
}

void
dadaUnaListaNULL_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL()
{
    lista_t* lista = NULL;

    pa2m_afirmar(lista_quitar_de_posicion(lista, 10) == NULL,
                 "Quitar de posicion en lista NULL, devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaVacia_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL()
{
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_quitar_de_posicion(lista, 10) == NULL,
                 "Quitar de posicion en lista vacia, devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaCon5Elementos_alQuitarUnElementoEnLaPosicion3Exitosamente_devuelveElElemento() {
    lista_t* lista = lista_crear();

    lista_destruir(lista);
}

/* Lista: Acceso Elementos */

void
dadaUnaListaNULL_alAccederAUnElemento_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
                 "Acceder lista NULL devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaVacia_alAccederAUnElemento_devuelveNULL() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
                 "Acceder lista vacia devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaLista_alAccederAUnElementoEnUnaPosicionInvalida_devuelveNULL() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_elemento_en_posicion(lista, 5) == NULL,
                 "Acceder posicion invalida devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaCon3Elementos_alAccederAlElementoEnLaPosicion1_devuelveElElemento() {
    lista_t* lista = lista_crear();

    double elemento = 3.14159;
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, &elemento);
    lista = lista_insertar(lista, NULL);

    pa2m_afirmar(*(double*)lista_elemento_en_posicion(lista, 1) == elemento,
                 "Segundo elemento es 3.14159");

    lista_destruir(lista);
}

/* Lista: Mixtos */

void
dadaUnaLista_sePuedenAplicarMultiplesOperacionesExitosamente() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_vacia(lista), "Lista se crea vacia");

    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);

    pa2m_afirmar(lista_tamanio(lista) == 5, "Se agregan 5 elementos");

    double elemento = 3.14159;
    lista = lista_insertar_en_posicion(lista, &elemento, 2);

    pa2m_afirmar(*(double*)lista_elemento_en_posicion(lista, 2) == elemento,
                 "Elemento 3.14159 insertado en la posicion 2");

    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);

    pa2m_afirmar(
        *(double*)lista_ultimo(lista) == elemento,
        "Tras quitar 3 elementos del final, el ultimo elemento es 3.14159");

    lista = lista_insertar_en_posicion(lista, lista_ultimo(lista), 0);
    pa2m_afirmar(*(double*)lista_primero(lista) == elemento,
                 "Ultimo elemento insertado en la posicion 0");

    double nuevo_primer_elemento = 2.71828;
    lista = lista_insertar_en_posicion(lista, &nuevo_primer_elemento, 0);

    pa2m_afirmar(*(double*)lista_primero(lista) == nuevo_primer_elemento,
                 "Elemento 2.71828 insertado en la posicion 0");
    pa2m_afirmar(
        *(double*)lista_elemento_en_posicion(lista, 1) == elemento,
        "Ultimo elemento insertado en la posicion 0, ahora esta en posicion 1");
    pa2m_afirmar(lista_tamanio(lista) == 5, "El tamanio de la lista es 5");

    lista = lista_insertar(lista, &elemento);
    lista = lista_insertar(lista, lista_quitar(lista));
    pa2m_afirmar(*(double*)lista_ultimo(lista) == elemento,
                 "Se puede quitar y volver a poner el ultimo elemento");

    lista_destruir(lista);
}

int
main() {
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
    dadaUnaListaConVariosElementos_alQuitarElUltimoElementoExitosamente_devuelveElElemento();
    dadaUnaListaNULL_alIntentarQuitarUnElemento_devuelveNULL();
    dadaUnaListaVacia_alIntentarQuitarUnElemento_devuelveNULL();
    dadaUnaListaCon1Elemento_alQuitarElElemento_elNodoInicialYFinalApuntanANULL();
    dadaUnaListaCon5Elementos_alQuitarLos2UltimosElementosExitosamente_laListaQuedaConTamanio3();
    dadaUnaListaCon5Elementos_alQuitarLos5UltimosElementosExitosamente_laListaQuedaVacia();

    pa2m_nuevo_grupo("Lista: Eliminacion en Posicion Especifica");
	dadaUnaListaConVariosElementos_alQuitarUnElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento();
	dadaUnaListaNULL_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL();
	dadaUnaListaVacia_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL();

    pa2m_nuevo_grupo("Lista: Acceso Elementos");
    dadaUnaListaNULL_alAccederAUnElemento_devuelveNULL();
    dadaUnaListaVacia_alAccederAUnElemento_devuelveNULL();
    dadaUnaLista_alAccederAUnElementoEnUnaPosicionInvalida_devuelveNULL();
    dadaUnaListaCon3Elementos_alAccederAlElementoEnLaPosicion1_devuelveElElemento();

    // pa2m_nuevo_grupo("Lista: Mixtos");
    // dadaUnaLista_sePuedenAplicarMultiplesOperacionesExitosamente();
}
