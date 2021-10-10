#ifndef NODO_H_
#define NODO_H_

#include "lista.h"

nodo_t* nodo_crear(void* elemento);

nodo_t* nodo_en_posicion(nodo_t* inicio, size_t posicion);

nodo_t* nodo_anterior_a_posicion_aux(nodo_t* nodo_inicial, size_t posicion);

nodo_t* nodo_penultimo_aux(nodo_t* nodo_inicial);

#endif