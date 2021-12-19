#ifndef JUEGO_H_
#define JUEGO_H_

#include <stdbool.h>

#include "hospital.h"
#include "simulador.h"

typedef struct {
    simulador_t* simulador;
    bool jugando;
} Juego;

void juego_inicializar(Juego* juego, hospital_t* hospital);

void juego_titulo(const char* titulo);

void juego_prompt_exito(const char* prompt, const char* mensaje);

void juego_prompt_error(const char* prompt, const char* mensaje);

void juego_terminar(Juego* juego);

void juego_destruir(Juego juego);

#endif
