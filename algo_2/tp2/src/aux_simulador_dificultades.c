#include "aux_simulador_dificultades.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PUNTAJE_INICIAL 100
#define PUNTAJE_MINIMO 0

#define PENALIZACION_FALLO_FACIL 1
#define PENALIZACION_FALLO_MEDIA 5
#define PENALIZACION_FALLO_DIFICIL 10

int comparador_dificultades(void* _dificultad_1, void* _dificultad_2) {
	DatosDificultadConId* dificultad_1 = _dificultad_1;
	DatosDificultadConId* dificultad_2 = _dificultad_2;

	if (dificultad_1->id > dificultad_2->id)
		return 1;

	if (dificultad_1->id < dificultad_2->id)
		return -1;

	return 0;
}

DatosDificultadConId* crear_nueva_dificultad(int id, const char* nombre, unsigned (*calcular_puntaje)(unsigned cantidad_intentos), int (*verificar_nivel)(unsigned nivel_adivinado, unsigned nivel_pokemon), const char* (*verificacion_a_string)(int resultado_verificacion)) {
	if (!nombre || !calcular_puntaje || !verificar_nivel || !verificacion_a_string)
		return NULL;

	DatosDificultadConId* dificultad = malloc(sizeof(DatosDificultadConId));
	if (!dificultad)
		return NULL;

	char* copia_nombre = malloc(strlen(nombre) + 1);
	if (!copia_nombre) {
		free(dificultad);
		return NULL;
	}

	strcpy(copia_nombre, nombre);

	dificultad->id = id;
	dificultad->nombre = copia_nombre;
	dificultad->calcular_puntaje = calcular_puntaje;
	dificultad->verificar_nivel = verificar_nivel;
	dificultad->verificacion_a_string = verificacion_a_string;

	return dificultad;
}

int verificar_nivel(unsigned nivel_adivinado, unsigned nivel_pokemon) {
	return (int)nivel_pokemon - (int)nivel_adivinado;
}

/* Dificultad Facil */

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

/* Dificultad Media */

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

/* Dificultad Dificil */

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

abb_t* crear_dificultades_iniciales(DatosDificultadConId* dificultad_por_defecto) {
	if (!dificultad_por_defecto)
		return NULL;

	abb_t* dificultades = abb_crear(comparador_dificultades);
	if (!dificultades)
		return NULL;

	DatosDificultadConId* dificultad_facil = crear_nueva_dificultad(0, "Facil", calcular_puntaje_facil, verificar_nivel, verificacion_a_string_facil);
	DatosDificultadConId* dificultad_media = crear_nueva_dificultad(1, "Media", calcular_puntaje_media, verificar_nivel, verificacion_a_string_media);
	DatosDificultadConId* dificultad_dificil = crear_nueva_dificultad(2, "Dificil", calcular_puntaje_dificil, verificar_nivel, verificacion_a_string_dificil);

	if (!dificultad_facil || !dificultad_media || !dificultad_dificil) {
		destruir_dificultad(dificultad_facil);
		destruir_dificultad(dificultad_media);
		destruir_dificultad(dificultad_dificil);

		abb_destruir(dificultades);
		return NULL;
	}

	abb_t* dificultades_aux = abb_insertar(dificultades, dificultad_facil);
	dificultades_aux = abb_insertar(dificultades, dificultad_media);
	dificultades_aux = abb_insertar(dificultades, dificultad_dificil);

	if (!dificultades_aux) {
		destruir_dificultad(dificultad_facil);
		destruir_dificultad(dificultad_media);
		destruir_dificultad(dificultad_dificil);

		abb_destruir(dificultades);
		return NULL;
	}

	// *dificultad_por_defecto = *dificultad_facil;
	*dificultad_por_defecto = *dificultad_dificil;

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
