#ifndef AUX_SIMULADOR_DIFICULTADES_H__
#define AUX_SIMULADOR_DIFICULTADES_H__

#include <stddef.h>

#include "abb.h"
#include "simulador.h"

typedef struct {
    int id;
    DatosDificultad datos;
} DatosDificultadConId;

abb_t* crear_dificultades_iniciales();

bool dificultad_esta_en_uso(DatosDificultadConId dificultad_en_uso, DatosDificultadConId dificultad_buscada);

void destruir_dificultad(void* _dificultad);

#endif
