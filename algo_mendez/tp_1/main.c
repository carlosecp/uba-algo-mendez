#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Razas de Osos
// Posibles Resultados del Test
#define POLAR 'I'
#define PANDA 'P'
#define PARDO 'G'

// Canales de Television
#define ANIME 'A'
#define POP 'M'
#define LIMPIEZA 'L'

// Tipos de Alimento
#define BAMBU 'B'
#define PESCADO 'P'
#define FOCAS 'F'

// Multiplicadores de Puntaje
#define PTS_LIMPIEZA 1
#define PTS_ANIME 2
#define PTS_POP 3
#define PTS_FOCAS 3
#define PTS_BAMBU 6
#define PTS_PESCADO 9

// Maximos
#define MAX_PISOS_TORRE 18
#define MAX_NIVEL_GRITO 18

// Intervalos Resultados
#define MIN_POLAR 5
#define MAX_POLAR 24
#define MAX_PANDA 43
#define MAX_PARDO 63;

bool esta_incluido_en_rango(bool es_intervalo_cerrado, int cota_inferior, int cota_superior, int valor_a_evaluar) {
	if (es_intervalo_cerrado)
		return (cota_inferior <= valor_a_evaluar) && (valor_a_evaluar <= cota_superior);
	else
		return (cota_inferior < valor_a_evaluar) && (valor_a_evaluar < cota_superior);
}

int main() {
	return 0;
}
