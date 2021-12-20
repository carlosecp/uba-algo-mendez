#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/hospital.h"
#include "src/juego.h"
#include "src/simulador.h"

char leer_comando() {
	char linea[100];
	char* leido;
	leido = fgets(linea, 100, stdin);
	if (!leido)
		return 0;
	while (*leido == ' ')
		leido++;
	return (char)tolower(*leido);
}

/**
  * Se encarga de llamar al evento "ObtenerEstadisticas" y muestra los
  * resultados obtenidos por pantalla. En caso de error no muestra nada.
  */
void juego_mostrar_estadisticas(simulador_t* simulador) {
	EstadisticasSimulacion e;
	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerEstadisticas, &e);

	if (res == ErrorSimulacion)
		return;

	juego_titulo("Estadisticas");
	printf(" • Entrenadores Atendidos: %u\n", e.entrenadores_atendidos);
	printf(" • Entrenadores Totales: %u\n", e.entrenadores_totales);
	printf(" • Pokemon Atendidos: %u\n", e.pokemon_atendidos);
	printf(" • Pokemon En Espera: %u\n", e.pokemon_en_espera);
	printf(" • Pokemon Totales: %u\n", e.pokemon_totales);
	printf(" • Puntos: %u\n", e.puntos);
	printf(" • Cantidad Eventos Simulados: %u\n", e.cantidad_eventos_simulados);
}

/**
  * Se encarga de llamar al evento "AtenderProximoEntrenador".
  * En caso de exito se retorna al usuario al menu principal y en caso de error
  * se muestra un mensaje indicando que hubo un error.
  */
void juego_atender_proximo_entreandor(simulador_t* simulador) {
	ResultadoSimulacion res = simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
	if (res == ErrorSimulacion) {
		juego_prompt_error("Error", "No se pudo atender al proximo entrenador");
		return;
	}
}

/**
  * Se encarga de llamar al evento "ObtenerInformacionPokemonEnTratamiento".
  * En caso de que haya un pokemon en tratamiento, muestra la informacion de
  * ese pokemon.
  */
void juego_mostrar_pokemon_en_tratamiento(simulador_t* simulador) {
	InformacionPokemon i = {};
	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerInformacionPokemonEnTratamiento, &i);

	if (res == ErrorSimulacion)
		return;

	juego_titulo("Pokemon en Tratamiento");
	printf(" • Pokemon: %s\n", i.nombre_pokemon);
	printf(" • Entrenador: %s\n", i.nombre_entrenador);
}

/**
  * Se encarga de llamar al evento "AdivinarNivelPokemon". Se le pide al
  * usuario que ingrese un numero correspondiente al nivel del pokemon que
  * actualmente esta en tratamiento. En caso que no haber adivinado, se sigue
  * pidiendo el ingreso de un numero hasta dar con el nivel correcto. Cuando
  * se adivina o se erra el nivel del pokemon se muestra la pista
  * correspondiente.
  */
void juego_adivinar_nivel_pokemon_en_tratamiento(simulador_t* simulador) {
	if (!simulador)
		return;

	Intento intento = {
		.nivel_adivinado = 0,
		.es_correcto = false,
		.resultado_string = "",
	};

	while (!intento.es_correcto) {
		printf("Nivel Pokemon: ");
		scanf(" %i", &(intento.nivel_adivinado));

		ResultadoSimulacion res = simulador_simular_evento(simulador, AdivinarNivelPokemon, &intento);
		if (res == ErrorSimulacion)
			return;

		if (!intento.es_correcto)
			juego_prompt_error("Incorrecto", intento.resultado_string);
	}

	juego_prompt_exito("Correcto", intento.resultado_string);
}

/**
  * Se encarga de llamar al evento "SeleccionarDificultad". Le permite al 
  * usuario cambiar la dificultad de las pistas que se dan al intentar
  * adivinar el nivel de un pokemon.
  */
void juego_seleccionar_nueva_dificultad(simulador_t* simulador) {
	if (!simulador)
		return;

	int id_nueva_dificultad;

	printf("Seleccionar ID Dificultad: ");
	scanf(" %i", &id_nueva_dificultad);

	ResultadoSimulacion res = simulador_simular_evento(simulador, SeleccionarDificultad, &id_nueva_dificultad);
	if (res == ErrorSimulacion)
		return;

	InformacionDificultad informacion_nueva_dificultad = {
		.id = id_nueva_dificultad,
	};

	res = simulador_simular_evento(simulador, ObtenerInformacionDificultad, &informacion_nueva_dificultad);
	if (res == ErrorSimulacion)
		return;

	juego_prompt_exito("DIFICULTAD SELECCIONADA", informacion_nueva_dificultad.nombre_dificultad);
}

/**
  * Se encarga de llamar al evento "ObtenerInformacionDificultad" para todas
  * las dificultades disponibles o hasta que el evento retorne error. Muestra
  * en pantalla las dificultades y si cual es la dificultad activa actualmente.
  */
void juego_mostrar_informacion_dificultad(simulador_t* simulador) {
	InformacionDificultad dificultad_buscada = {
		.nombre_dificultad = NULL,
		.en_uso = false,
		.id = 0,
	};

	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerInformacionDificultad, &dificultad_buscada);
	if (res == ErrorSimulacion)
		return;

	juego_titulo("Dificultades");

	while (res == ExitoSimulacion) {
		if (!dificultad_buscada.nombre_dificultad)
			return;

		if (dificultad_buscada.en_uso)
			printf(" • \x1b[38;5;42m\x1b[1m\x1b[4m[%i] %s (en uso)\x1b[0m\n", dificultad_buscada.id, dificultad_buscada.nombre_dificultad);
		else 
			printf(" • [%i] %s\n", dificultad_buscada.id, dificultad_buscada.nombre_dificultad);

		dificultad_buscada.id++;

		res = simulador_simular_evento(simulador, ObtenerInformacionDificultad, &dificultad_buscada);
	}
}

/**
  * Recibe un juego inicializado.
  * Toma un comando y ejecuta el evento correspondiente.
  */
void juego_ejecutar_comando(Juego* juego, char comando) {
	simulador_t* simulador = juego->simulador;

	switch (comando) {
		case 'e':
			juego_mostrar_estadisticas(simulador);
			break;
		case 'p':
			juego_atender_proximo_entreandor(simulador);
			break;
		case 'i':
			juego_mostrar_pokemon_en_tratamiento(simulador);
			break;
		case 'a':
			juego_adivinar_nivel_pokemon_en_tratamiento(simulador);
			break;
		case 'd':
			juego_seleccionar_nueva_dificultad(simulador);
			break;
		case 'o':
			juego_mostrar_informacion_dificultad(simulador);
			break;
		case 'q':
			juego_terminar(juego);
			break;
		default:
			break;
	}
}

int main(int argc, char* argv[]) {
	hospital_t* hospital = hospital_crear();
	hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital");

	Juego juego;
	juego_inicializar(&juego, hospital);

	do {
		printf("> ");
		char c = leer_comando();
		juego_ejecutar_comando(&juego, c);
	} while (juego.jugando);

	juego_destruir(juego);

	return 0;
}
