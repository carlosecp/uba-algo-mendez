#ifndef JUEGO_H_
#define JUEGO_H_

#include <stdbool.h>

#include "hospital.h"
#include "simulador.h"

typedef struct {
    simulador_t* simulador;  // simulador_t ya continene un hospital
    bool jugando;
} Juego;

void inicializar_juego(Juego* juego, hospital_t* hospital);

void mostrar_estadisticas(Juego* juego);

void atender_entrenador(Juego* juego);

void terminar_juego(Juego* juego);

void destruir_juego(Juego juego);

#endif
