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

void mostrar_estadisticas(simulador_t* simulador) {
	EstadisticasSimulacion e;
	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerEstadisticas, &e);

	if (res == ErrorSimulacion)
		return;

	juego_titulo("ESTADISTICAS");
	printf("• Entrenadores Atendidos: %u\n", e.entrenadores_atendidos);
	printf("• Entrenadores Totales: %u\n", e.entrenadores_totales);
	printf("• Pokemon Atendidos: %u\n", e.pokemon_atendidos);
	printf("• Pokemon En Espera: %u\n", e.pokemon_en_espera);
	printf("• Pokemon Totales: %u\n", e.pokemon_totales);
	printf("• Puntos: %u\n", e.puntos);
	printf("• Cantidad Eventos Simulados: %u\n", e.cantidad_eventos_simulados);
}

void atender_proximo_entreandor(simulador_t* simulador) {
	ResultadoSimulacion res = simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);

	if (res == ErrorSimulacion)
		return;
}

void mostrar_pokemon_en_tratamiento(simulador_t* simulador) {
	InformacionPokemon i = {NULL};
	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerInformacionPokemonEnTratamiento, &i);

	if (res == ErrorSimulacion)
		return;

	juego_titulo("POKEMON EN TRATAMIENTO");
	printf("• Pokemon: %s\n", i.nombre_pokemon);
	printf("• Entrenador: %s\n", i.nombre_entrenador);
}

void adivinar_nivel_pokemon_en_tratamiento(simulador_t* simulador) {
	if (!simulador)
		return;

	Intento intento = {
		.nivel_adivinado = 0,
		.es_correcto = false,
		.resultado_string = "",
	};

	printf("Nivel Pokemon: ");
	scanf(" %i", &(intento.nivel_adivinado));

	ResultadoSimulacion res = simulador_simular_evento(simulador, AdivinarNivelPokemon, &intento);

	if (res == ErrorSimulacion)
		return;

	if (intento.es_correcto) {
		juego_prompt_exito("CORRECTO", intento.resultado_string);
	} else {
		juego_prompt_error("INCORRECTO", intento.resultado_string);
	}
}

void mostrar_informacion_dificultad(simulador_t* simulador) {
	InformacionDificultad dificultad_buscada = {
		.nombre_dificultad = NULL,
		.en_uso = false,
		.id = -1,
	};

	printf("ID Dificultad: ");
	scanf(" %i", &(dificultad_buscada.id));

	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerInformacionDificultad, &dificultad_buscada);

	if (res == ErrorSimulacion)
		return;

	if (!dificultad_buscada.nombre_dificultad) {
		return;
	}

	// Make this prettier
	printf("Dificultad Encontrada: {%s %i}\n", dificultad_buscada.nombre_dificultad, dificultad_buscada.id);
	printf("Dificultad Esta En Uso: %s\n", dificultad_buscada.en_uso ? "Si" : "No");
}

void ejecutar_comando(Juego* juego, char comando) {
	simulador_t* simulador = juego->simulador;

	switch (comando) {
		case 'e':
			mostrar_estadisticas(simulador);
			break;
		case 'p':
			atender_proximo_entreandor(simulador);
			break;
		case 'i':
			mostrar_pokemon_en_tratamiento(simulador);
			break;
		case 'a':
			adivinar_nivel_pokemon_en_tratamiento(simulador);
			break;
		case 'd':
		case 'o':
			mostrar_informacion_dificultad(simulador);
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
		ejecutar_comando(&juego, c);
	} while (juego.jugando);

	juego_destruir(juego);

	return 0;
}
