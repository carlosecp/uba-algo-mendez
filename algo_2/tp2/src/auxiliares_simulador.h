#ifndef AUXILIARES_SIMULADOR_H__
#define AUXILIARES_SIMULADOR_H__

#include <stdlib.h>

#include "hospital.h"
#include "auxiliares_hospital.h"
#include "simulador.h"
#include "heap.h"

typedef struct {
	char* nombre_pokemon;
	char* nombre_entrenador;
	size_t nivel;
} pokemon_en_recepcion_t;

int comparador_nivel_pokemon(void* _pokemon_a, void* _pokemon_b);

void destructor_pokemon_en_recepcion(void* _pokemon);

bool agregar_pokemones_de_entrenador_a_recepcion(entrenador_t* proximo_entrenador, lista_iterador_t* sala_de_espera_pokemones, heap_t* recepcion);

void actualizar_pokemon_en_consultorio(pokemon_en_recepcion_t* pokemon_en_consultorio, heap_t* recepcion);

#endif
