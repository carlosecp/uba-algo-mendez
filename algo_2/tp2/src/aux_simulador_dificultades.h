#ifndef AUX_SIMULADOR_DIFICULTADES_H__
#define AUX_SIMULADOR_DIFICULTADES_H__

#include <stddef.h>

#include "abb.h"
#include "simulador.h"

typedef struct {
    int id;
    const char* nombre;
    unsigned (*calcular_puntaje)(unsigned cantidad_intentos);
    int (*verificar_nivel)(unsigned nivel_adivinado, unsigned nivel_pokemon);
    const char* (*verificacion_a_string)(int resultado_verificacion);
} DatosDificultadConId;

/**
 *
 */
DatosDificultadConId* crear_dificultad(abb_t* dificultades, DatosDificultad datos_dificultad);

abb_t* inicializar_dificultades(DatosDificultadConId* dificultad_por_defecto);

bool dificultad_esta_en_uso(DatosDificultadConId dificultad_en_uso, DatosDificultadConId dificultad_buscada);

void destruir_dificultad(void* _dificultad);

#endif
