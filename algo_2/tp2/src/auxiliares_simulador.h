#ifndef AUXILIARES_SIMULADOR_H__
#define AUXILIARES_SIMULADOR_H__

#include <stdlib.h>

#include "hospital.h"
#include "auxiliares_hospital.h"
#include "simulador.h"

typedef struct {
	char* nombre;
	size_t nivel;
	char* nombre_entrenador;
} pokemon_en_recepcion_t;

pokemon_en_recepcion_t* preparar_pokemon_para_recepcion(pokemon_t* pokemon, char* nombre_entrenador);

bool hay_pokemon_en_consultorio(InformacionPokemon pokemon_en_consultorio);

void atender_pokemon_de_menor_nivel(InformacionPokemon* pokemon_en_consultorio, pokemon_en_recepcion_t* pokemon_de_menor_nivel);

#endif
