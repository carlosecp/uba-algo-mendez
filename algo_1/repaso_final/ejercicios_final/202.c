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

// Archivo binario secuencial desactualizado
// Archivo binario secuencial de actualizaciones
int actualizar_almas(char nombre_arch_almas[], char nombre_arch_actualizaciones[]) {
	FILE *arch_almas = fopen(nombre_arch_almas, "r");
	FILE *arch_actualizaciones = fopen(nombre_arch_actualizaciones, "r");

	if (!arch_almas) {
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_actualizaciones) {
		perror("Error al abrir el archivo");
		return -1;
	}

	alma_t alma;
	alma_t alma_actualizada;

	fread(&alma, sizeof(alma_t), 1, arch_almas);
	fread(&alma_actualizada, sizeof(alma_t), 1, arch_actualizaciones);

	int comp;
	while (!feof(arch_almas) && !feof(arch_actualizaciones)) {
		comp = strcmp(alma.nombre, alma_actualizada.nombre);
		if (comp == 0) { // Significa que las almas son las mismas
			fseek(arch_almas, -1 * sizeof(alma_t), SEEK_CUR);
			fwrite(&alma_actualizada, sizeof(alma_t), 1, arch_almas);
			fread(&alma_actualizada, sizeof(alma_t), 1, arch_actualizaciones);
		}
		fread(&alma, sizeof(alma_t), 1, arch_almas);
	}

	while (!feof(arch_almas)) {
		fwrite(&alma, sizeof(alma_t), 1, arch_almas);
		fread(&alma, sizeof(alma_t), 1, arch_almas);
	}

	fclose(arch_almas);
	fclose(arch_actualizaciones);
	
	return 0;
}
