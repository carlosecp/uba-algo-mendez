#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/hospital.h"
#include "src/simulador.h"
#include "src/juego.h"

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

void mostrar_estadisticas(Juego* juego) {
    EstadisticasSimulacion e;
    simulador_simular_evento(juego->simulador, ObtenerEstadisticas, &e);

    // Mostrar estadísticas
	printf("\033[1m\033[4mEstadisticas:\033[0m\n");
	printf("Entrenadores Atendidos: %u\n", e.entrenadores_atendidos);
	printf("Entrenadores Totales: %u\n", e.entrenadores_totales);
	printf("Pokemon Atendidos: %u\n", e.pokemon_atendidos);
	printf("Pokemon En Espera: %u\n", e.pokemon_en_espera);
	printf("Pokemon Totales: %u\n", e.pokemon_totales);
	printf("Puntos: %u\n", e.puntos);
	printf("Cantidad Eventos Simulados: %u\n", e.cantidad_eventos_simulados);
}

void ejecutar_comando(Juego* juego, char comando) {
	switch (comando) {
		case 'e':
			mostrar_estadisticas(juego);
			break;
		case 'p':
			simulador_simular_evento(juego->simulador, AtenderProximoEntrenador, NULL);
			break;
		case 'i':
		case 'a':
		case 'n':
		case 'd':
		case 'o':
		case 'q':
			terminar_juego(juego);
			break;
		default:
			break;
	}
}

int main(int argc, char* argv[]) {
	hospital_t* hospital = hospital_crear();
	hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital");

	Juego juego;
	inicializar_juego(&juego, hospital);

	do {
		printf("> ");
		char c = leer_comando();
		ejecutar_comando(&juego, c);
	} while (juego.jugando);

	destruir_juego(juego);

	return 0;
}
