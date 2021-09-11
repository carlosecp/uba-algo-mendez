#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct alma {
	char nombre[100];
	int vejez;
	bool fue_recolectada;
	bool fue_buena_persona;
} alma_t;

void actualizar_almas(char nombre_arch_actual[], char nombre_arch_actualizaciones[], char nombre_arch_final[]) {
	FILE *arch_actual = fopen(nombre_arch_actual, "r");
	FILE *arch_actualizaciones = fopen(nombre_arch_actualizaciones, "r");
	FILE *arch_final = fopen(nombre_arch_final, "w");

	alma_t alma_actual;
	alma_t alma_actualizada;

	fread(&alma_actual, sizeof(alma_t), 1, arch_actual);
	fread(&alma_actualizada, sizeof(alma_t), 1, arch_actualizaciones);

	while(!feof(arch_actual) && !feof(arch_actualizaciones)) {
		int comparacion = strcmp(alma_actual.nombre, alma_actualizada.nombre);

		if (comparacion == 0) {
			fwrite(&alma_actualizada, sizeof(alma_t), 1, arch_final);
			fread(&alma_actual, sizeof(alma_t), 1, arch_actual);
			fread(&alma_actualizada, sizeof(alma_t), 1, arch_actualizaciones);
		} else if (comparacion < 0) {
			fwrite(&alma_actual, sizeof(alma_t), 1, arch_final);
			fread(&alma_actual, sizeof(alma_t), 1, arch_actual);
		} else {
			fread(&alma_actualizada, sizeof(alma_t), 1, arch_actualizaciones);
		}
	}

	while(!feof(arch_actual)) {
		fread(&alma_actual, sizeof(alma_t), 1, arch_actual);
		fwrite(&alma_actual, sizeof(alma_t), 1, arch_final);
	}

	fclose(arch_actual);
	fclose(arch_actualizaciones);
	fclose(arch_final);
}
