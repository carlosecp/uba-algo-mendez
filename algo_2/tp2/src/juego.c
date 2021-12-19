#include "juego.h"

#include <stdio.h>
#include "simulador.h"

#define PUNTAJE_INICIAL 100

unsigned calcular_puntaje_ultra_nightmare(unsigned cantidad_intentos) {
	return PUNTAJE_INICIAL / cantidad_intentos + 1;
}

int verificar_nivel_ultra_nightmare(unsigned nivel_adivinado, unsigned nivel_pokemon) {
	return (int)nivel_pokemon - (int)nivel_adivinado;
}

const char* verificacion_a_string_ultra_nightmare(int resultado_verificacion) {
	if (resultado_verificacion == 0)
		return "Adivinaste Crack";

	return "No Adivinaste Crack";
}

void juego_inicializar(Juego* juego, hospital_t* hospital) {
	if (!juego || !hospital)
		return;

	// TODO: Verificar la creacion del simulador
    juego->simulador = simulador_crear(hospital);
    juego->jugando = true;

	DatosDificultad dificultad_ultra_nightmare = {
		.nombre = "Ultra Nightmare",
		.calcular_puntaje = calcular_puntaje_ultra_nightmare,
		.verificar_nivel = verificar_nivel_ultra_nightmare,
		.verificacion_a_string = verificacion_a_string_ultra_nightmare 
	};

	simulador_simular_evento(juego->simulador, AgregarDificultad, &dificultad_ultra_nightmare);
}

void juego_titulo(const char* titulo) {
	printf("\x1b[38;5;0m\x1b[48;5;42m\x1b[1m %s \x1b[0m\n", titulo);
}

void juego_prompt_exito(const char* prompt, const char* mensaje) {
	printf("\x1b[38;5;42m\x1b[1m%s\x1b[0m: %s\n", prompt, mensaje);
}

void juego_prompt_error(const char* prompt, const char* mensaje) {
	printf("\x1b[38;5;160m\x1b[1m%s\x1b[0m: %s\n", prompt, mensaje);
}

void juego_terminar(Juego* juego) {
	if (!juego)
		return;

	juego->jugando = false;
}

void juego_destruir(Juego juego) {
	simulador_destruir(juego.simulador);
}
