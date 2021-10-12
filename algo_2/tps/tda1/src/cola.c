#include "cola.h"
#include "lista.h"

cola_t* cola_crear(){
    return calloc(1, sizeof(lista_t));
}

cola_t* cola_encolar(cola_t* cola, void* elemento){
    return (cola_t*)lista_insertar_en_posicion((lista_t*)cola, elemento, cola_tamanio(cola));
}

void* cola_desencolar(cola_t* cola){
    return NULL;
}

void* cola_frente(cola_t* cola){
    return NULL;
}

size_t cola_tamanio(cola_t* cola){
    if (!cola)
        return 0;

    return ((lista_t*)cola) -> cantidad;
}

bool cola_vacia(cola_t* cola){
    if (!cola)
        return true;

    return ((lista_t*)cola) -> cantidad == 0;
}

void cola_destruir(cola_t* cola){
    lista_destruir((lista_t*)cola);
}
