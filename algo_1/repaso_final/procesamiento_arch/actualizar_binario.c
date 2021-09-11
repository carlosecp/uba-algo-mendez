#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct colab {
	char nombre[100];
	int goles_metidos;
	int goles_errados;
	int faltas_cometidas;
	int cantidad_lesiones;
} colab_t;

// Considerando que si podemos tener colaboradores nuevos.
int actualizar_colab_con_nuevos(char nombre_arch_colabs[], char nombre_arch_actualizaciones[]) {
	FILE *arch_colabs = fopen(nombre_arch_colabs, "r");
	FILE *arch_actualizaciones = fopen(nombre_arch_actualizaciones, "w");
	FILE *arch_aux = fopen("archivo_aux.dat", "w");

	if (!arch_colabs) {
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_actualizaciones) {
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_aux) {
		perror("Error al crear el archivo");
		return -1;
	}

	colab_t colab_temp;
	colab_t colab_actualizacion_temp;

	fread(&colab_temp, sizeof(colab_t), 1, arch_colabs);
	fread(&colab_actualizacion_temp, sizeof(colab_t), 1, arch_actualizaciones);

	int comp;
	while (!feof(arch_colabs) && !feof(arch_actualizaciones)) {
		comp = strcmp(colab_temp.nombre, colab_actualizacion_temp.nombre);
		if (comp == 0) {
			// Recordemos que es una acutalizacion de suma, no de reemplazo
			colab_temp.goles_metidos += colab_actualizacion_temp.goles_metidos;
			colab_temp.goles_errados += colab_actualizacion_temp.goles_errados;
			colab_temp.faltas_cometidas += colab_actualizacion_temp.faltas_cometidas;
			colab_temp.cantidad_lesiones += colab_actualizacion_temp.cantidad_lesiones;
			fwrite(&colab_temp, sizeof(colab_t), 1, arch_aux);

			fread(&colab_temp, sizeof(colab_t), 1, arch_colabs);
			fread(&colab_actualizacion_temp, sizeof(colab_t), 1, arch_actualizaciones);
		} else if (comp < 0) {
			fwrite(&colab_temp, sizeof(colab_t), 1, arch_aux);
			fread(&colab_temp, sizeof(colab_t), 1, arch_colabs);
		} else {
			fwrite(&colab_actualizacion_temp, sizeof(colab_t), 1, arch_aux);
			fread(&colab_actualizacion_temp, sizeof(colab_t), 1, arch_actualizaciones);
		}
	}

	while (!feof(arch_colabs)) {
		fwrite(&colab_temp, sizeof(colab_t), 1, arch_aux);
		fread(&colab_temp, sizeof(colab_t), 1, arch_colabs);
	}

	fclose(arch_colabs);
	fclose(arch_actualizaciones);
	fclose(arch_aux);

	return 0;
}

// Considerando que no podemos tener colaboradores nuevos (usando fseek)
int actualizar_colab_sin_nuevos(char nombre_arch_colabs[], char nombre_arch_actualizaciones[]) {
	FILE *arch_colabs = fopen(nombre_arch_colabs, "r+");
	FILE *arch_actualizaciones = fopen(nombre_arch_actualizaciones, "w");

	if (!arch_colabs) {
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_actualizaciones) {
		perror("Error al abrir el archivo");
		return -1;
	}

	colab_t colab_temp;
	colab_t colab_actualizacion_temp;

	fread(&colab_temp, sizeof(colab_t), 1, arch_colabs);
	fread(&colab_actualizacion_temp, sizeof(colab_t), 1, arch_actualizaciones);

	int comp;
	while (!feof(arch_colabs) && !feof(arch_actualizaciones)) {
		comp = strcmp(colab_temp.nombre, colab_actualizacion_temp.nombre);
		if (comp == 0) {
			colab_temp.goles_metidos += colab_actualizacion_temp.goles_metidos;
			colab_temp.goles_errados += colab_actualizacion_temp.goles_errados;
			colab_temp.faltas_cometidas += colab_actualizacion_temp.faltas_cometidas;
			colab_temp.cantidad_lesiones += colab_actualizacion_temp.cantidad_lesiones;

			fseek(arch_colabs, -1 * sizeof(colab_t), SEEK_CUR);
			fwrite(&colab_temp, sizeof(colab_t), 1, arch_colabs);
		}
		fread(&colab_temp, sizeof(colab_t), 1, arch_colabs);
	}

	fclose(arch_colabs);
	fclose(arch_actualizaciones);
	
	return 0;
}
