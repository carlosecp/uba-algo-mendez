#include "pila.h"
#include "lista.h"

pila_t*
pila_crear()
{
	pila_t* cola = (pila_t*)malloc(sizeof(lista_t));
	if (!cola)
		return NULL;

	((lista_t*)cola) -> cantidad = 0;

    return cola;
}

pila_t* pila_apilar(pila_t* pila, void* elemento){
    return NULL;
}

void* pila_desapilar(pila_t* pila){
    return NULL;
}

void* pila_tope(pila_t* pila){
    return NULL;
}

size_t pila_tamanio(pila_t* pila){
    return 0;
}

bool pila_vacia(pila_t* pila){
    return false;
}

void pila_destruir(pila_t* pila){

}
