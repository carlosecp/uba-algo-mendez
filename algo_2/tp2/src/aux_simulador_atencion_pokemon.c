#include "aux_simulador_atencion_pokemon.h"

#include <string.h>

int comparador_nivel_pokemon(void* _pokemon_a, void* _pokemon_b) {
	PokemonEnRecepcion* pokemon_a = _pokemon_a;
	PokemonEnRecepcion* pokemon_b = _pokemon_b;

	if (pokemon_a->nivel > pokemon_b->nivel)
		return 1;

	else if (pokemon_a->nivel < pokemon_b->nivel)
		return -1;

	return 0;
}

PokemonEnRecepcion* asociar_pokemon_con_su_entrenador(pokemon_t* pokemon, char* nombre_entrenador) {
	if (!pokemon || !nombre_entrenador)
		return NULL;

	PokemonEnRecepcion* pokemon_en_recepcion = malloc(sizeof(PokemonEnRecepcion));
	if (!pokemon_en_recepcion)
		return NULL;

	char* copia_nombre = malloc(strlen(pokemon->nombre) + 1);
	if (!copia_nombre) {
		free(pokemon_en_recepcion);
		return NULL;
	}

	char* copia_nombre_entrenador = malloc(strlen(nombre_entrenador) + 1);
	if (!copia_nombre_entrenador) {
		free(pokemon_en_recepcion);
		free(copia_nombre);
		return NULL;
	}

	strcpy(copia_nombre, pokemon->nombre);
	pokemon_en_recepcion->nombre_pokemon = copia_nombre;

	pokemon_en_recepcion->nivel = pokemon->nivel;

	strcpy(copia_nombre_entrenador, nombre_entrenador);
	pokemon_en_recepcion->nombre_entrenador = copia_nombre_entrenador;

	return pokemon_en_recepcion;
}

bool agregar_pokemones_de_entrenador_a_recepcion(entrenador_t* proximo_entrenador, lista_iterador_t* sala_de_espera_pokemones, heap_t* recepcion) {
	if (!proximo_entrenador)
		return false;

	for (int i = 0; i < proximo_entrenador->cantidad_pokemones; i++) {
		pokemon_t* proximo_pokemon = lista_iterador_elemento_actual(sala_de_espera_pokemones);
		if (proximo_pokemon) {
			PokemonEnRecepcion* pokemon_en_recepcion = asociar_pokemon_con_su_entrenador(proximo_pokemon, proximo_entrenador->nombre);
			if (!pokemon_en_recepcion)
				return false;

			size_t exito_recepcion = heap_insertar(recepcion, pokemon_en_recepcion);
			if (!exito_recepcion)
				return false;
		}

		lista_iterador_avanzar(sala_de_espera_pokemones);
	}

	return true;
}

bool actualizar_pokemon_en_tratamiento(PokemonEnRecepcion** pokemon_en_tratamiento, heap_t* recepcion) {
	if (!pokemon_en_tratamiento || !recepcion)
		return false;

	*pokemon_en_tratamiento = heap_elemento_en_raiz(recepcion);
	return true;
}

bool actualizar_cantidad_pokemones_en_recepcion(EstadisticasSimulacion* estadisticas, heap_t* recepcion) {
	if (!estadisticas || !recepcion)
		return false;

	unsigned tamanio_recepcion = (unsigned)heap_tamanio(recepcion);
	estadisticas->pokemon_en_espera = tamanio_recepcion > 0 ? tamanio_recepcion - 1 : tamanio_recepcion;
	return true;
}

void destruir_pokemon_en_recepcion(void* _pokemon) {
	if (!_pokemon)
		return;

	PokemonEnRecepcion* pokemon = _pokemon;
	free(pokemon->nombre_pokemon);
	free(pokemon->nombre_entrenador);
	free(pokemon);
}
