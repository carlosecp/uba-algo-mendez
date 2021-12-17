#ifndef JUEGO_H_
#define JUEGO_H_

#include <stdbool.h>

#include "hospital.h"
#include "simulador.h"

typedef struct {
    simulador_t* simulador;  // simulador_t ya continene un hospital
    bool jugando;
} Juego;

void juego_inicializar(Juego* juego, hospital_t* hospital);

void juego_titulo(const char* titulo);

void juego_catch_error(const char* evento_simulado);

void juego_terminar(Juego* juego);

void juego_destruir(Juego juego);

#endif
