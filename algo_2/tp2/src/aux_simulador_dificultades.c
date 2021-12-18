#include "aux_simulador_dificultades.h"

#include <stdio.h>
#include <string.h>
#include "simulador.h"

int comparador_dificultades(void* _dificultad_1, void* _dificultad_2) {
	DatosDificultadConId* dificultad_1 = _dificultad_1;
	DatosDificultadConId* dificultad_2 = _dificultad_2;

	if (dificultad_1->id > dificultad_2->id)
		return 1;

	if (dificultad_1->id < dificultad_2->id)
		return -1;

	return 0;
}

DatosDificultadConId* crear_dificultad(int id, const char* nombre, unsigned (*calcular_puntaje)(unsigned cantidad_intentos), int (*verificar_nivel)(unsigned nivel_adivinado, unsigned nivel_pokemon), const char* (*verificacion_a_string)(int resultado_verificacion)) {
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
	dificultad->datos = (DatosDificultad){
		.nombre = copia_nombre,
		.calcular_puntaje = calcular_puntaje,
		.verificar_nivel = verificar_nivel,
		.verificacion_a_string = verificacion_a_string,
	};

	return dificultad;
}

/* Dificultad Facil */

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

unsigned calculo_puntaje_facil(unsigned cantidad_intentos) {
	return 0;
}

DatosDificultadConId* crear_dificultad_facil(int cantidad_dificultades_existentes) {
	DatosDificultadConId* dificultad_facil = malloc(sizeof(DatosDificultadConId));
	if (!dificultad_facil)
		return NULL;

	dificultad_facil->id = cantidad_dificultades_existentes;
	dificultad_facil->datos = (DatosDificultad){
		.nombre = "Facil",
		.calcular_puntaje = calculo_puntaje_facil,
		.verificar_nivel = verificar_nivel_facil,
		.verificacion_a_string = verificacion_a_string_facil,
	};

	return dificultad_facil;
}

/* Dificultad Media */


abb_t* crear_dificultades_iniciales() {
	abb_t* dificultades_iniciales = abb_crear(comparador_dificultades);
	if (!dificultades_iniciales)
		return NULL;

	DatosDificultadConId* dificultad_facil = crear_dificultad(0, "Facil", calcular_puntaje_facil, verificar_nivel_facil, verificacion_a_string_facil);

	// TODO: faltan validaciones
	dificultades_iniciales = abb_insertar(dificultades_iniciales, dificultad_facil);

	return dificultades_iniciales;
}

bool dificultad_esta_en_uso(DatosDificultadConId dificultad_en_uso, DatosDificultadConId dificultad_buscada) {
	return dificultad_en_uso.id == dificultad_buscada.id;
}

// TODO: validaciones de frees como estos (destructores)
void destruir_dificultad(void* _dificultad) {
	DatosDificultadConId* dificultad = _dificultad;
	free((char*)dificultad->datos.nombre);
	free(dificultad);
}
