#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct victoria {
	char nombre_enemigo[100];
	bool es_monstruo;
	int dificultad;
} victoria_t;

typedef victoria_t vic;

void agregar_victorias_faltantes(vic victorias[], int tope_victorias,
								 vic victorias_faltantes[], int tope_victorias_faltantes,
								 vic victorias_totales[], int *tope_victorias_totales) {
	int i = 0, j = 0;

	int comp;
	while (i < tope_victorias && j < tope_victorias_faltantes) {
		comp = strcmp(victorias[i].nombre_enemigo, victorias_faltantes[i].nombre_enemigo);
		if (comp <= 0) {
			victorias_totales[*tope_victorias_totales] = victorias[i];
			(*tope_victorias_totales)++;
			i++;
		} else {
			victorias_totales[*tope_victorias_totales] = victorias[j];
			(*tope_victorias_totales)++;
			j++;
		}
	}

	while (i < tope_victorias) {
		victorias_totales[*tope_victorias_totales] = victorias[i];
		(*tope_victorias_totales)++;
		i++;
	}

	while (j < tope_victorias_faltantes) {
		victorias_totales[*tope_victorias_totales] = victorias[j];
		(*tope_victorias_totales)++;
		j++;
	}
}
