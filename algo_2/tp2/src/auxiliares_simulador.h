#ifndef AUXILIARES_SIMULADOR_H__
#define AUXILIARES_SIMULADOR_H__

#include <stdlib.h>

#include "hospital.h"
#include "auxiliares_hospital.h"
#include "heap.h"
#include "simulador.h"

typedef struct {
	char* nombre_pokemon;
	char* nombre_entrenador;
	size_t nivel;
} pokemon_en_recepcion_t;

int comparador_nivel_pokemon(void* _pokemon_a, void* _pokemon_b);

void destruir_pokemon_en_recepcion(void* _pokemon);

bool destruir_dificultad(void* _dificultad, void* aux);

bool agregar_pokemones_de_entrenador_a_recepcion(entrenador_t* proximo_entrenador, lista_iterador_t* sala_de_espera_pokemones, heap_t* recepcion);

bool hay_pokemon_en_tratamiento(pokemon_en_recepcion_t pokemon_en_tratamiento);

void actualizar_pokemon_en_tratamiento(pokemon_en_recepcion_t* pokemon_en_tratamiento, heap_t* recepcion);

lista_t* agregar_dificultades_iniciales(lista_t* dificultades);

#endif
