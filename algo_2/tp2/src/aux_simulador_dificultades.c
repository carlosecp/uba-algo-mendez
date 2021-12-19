#include "aux_simulador_dificultades.h"

#include <stdio.h>
#include <string.h>

const unsigned PUNTAJE_INICIAL = 100;
const unsigned PUNTAJE_MINIMO = 0;

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

/* Dificultad Facil */

int verificar_nivel_facil(unsigned nivel_adivinado, unsigned nivel_pokemon) {
	return (int)(nivel_pokemon - nivel_adivinado);
}

unsigned calcular_puntaje_facil(unsigned cantidad_intentos) {
	int puntaje = (int)PUNTAJE_INICIAL - (int)cantidad_intentos;
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

	if (resultado_verificacion < 0)
		return "Te pasaste por entre 1 y 5 niveles";

	return "Adivinaste Crack";
}

abb_t* crear_dificultades_iniciales(DatosDificultadConId* dificultad_por_defecto) {
	if (!dificultad_por_defecto)
		return NULL;

	abb_t* dificultades = abb_crear(comparador_dificultades);
	if (!dificultades)
		return NULL;

	DatosDificultadConId* dificultad_facil = crear_nueva_dificultad(0, "Facil", calcular_puntaje_facil, verificar_nivel_facil, verificacion_a_string_facil);
	DatosDificultadConId* dificultad_media = crear_nueva_dificultad(1, "Media", calcular_puntaje_facil, verificar_nivel_facil, verificacion_a_string_facil);
	DatosDificultadConId* dificultad_dificil = crear_nueva_dificultad(2, "Dificil", calcular_puntaje_facil, verificar_nivel_facil, verificacion_a_string_facil);

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
