#include "auxiliares_simulador.h"
#include "abb.h"
#include "lista.h"
#include "simulador.h"

#include <stdio.h>
#include <string.h>

int comparador_nivel_pokemon(void* _pokemon_a, void* _pokemon_b) {
	pokemon_en_recepcion_t* pokemon_a = _pokemon_a;
	pokemon_en_recepcion_t* pokemon_b = _pokemon_b;

	if (pokemon_a->nivel > pokemon_b->nivel)
		return 1;
	else if (pokemon_a->nivel < pokemon_b->nivel)
		return -1;

	return 0;
}

void destruir_pokemon_en_recepcion(void* _pokemon) {
	pokemon_en_recepcion_t* pokemon = _pokemon;
	free(pokemon->nombre_pokemon);
	free(pokemon->nombre_entrenador);
	free(pokemon);
}

pokemon_en_recepcion_t* asociar_pokemon_con_su_entrenador(pokemon_t* pokemon, char* nombre_entrenador) {
	if (!pokemon || !nombre_entrenador)
		return NULL;

	pokemon_en_recepcion_t* pokemon_en_recepcion = malloc(sizeof(pokemon_en_recepcion_t));
	if (!pokemon_en_recepcion)
		return NULL;

	char* copia_nombre = malloc(strlen(pokemon->nombre) + 1);
	if (!copia_nombre)
		return NULL;

	strcpy(copia_nombre, pokemon->nombre);
	pokemon_en_recepcion->nombre_pokemon = copia_nombre;

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

bool agregar_pokemones_de_entrenador_a_recepcion(entrenador_t* proximo_entrenador, lista_iterador_t* sala_de_espera_pokemones, heap_t* recepcion) {
	if (!proximo_entrenador)
		return false;

	for (int i = 0; i < proximo_entrenador->cantidad_pokemones; i++) {
		pokemon_t* proximo_pokemon = lista_iterador_elemento_actual(sala_de_espera_pokemones);
		if (proximo_pokemon) {
			pokemon_en_recepcion_t* pokemon_en_recepcion = asociar_pokemon_con_su_entrenador(proximo_pokemon, proximo_entrenador->nombre);
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

bool hay_pokemon_en_tratamiento(pokemon_en_recepcion_t pokemon_en_tratamiento) {
	return pokemon_en_tratamiento.nombre_pokemon && pokemon_en_tratamiento.nombre_entrenador;
}

void actualizar_pokemon_en_tratamiento(pokemon_en_recepcion_t* pokemon_en_tratamiento, heap_t* recepcion) {
	if (!pokemon_en_tratamiento)
		return;

	if (!recepcion)
		return;

	if (hay_pokemon_en_tratamiento(*pokemon_en_tratamiento))
		return;

	pokemon_en_recepcion_t* pokemon_de_menor_nivel = heap_extraer_raiz(recepcion);
	if (!pokemon_de_menor_nivel)
		return;

	pokemon_en_tratamiento->nombre_pokemon = pokemon_de_menor_nivel->nombre_pokemon;
	pokemon_en_tratamiento->nombre_entrenador = pokemon_de_menor_nivel->nombre_entrenador;
	pokemon_en_tratamiento->nivel = pokemon_de_menor_nivel->nivel;

	free(pokemon_de_menor_nivel); // El nombre y el nivel se quedan guardados como copia. Luego se liberan.
}

/* typedef struct {
	const char* nombre;
	unsigned (*calcular_puntaje)(unsigned cantidad_intentos);
	int (*verificar_nivel)(unsigned nivel_adivinado, unsigned nivel_pokemon);
	const char* (*verificacion_a_string)(int resultado_verificacion);
} DatosDificultad; */

int verificar_nivel_facil(unsigned nivel_adivinado, unsigned nivel_pokemon) {
	return (int)(nivel_pokemon - nivel_adivinado);
}

unsigned calcular_puntaje_facil(unsigned cantidad_intentos) {
	return 0;
}

const char* verificacion_a_string_facil(int resultado_verificacion) {
	if (resultado_verificacion >= 50)
		return "Te quedaste corto por mas de 50 niveles";

	if (resultado_verificacion < 50 && resultado_verificacion >= 25)
		return "Te quedaste corto por entre 25 y 50 niveles";

	if (resultado_verificacion < 25 && resultado_verificacion >= 10)
		return "Te quedaste corto por entre 10 y 25 niveles";

	if (resultado_verificacion < 10 && resultado_verificacion >= 5)
		return "Te quedaste corto por entre 5 y 10 niveles";

	if (resultado_verificacion > 0)
		return "Te quedaste corto por entre 1 y 5 niveles";

	if (resultado_verificacion < 0)
		return "Te pasaste por entre 1 y 5 niveles";

	return "Adivinaste Crack";
}

int comparador_dificultades(void* _dificultad_1, void* _dificultad_2) {
	DatosDificultadConId* dificultad_1 = _dificultad_1;
	DatosDificultadConId* dificultad_2 = _dificultad_2;

	if (dificultad_1->id > dificultad_2->id)
		return 1;

	if (dificultad_1->id < dificultad_2->id)
		return -1;

	return 0;
}

// TODO: Mejorar las validaciones
// Probablemente sea mejor hacer todo esto en una funcion para cada dificultad
// Tambien deberia estar usando agregar_dificultad (no en el juego, no se ni donde)
abb_t* crear_dificultades_iniciales() {
	abb_t* dificultades = abb_crear(comparador_dificultades);
	if (!dificultades)
		return NULL;

	DatosDificultadConId* dificultad_facil = malloc(sizeof(DatosDificultadConId));
	if (!dificultad_facil)
		return NULL;

	dificultad_facil->datos_dificultad = (DatosDificultad){
		.nombre = "Facil",
		.verificar_nivel = verificar_nivel_facil,
		.verificacion_a_string = verificacion_a_string_facil,
	};

	dificultad_facil->id = (int)abb_tamanio(dificultades);
	dificultades = abb_insertar(dificultades, dificultad_facil);

	DatosDificultadConId* dificultad_media = malloc(sizeof(DatosDificultadConId));
	if (!dificultad_media)
		return NULL;

	dificultad_media->datos_dificultad = (DatosDificultad){
		.nombre = "Media",
		.verificar_nivel = verificar_nivel_facil,
		.verificacion_a_string = verificacion_a_string_facil,
	};

	dificultad_media->id = (int)abb_tamanio(dificultades);
	dificultades = abb_insertar(dificultades, dificultad_media);

	return dificultades;
}

void destruir_dificultad(void* _dificultad) {
	DatosDificultadConId* dificultad = _dificultad;
	free(dificultad);
}
