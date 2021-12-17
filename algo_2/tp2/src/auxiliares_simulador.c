#include "auxiliares_simulador.h"

#include <stdio.h>
#include <string.h>

pokemon_en_recepcion_t* preparar_pokemon_para_recepcion(pokemon_t* pokemon, char* nombre_entrenador) {
	if (!pokemon || !nombre_entrenador)
		return NULL;

	pokemon_en_recepcion_t* pokemon_en_recepcion = malloc(sizeof(pokemon_en_recepcion_t));
	if (!pokemon_en_recepcion)
		return NULL;

	char* copia_nombre = malloc(strlen(pokemon->nombre) + 1);
	if (!copia_nombre)
		return NULL;

	strcpy(copia_nombre, pokemon->nombre);
	pokemon_en_recepcion->nombre = copia_nombre;

	pokemon_en_recepcion->nivel = pokemon->nivel;

	char* copia_nombre_entrenador = malloc(strlen(nombre_entrenador) + 1);
	if (!copia_nombre_entrenador) {
		free(copia_nombre);
		return NULL;
	}

	strcpy(copia_nombre_entrenador, nombre_entrenador);
	pokemon_en_recepcion->nombre_entrenador = copia_nombre_entrenador;

	return pokemon_en_recepcion;
}

bool hay_pokemon_en_consultorio(InformacionPokemon pokemon_en_consultorio) {
	return pokemon_en_consultorio.nombre_pokemon && pokemon_en_consultorio.nombre_entrenador;
}

void atender_pokemon_de_menor_nivel(InformacionPokemon* pokemon_en_consultorio, pokemon_en_recepcion_t* pokemon_de_menor_nivel) {
	pokemon_en_consultorio->nombre_pokemon = malloc(strlen(pokemon_de_menor_nivel->nombre) + 1);
	pokemon_en_consultorio->nombre_entrenador = malloc(strlen(pokemon_de_menor_nivel->nombre_entrenador) + 1);

	strcpy((char*)pokemon_en_consultorio->nombre_pokemon, pokemon_de_menor_nivel->nombre);
	strcpy((char*)pokemon_en_consultorio->nombre_entrenador, pokemon_de_menor_nivel->nombre_entrenador);
}

