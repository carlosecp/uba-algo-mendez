#include "aux_simulador_dificultades.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"
#include "simulador.h"

#define PUNTAJE_INICIAL 100
#define PUNTAJE_MINIMO 0

#define PENALIZACION_FALLO_FACIL 1
#define PENALIZACION_FALLO_MEDIA 5
#define PENALIZACION_FALLO_DIFICIL 10

typedef struct {
	const char* nombre;
	bool tiene_nombre_repetido;
} DatosDificultadConNombreRepetido;

int comparador_dificultades(void* _dificultad_1, void* _dificultad_2) {
	DatosDificultadConId* dificultad_1 = _dificultad_1;
	DatosDificultadConId* dificultad_2 = _dificultad_2;

	if (dificultad_1->id > dificultad_2->id)
		return 1;

	if (dificultad_1->id < dificultad_2->id)
		return -1;

	return 0;
}

bool es_dificultad_con_nombre_repetido(void* _dificultad_existente, void* _nueva_dificultad) {
	DatosDificultadConId* dificultad_existente = _dificultad_existente;
	DatosDificultadConNombreRepetido* nueva_dificultad = _nueva_dificultad;

	nueva_dificultad->tiene_nombre_repetido = strcmp(dificultad_existente->nombre, nueva_dificultad->nombre) == 0;

	return !(nueva_dificultad->tiene_nombre_repetido);
}

DatosDificultadConId* crear_dificultad(abb_t* dificultades, int id, DatosDificultad datos_dificultad) {
	if (!dificultades)
		return NULL;

	if (!(datos_dificultad.nombre) ||
			!(datos_dificultad.calcular_puntaje) ||
			!(datos_dificultad.verificar_nivel) ||
			!(datos_dificultad.verificacion_a_string))
		return NULL;

	DatosDificultadConNombreRepetido datos_dificultad_nombre_repetido = {
		.nombre = datos_dificultad.nombre,
		.tiene_nombre_repetido = false,
	};

	abb_con_cada_elemento(dificultades, PREORDEN, es_dificultad_con_nombre_repetido, &datos_dificultad_nombre_repetido);

	if (datos_dificultad_nombre_repetido.tiene_nombre_repetido)
		return NULL;

	DatosDificultadConId* nueva_dificultad = malloc(sizeof(DatosDificultadConId));
	if (!nueva_dificultad)
		return NULL;

	char* copia_nombre = malloc(strlen(datos_dificultad.nombre) + 1);
	if (!copia_nombre) {
		free(nueva_dificultad);
		return NULL;
	}

	strcpy(copia_nombre, datos_dificultad.nombre);

	nueva_dificultad->id = id;
	nueva_dificultad->nombre = copia_nombre;
	nueva_dificultad->calcular_puntaje = datos_dificultad.calcular_puntaje;
	nueva_dificultad->verificar_nivel = datos_dificultad.verificar_nivel;
	nueva_dificultad->verificacion_a_string = datos_dificultad.verificacion_a_string;

	return nueva_dificultad;
}

int verificar_nivel(unsigned nivel_adivinado, unsigned nivel_pokemon) {
	return (int)nivel_pokemon - (int)nivel_adivinado;
}

unsigned calcular_puntaje_facil(unsigned cantidad_intentos) {
	int puntaje = (int)PUNTAJE_INICIAL - ((int)cantidad_intentos * PENALIZACION_FALLO_FACIL);
	return puntaje > PUNTAJE_MINIMO ? (unsigned)puntaje : PUNTAJE_MINIMO;
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

	if (resultado_verificacion > -50 && resultado_verificacion <= -25)
		return "Te pasaste por entre 25 y 50 niveles";

	if (resultado_verificacion > -25 && resultado_verificacion <= -10)
		return "Te pasaste por entre 10 y 25 niveles";

	if (resultado_verificacion > -10 && resultado_verificacion <= -5)
		return "Te pasaste por entre 5 y 10 niveles";

	if (resultado_verificacion < 0)
		return "Te pasaste por mas de 50 niveles";

	return "Adivinaste Crack";
}

unsigned calcular_puntaje_media(unsigned cantidad_intentos) {
	int puntaje = (int)PUNTAJE_INICIAL - ((int)cantidad_intentos * PENALIZACION_FALLO_MEDIA);
	return puntaje > PUNTAJE_MINIMO ? (unsigned)puntaje : PUNTAJE_MINIMO;
}

const char* verificacion_a_string_media(int resultado_verificacion) {
	if (resultado_verificacion >= 50)
		return "Te quedaste corto por bastante";

	if (resultado_verificacion > 0)
		return "Te quedaste corto por poco";

	if (resultado_verificacion <= -50)
		return "Te pasaste por bastante";

	if (resultado_verificacion < 0)
		return "Te pasaste por poco";

	return "Adivinaste Crack";
}

unsigned calcular_puntaje_dificil(unsigned cantidad_intentos) {
	int puntaje = (int)PUNTAJE_INICIAL - ((int)cantidad_intentos * PENALIZACION_FALLO_DIFICIL);
	return puntaje > PUNTAJE_MINIMO ? (unsigned)puntaje : PUNTAJE_MINIMO;
}

const char* verificacion_a_string_dificil(int resultado_verificacion) {
	int diferencia_intento = abs(resultado_verificacion);

	if (diferencia_intento > 50)
		return "Frio";

	if (diferencia_intento > 25)
		return "Tibio";

	if (diferencia_intento > 0)
		return "Caliente";

	return "Adivinaste Crack";
}

DatosDificultad datos_dificultad_facil() {
	return (DatosDificultad){
		.nombre = "Facil",
		.calcular_puntaje = calcular_puntaje_facil,
		.verificar_nivel = verificar_nivel,
		.verificacion_a_string = verificacion_a_string_facil,
	};
}

DatosDificultad datos_dificultad_media() {
	return (DatosDificultad){
		.nombre = "Media",
		.calcular_puntaje = calcular_puntaje_media,
		.verificar_nivel = verificar_nivel,
		.verificacion_a_string = verificacion_a_string_media,
	};
}

DatosDificultad datos_dificultad_dificil() {
	return (DatosDificultad){
		.nombre = "Dificil",
		.calcular_puntaje = calcular_puntaje_dificil,
		.verificar_nivel = verificar_nivel,
		.verificacion_a_string = verificacion_a_string_dificil,
	};
}

abb_t* inicializar_dificultades(DatosDificultadConId* dificultad_por_defecto) {
	if (!dificultad_por_defecto)
		return NULL;

	abb_t* dificultades = abb_crear(comparador_dificultades);
	if (!dificultades)
		return NULL;

	DatosDificultadConId* dificultad_facil =
		crear_dificultad(dificultades, 0, datos_dificultad_facil());

	abb_insertar(dificultades, dificultad_facil);

	DatosDificultadConId* dificultad_media =
		crear_dificultad(dificultades, 1, datos_dificultad_media());

	abb_insertar(dificultades, dificultad_media);

	DatosDificultadConId* dificultad_dificil =
		crear_dificultad(dificultades, 2, datos_dificultad_dificil());

	abb_insertar(dificultades, dificultad_dificil);

	*dificultad_por_defecto = *dificultad_facil;

	return dificultades;
}

bool dificultad_esta_en_uso(DatosDificultadConId dificultad_en_uso, DatosDificultadConId dificultad_buscada) {
	return dificultad_en_uso.id == dificultad_buscada.id;
}

void destruir_dificultad(void* _dificultad) {
	if (!_dificultad)
		return;

	DatosDificultadConId* dificultad = _dificultad;
	free((char*)dificultad->nombre);
	free(dificultad);
}
