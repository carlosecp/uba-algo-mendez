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

    pa2m_afirmar(lista != NULL, "Crear una lista devuelve la lista");
    pa2m_afirmar(lista_primero(lista) == NULL, "El nodo inicial de la lista apunta a NULL");
    pa2m_afirmar(lista_ultimo(lista) == NULL, "El nodo final de la lista apunta a NULL");
    pa2m_afirmar(lista_vacia(lista), "La lista se crea vacia");

    lista_destruir(lista);
}

/* Lista: Insercion */

void
dadaUnaListaVacia_alInsertarUnElementoExitosamente_devuelveLaLista() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
                 "Insertar en una lista devuelve la lista");

    lista_destruir(lista);
}

void
dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(lista_insertar(lista, NULL) == NULL,
                 "Insertar en una lista NULL devuelve NULL");
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
                 "Para una lista con 10 elementos el tamanio es 10")

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
                 "El primer elemento insertado, cuyo valor es 'a', queda en la posicion 0");
    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 1) == b,
                 "El segundo elemento insertado, cuyo valor es 'b', queda en la posicion 1");
    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 2) == c,
                 "El tercer elemento insertado, cuyo valor es 'c', queda en la posicion 2");

    lista_destruir(lista);
}

/* Lista: Insercion en Posicion Especifica */

void
dadaUnaListaNULL_alIntentarInsertarUnElementoEnUnaPosicionEspecifica_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(
        lista_insertar_en_posicion(lista, NULL, 0) == NULL,
        "Insertar un elemento en una posicion especifica en una lista NULL devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alInsertarUnElementoEnLaPosicion0Exitosamente_elElementoSeInsertaAlInicio() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd';
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar_en_posicion(lista, &a, 0);

    pa2m_afirmar(*(char*)lista_primero(lista) == a,
                 "Insertar el elemento 'a' en la posicion 0, ubica el elemento al inicio de la lista");
    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 1) == b,
                "Tras insertar 'a' en la posicion 0, el elemento 'b', que antes estaba de primero, ahora esta en la posicion 1");

    lista_destruir(lista);
}

void
dadaUnaLista_alIntentarInsertarUnElementoEnUnaPosicionInvalida_elElementoSeInsertaAlFinal() {
    lista_t* lista = lista_crear();

    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, NULL);

    char a = 'a';
    lista = lista_insertar_en_posicion(lista, &a, 10);

    pa2m_afirmar(*(char*)lista_ultimo(lista) == a,
                 "Intentar insertar un elemento en una posicion mayor a la posible, lo inserta al final de la lista");

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
                 "El elemento insertado en la posicion 3, cuyo valor es 'd', queda en esa posicion");
    pa2m_afirmar(
        *(char*)lista_elemento_en_posicion(lista, 4) == e,
        "Tras insertar 'd' en la posicion 3, el elemento 'e', que antes estaba en la posicion 3, ahora esta en la posicion 4");

    lista_destruir(lista);
}

/* Lista: Eliminacion */

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
dadaUnaListaConVariosElementos_alQuitarElUltimoElementoExitosamente_devuelveElElemento() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);

    pa2m_afirmar(*(char*)lista_quitar(lista) == c,
                 "Quitar un elemento devuelve el elemento");
    pa2m_afirmar(*(char*)lista_ultimo(lista) == b,
                 "Al quitar un elemento, el elemento que antes estaba de penultimo, ahora es el ultimo");

    lista_destruir(lista);
}

void
dadaUnaListaCon1Elemento_alQuitarElElemento_elNodoInicialYFinalApuntanANULL() {
    lista_t* lista = lista_crear();

    char a = 'a';
    lista = lista_insertar(lista, &a);
    lista_quitar(lista);

    pa2m_afirmar(lista_primero(lista) == NULL,
                 "Para una lista con 1 elemento, al quitar el elemento, el nodo "
                 "inicial apunta a NULL");
    pa2m_afirmar(lista_ultimo(lista) == NULL,
                 "Para una lista con 1 elemento, al quitar el elemento, el nodo "
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
                 "Para una lista con 5 elementos, al quitar los 2 ultimos "
                 "elementos el tamanio es 3");

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
                 "Al quitar todos los elementos de la lista, esta queda vacia");

    lista_destruir(lista);
}

/* Lista: Eliminacion en Posicion Especifica */

void
dadaUnaListaNULL_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(lista_quitar_de_posicion(lista, 10) == NULL,
                 "Quitar un elemento en una posicion especifica en una lista NULL, devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaVacia_alIntentarQuitarUnElementoEnUnaPosicionEspecifica_devuelveNULL() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_quitar_de_posicion(lista, 10) == NULL,
                 "Quitar un elemento en una posicion especifica en una lista vacia, devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alQuitarUnElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar(lista, &e);

    pa2m_afirmar(*(char*)lista_quitar_de_posicion(lista, 2) == c,
                 "Quitar un elemento en una posicion especifica en una lista devuelve ese elemento");
    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 2) == d,
                 "Al quitar el elemento 'd' de la posicion 2, el elemento que "
                 "le seguia, cuyo valor es 'e', ahora ocupa la posicion 2");

    lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alQuitarElElementoEnLaPosicion0Exitosamente_seEliminaElPrimerElemento() {
    lista_t* lista = lista_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, &b);
    lista = lista_insertar(lista, &c);
    lista = lista_insertar(lista, &d);
    lista = lista_insertar(lista, &e);

    pa2m_afirmar(*(char*)lista_quitar_de_posicion(lista, 0) == a,
                 "Quitar un elemento en la posicion 0 efectivamente quita el "
                 "primer elemento");

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
                 "Para una lista con 5 elementos, al quitar un elemento "
                 "especifico la lista queda con tamanio 4");

    lista_destruir(lista);
}

/* Lista: Acceso Elementos */

void
dadaUnaListaNULL_alAccederAUnElemento_devuelveNULL() {
    lista_t* lista = NULL;

    pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
                 "Acceder a lista NULL devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaVacia_alAccederAUnElemento_devuelveNULL() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
                 "Acceder a lista vacia devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaLista_alAccederAUnElementoEnUnaPosicionInvalida_devuelveNULL() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_elemento_en_posicion(lista, 5) == NULL,
                 "Acceder a una posicion invalida devuelve NULL");

    lista_destruir(lista);
}

void
dadaUnaListaConVariosElementos_alAccederAlElementoEnUnaPosicionEspecificaExitosamente_devuelveElElemento() {
    lista_t* lista = lista_crear();

    char a = 'a';
    lista = lista_insertar(lista, NULL);
    lista = lista_insertar(lista, &a);
    lista = lista_insertar(lista, NULL);

    pa2m_afirmar(*(char*)lista_elemento_en_posicion(lista, 1) == a,
                 "Acceder a la posicion de un elemento de la lista, efecticamente devuelve el elemento en esa posicion");

    lista_destruir(lista);
}

/* Cola: Creacion */

void
puedoCrearYDestruirUnaCola() {
    cola_t* cola = cola_crear();

    pa2m_afirmar(cola != NULL, "Crear una cola devuelve la cola");
    pa2m_afirmar(cola_frente(cola) == NULL,
                 "El frente de la cola se crea NULL");
    pa2m_afirmar(cola_vacia(cola), "La cola se crea vacia");

    cola_destruir(cola);
}

/* Cola: Encolar */

void
dadaUnaColaNULL_alIntentarEncolarUnElemento_devuelveNULL() {
    cola_t* cola = NULL;

    pa2m_afirmar(cola_encolar(cola, NULL) == NULL,
                 "Encolar en una cola NULL devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaVacia_alEncolar10ElementosExitosamente_laColaQuedaConTamanio10() {
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
                 "Para una cola con 10 elementos el tamanio es 10");

    cola_destruir(cola);
}

void
dadaUnaColaCon1ElementoEnElFrente_alEncolarMultiplesElementosExitosamente_elPrimerElementoSigueEnElFrente() {
    cola_t* cola = cola_crear();

    char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
    cola = cola_encolar(cola, &a);
    cola = cola_encolar(cola, &b);
    cola = cola_encolar(cola, &c);
    cola = cola_encolar(cola, &d);
    cola = cola_encolar(cola, &e);

    pa2m_afirmar(*(char*)cola_desencolar(cola) == a,
                 "Luego de encolar multiples elementos, el primer elemento "
                 "encolado 'a', sigue estando en el frente de la cola");

    cola_destruir(cola);
}

/* Cola: Desencolar */

void
dadaUnaColaNULL_alIntentarDesencolarUnElemento_devuelveNULL() {
    cola_t* cola = NULL;

    pa2m_afirmar(cola_desencolar(cola) == NULL,
                 "Desencolar en una cola NULL, devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaVacia_alIntentarDesencolarUnElemento_devuelveNULL() {
    cola_t* cola = cola_crear();

    pa2m_afirmar(cola_desencolar(cola) == NULL,
                 "Desencolar en una cola vacia, devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaConVariosElementos_alDesencolarUnElemento_devuelveElElemento()
{
    cola_t* cola = cola_crear();

    char a = 'a', b = 'b', c = 'c';
    cola = cola_encolar(cola, &a);
    cola = cola_encolar(cola, &b);
    cola = cola_encolar(cola, &c);

    pa2m_afirmar(*(char*)cola_desencolar(cola) == a,
                 "Desencolar un elemento devuelve el elemento");

    cola_destruir(cola);
}

void
dadaUnaColaConVariosElementos_alDesencolarUnElemento_elSegundoElementoEncoladoAhoraEsElFrente()
{
    cola_t* cola = cola_crear();

    char a = 'a', b = 'b';
    cola = cola_encolar(cola, &a);
    cola = cola_encolar(cola, &b);
    cola_desencolar(cola);

    pa2m_afirmar(*(char*)cola_frente(cola) == b,
                 "Al desencolar el primer elemento 'a', el segundo elemento "
                 "encolado 'b', pasa a estar en el frente de la cola");

    cola_desencolar(cola);
}

void
dadaUnaColaConVariosElementos_alDesencolarTodosElementosExitosamente_laColaQuedaVacia()
{
    cola_t* cola = cola_crear();

    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola = cola_encolar(cola, NULL);
    cola_desencolar(cola);
    cola_desencolar(cola);
    cola_desencolar(cola);
    cola_desencolar(cola);
    cola_desencolar(cola);

    pa2m_afirmar(cola_vacia(cola),
                 "Al desencolar todos los elementos de una cola, esta queda vacia");

    cola_destruir(cola);
}

/* Cola: Acceso Frente */

void
dadaUnaColaNULL_alAccederAlElementoDelFrente_devuelveNULL()
{
    cola_t* cola = NULL;

    pa2m_afirmar(cola_frente(cola) == NULL,
                "Acceder al frente de una cola NULL devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaVacia_alAccederAlElementoDelFrente_devuelveNULL()
{
    cola_t* cola = cola_crear();

    pa2m_afirmar(cola_frente(cola) == NULL,
                "Acceder al frente de una cola vacia devuelve NULL");

    cola_destruir(cola);
}

void
dadaUnaColaConVariosElementos_alAccederAlElementoDelFrente_devuelveElElemento()
{
    cola_t* cola = cola_crear();

    char a = 'a', b = 'b', c = 'c';
    cola = cola_encolar(cola, &a);
    cola = cola_encolar(cola, &b);
    cola = cola_encolar(cola, &c);

    pa2m_afirmar(
        *(char*)cola_frente(cola) == a,
        "Acceder al frente de una cola, efectivamente devuelve ese elemento");

    cola_destruir(cola);
}

void
dadaUnaColaConVariosElementos_alDesencolarUnElemento_devuelveElElemento();

void
dadaUnaColaConVariosElementos_alDesencolarUnElemento_elSegundoElementoEncoladoAhoraEsElFrente();

void
dadaUnaColaCon1Elemento_alDesencolarUnElemento_laColaQuedaVacia();

int
main() {
    pa2m_nuevo_grupo("Lista: Creacion");
    puedoCrearYDestruirUnaLista();

    pa2m_nuevo_grupo("Lista: Insercion");
    dadaUnaListaNULL_alIntentarInsertarUnElemento_devuelveNULL();
    dadaUnaListaVacia_alInsertarUnElementoExitosamente_devuelveLaLista();
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
    dadaUnaColaCon1ElementoEnElFrente_alEncolarMultiplesElementosExitosamente_elPrimerElementoSigueEnElFrente();

    pa2m_nuevo_grupo("Cola: Desencolado");
    dadaUnaColaNULL_alIntentarDesencolarUnElemento_devuelveNULL();
    dadaUnaColaVacia_alIntentarDesencolarUnElemento_devuelveNULL();
    dadaUnaColaConVariosElementos_alDesencolarUnElemento_devuelveElElemento();
    dadaUnaColaConVariosElementos_alDesencolarUnElemento_elSegundoElementoEncoladoAhoraEsElFrente();
    dadaUnaColaConVariosElementos_alDesencolarTodosElementosExitosamente_laColaQuedaVacia();

    pa2m_nuevo_grupo("Cola: Acceso Frente");
    dadaUnaColaNULL_alAccederAlElementoDelFrente_devuelveNULL();
    dadaUnaColaVacia_alAccederAlElementoDelFrente_devuelveNULL();
    dadaUnaColaConVariosElementos_alAccederAlElementoDelFrente_devuelveElElemento();
    /* dadaUnaColaConVariosElemento_alAccederAlElementoDelFrente_devuelveElElemento(); */
}
