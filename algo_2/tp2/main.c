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

	if (res == ErrorSimulacion) {
		juego_log_error("ObtenerEstadisticas");
		return;
	}

	// Mostrar estadísticas
	printf("\x1b[38;5;11m\x1b[1mEstadisticas:\x1b[0m\n");
	printf("Entrenadores Atendidos: %u\n", e.entrenadores_atendidos);
	printf("Entrenadores Totales: %u\n", e.entrenadores_totales);
	printf("Pokemon Atendidos: %u\n", e.pokemon_atendidos);
	printf("Pokemon En Espera: %u\n", e.pokemon_en_espera);
	printf("Pokemon Totales: %u\n", e.pokemon_totales);
	printf("Puntos: %u\n", e.puntos);
	printf("Cantidad Eventos Simulados: %u\n", e.cantidad_eventos_simulados);
}

void atender_proximo_entreandor(simulador_t* simulador) {
	simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
}

void mostrar_pokemon_en_tratamiento(simulador_t* simulador) {
	InformacionPokemon i;
	ResultadoSimulacion res = simulador_simular_evento(simulador, ObtenerInformacionPokemonEnTratamiento, &i);

	if (res == ErrorSimulacion) {
		juego_log_error("ObtenerInformacionPokemonEnTratamiento");
		return;
	}

	printf("\x1b[38;5;11m\x1b[1mPokemon En Tratamiento:\x1b[0m\n");
	printf("Pokemon: %s\n", i.nombre_pokemon);
	printf("Entrenador: %s\n", i.nombre_entrenador);
}

void ejecutar_comando(Juego* juego, char comando) {
	switch (comando) {
		case 'e':
			mostrar_estadisticas(juego->simulador);
			break;
		case 'p':
			atender_proximo_entreandor(juego->simulador);
			break;
		case 'i':
			mostrar_pokemon_en_tratamiento(juego->simulador);
			break;
		case 'a':
		case 'n':
		case 'd':
		case 'o':
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
