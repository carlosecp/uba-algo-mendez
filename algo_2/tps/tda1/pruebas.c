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
                 "Para lista con 1 elemento el tamanio es 1");

    lista_destruir(lista);
}

void
dadaUnaListaCon1Elemento_alPedirElPrimerYUltimoElemento_devuelveElMismoElemento() {
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
dadaUnaListaVacia_alInsertarMultiplesElementosExitosamente_losElementosQuedanEnElOrdenCorrecto() {
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
dadaUnaListaConVariosElementos_alInsertarUnElementoEnLaPosicion0Exitosamente_elElementoSeInsertaAlInicio() {
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
dadaUnaLista_alIntentarInsertarUnElementoEnUnaPosicionInvalida_elElementoSeInsertaAlFinal() {
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
dadaUnaListaConVariosElementos_alInsertarUnElementoEnUnaPosicionEspecificaExitosamente_losElementosQuedanEnElOrdenCorrecta() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', e = 'e', f = 'f';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &e);
    lista = lista_insertar(lista, &f);

    char d = 'd';
    lista = lista_insertar_en_posicion(lista, &d, 3);

    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 3) == d,
                 "Elemento insertado en posicion 3 es 'd'");
    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 2) == c,
                 "Elemento que antes estaba en la posicion anterior al insertado sigue siendo 'c'");
    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 4) == e,
                 "Elemento que que le sigue al elemento insertado es igual a 'e'");

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
dadaUnaListaConVariosElementos_alQuitarTodosElementosExitosamente_laListaQuedaVacia() {
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
    pa2m_afirmar(
        *(char*)lista_elemento_en_posicion(lista, 2) == d,
        "Al quitar un elemento especifico, el elemento que le seguia toma su lugar");

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
dadaUnaListaConVariosElementos_alQuitarElElementoEnLaPosicion0Exitosamente_seEliminaElPrimerElemento()
{
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar(lista, &e);

    pa2m_afirmar(*(char*)lista_quitar_de_posicion(lista, 0) == a,
        "Quitar elemento en la posicion 0 efectivamente quita el primer elemento");
    
    lista_destruir(lista);
}

void
dadaUnaListaCon5Elementos_alQuitarUnElementoEnUnaPosicionEspecificaExitosamente_laListaQuedaConTamanio4() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar(lista, &e);
    lista_quitar_de_posicion(lista, 1);

    pa2m_afirmar(lista_tamanio(lista) == 4,
        "Para una lista con 5 elementos, al quitar un elemento especifico la lista queda con tamanio 4");

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
dadaUnaListaConVariosElementos_alAccederAlElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento() {
    lista_t* lista = lista_crear();

    double elemento = 3.14159;
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, &elemento);
    lista = lista_insertar(lista, NULL);

    pa2m_afirmar(*(double*)lista_elemento_en_posicion(lista, 1) == elemento,
                 "Segundo elemento es 3.14159");

    lista_destruir(lista);
}

/* Cola: Creacion */

void
puedoCrearYDestruirUnaCola()
{
    cola_t* cola = cola_crear();

    pa2m_afirmar(cola != NULL, "Crear lista devuelve la lista");
    pa2m_afirmar(cola_frente(cola) == NULL, "El frente de la cola cola se crea NULL");
    pa2m_afirmar(cola_vacia(cola), "Cola se crea vacia");

    cola_destruir(cola);
}

/* Cola: Encolar */

void
dadaUnaColaNULL_alIntentarEncolarUnElemento_devuelveNULL()
{
    cola_t* cola = NULL;

    pa2m_afirmar(cola_encolar(cola, NULL) == NULL,
                 "Encolar en cola NULL devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaVacia_alEncolar10ElementosExitosamente_laColaQuedaConTamanio10()
{
    cola_t* cola = cola_crear();

    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);

    pa2m_afirmar(cola_tamanio(cola) == 10,
                 "Para cola con 10 elementos el tamanio es 10");

    cola_destruir(cola);
}

void
dadaUnaColaConUnElementoEnElFrente_alEncolarMultiplesElementosExitosamente_todosSeAgreganDetrasDelFrente()
{
    cola_t* cola = cola_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    cola = cola_encolar(cola, &a);
    cola = cola_encolar(cola, &b);
    cola = cola_encolar(cola, &c);
    cola = cola_encolar(cola, &d);
    cola = cola_encolar(cola, &e);

    pa2m_afirmar(*(char*)cola_frente(cola) == a,
                 "Al encolar multiples elementos, el primer elemento se mantiene al frente de la cola");

    cola_destruir(cola);
}

/* Cola: Desencolar */

void
dadaUnaColaNULL_alIntentarDesencolarUnElemento_devuelveNULL()
{
    cola_t* cola = NULL;

    pa2m_afirmar(cola_desencolar(cola) == NULL,
                 "Desencolar en cola NULL, devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaVacia_alIntentarDesencolarUnElemento_devuelveNULL()
{
    cola_t* cola = cola_crear();

    pa2m_afirmar(cola_desencolar(cola) == NULL,
                 "Desencolar en cola vacia, devuelve NULL");

    cola_destruir(cola);
}

/* Cola: Acceso Frente */

void
dadaUnaColaNULL_alAccederAlElementoDelFrente_devuelveNULL();

void
dadaUnaColaVacia_alAccederAlElementoDelFrente_devuelveNULL();

void
dadaUnaColaConVariosElemento_alAccederAlElementoDelFrente_devuelveElElemento();

int
main() {
    pa2m_nuevo_grupo("Lista: Creacion");
    puedoCrearYDestruirUnaLista();

    pa2m_nuevo_grupo("Lista: Insercion");
    dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL();
    dadaUnaListaVacia_alInsertarUnElementoExitosamente_devuelveLaLista();
    dadaUnaListaVacia_alInsertarUnElementoExitosamente_laListaQuedaConTamanio1();
    dadaUnaListaCon1Elemento_alPedirElPrimerYUltimoElemento_devuelveElMismoElemento();
    dadaUnaListaVacia_alInsertar10ElementosExitosamente_laListaQuedaConTamanio10();
    dadaUnaListaVacia_alInsertarMultiplesElementosExitosamente_losElementosQuedanEnElOrdenCorrecto();

    pa2m_nuevo_grupo("Lista: Insercion en Posicion Especifica");
    dadaUnaListaNULL_alIntentarInsertarUnElementoEnUnaPosicionEspecifica_devuelveNULL();
    dadaUnaListaConVariosElementos_alInsertarUnElementoEnLaPosicion0Exitosamente_elElementoSeInsertaAlInicio();
    dadaUnaLista_alIntentarInsertarUnElementoEnUnaPosicionInvalida_elElementoSeInsertaAlFinal();
    dadaUnaListaConVariosElementos_alInsertarUnElementoEnUnaPosicionEspecificaExitosamente_losElementosQuedanEnElOrdenCorrecta();

    pa2m_nuevo_grupo("Lista: Eliminacion");
    dadaUnaListaNULL_alIntentarQuitarUnElemento_devuelveNULL();
    dadaUnaListaVacia_alIntentarQuitarUnElemento_devuelveNULL();
    dadaUnaListaConVariosElementos_alQuitarElUltimoElementoExitosamente_devuelveElElemento();
    dadaUnaListaCon1Elemento_alQuitarElElemento_elNodoInicialYFinalApuntanANULL();
    dadaUnaListaCon5Elementos_alQuitarLos2UltimosElementosExitosamente_laListaQuedaConTamanio3();
    dadaUnaListaConVariosElementos_alQuitarTodosElementosExitosamente_laListaQuedaVacia();

    pa2m_nuevo_grupo("Lista: Eliminacion en Posicion Especifica");
    dadaUnaListaNULL_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL();
    dadaUnaListaVacia_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL();
    dadaUnaListaConVariosElementos_alQuitarUnElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento();
    dadaUnaListaConVariosElementos_alQuitarElElementoEnLaPosicion0Exitosamente_seEliminaElPrimerElemento();
    dadaUnaListaCon5Elementos_alQuitarUnElementoEnUnaPosicionEspecificaExitosamente_laListaQuedaConTamanio4();

    pa2m_nuevo_grupo("Lista: Acceso Elementos");
    dadaUnaListaNULL_alAccederAUnElemento_devuelveNULL();
    dadaUnaListaVacia_alAccederAUnElemento_devuelveNULL();
    dadaUnaLista_alAccederAUnElementoEnUnaPosicionInvalida_devuelveNULL();
    dadaUnaListaConVariosElementos_alAccederAlElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento();

    pa2m_nuevo_grupo("Cola: Creacion");
    puedoCrearYDestruirUnaCola();

    pa2m_nuevo_grupo("Cola: Encolado");
    dadaUnaColaNULL_alIntentarEncolarUnElemento_devuelveNULL();
    dadaUnaColaVacia_alEncolar10ElementosExitosamente_laColaQuedaConTamanio10();
    dadaUnaColaConUnElementoEnElFrente_alEncolarMultiplesElementosExitosamente_todosSeAgreganDetrasDelFrente();

    pa2m_nuevo_grupo("Cola: Desencolado");
    dadaUnaColaNULL_alIntentarDesencolarUnElemento_devuelveNULL();
    dadaUnaColaVacia_alIntentarDesencolarUnElemento_devuelveNULL();

    pa2m_nuevo_grupo("Cola: Acceso Frente");
    /* dadaUnaColaNULL_alAccederAlElementoDelFrente_devuelveNULL(); */
    /* dadaUnaColaVacia_alAccederAlElementoDelFrente_devuelveNULL(); */
    /* dadaUnaColaConVariosElemento_alAccederAlElementoDelFrente_devuelveElElemento(); */
}
