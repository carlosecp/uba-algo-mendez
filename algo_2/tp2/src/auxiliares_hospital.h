#ifndef AUXILIARES_HOSPITAL_H_
#define AUXILIARES_HOSPITAL_H_

#include "lista.h"
#include "abb.h"

struct _hospital_pkm_t {
    lista_t* entrenadores;
    abb_t* pokemones;
};

struct _entrenador_t {
    int id;
    char* nombre;
    lista_t* pokemones;
};

struct _pkm_t {
    char* nombre;
    size_t nivel;
};

#endif
