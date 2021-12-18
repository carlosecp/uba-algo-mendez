#include "aux_simulador_dificultades.h"

#include <stdio.h>
#include <string.h>

#include "abb.h"
#include "lista.h"
#include "simulador.h"

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

bool dificultad_esta_en_uso(DatosDificultadConId dificultad_en_uso, DatosDificultadConId dificultad_buscada) {
	return dificultad_en_uso.id == dificultad_buscada.id;
}

void destruir_dificultad(void* _dificultad) {
    DatosDificultadConId* dificultad = _dificultad;
    free(dificultad);
}
