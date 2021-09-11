#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const char nombre_arch_info[] = "informacion.txt";

// Archivo binario secuencial
typedef struct alumno {
	char nombre[100];
	char nombre_corrector[100];
	int nota;
} alumno_t;

// Archivo de texto "informacion.txt"
int imprimir_alumnos_por_corrector_nota() {
	FILE *arch_info = fopen(nombre_arch_info, "r");

	if (!arch_info) {
		perror("Error al abrir el archivo");
		return -1;
	}

	char nombre_arch_alumnos[100];
	char nombre_corrector_buscado[100];
	int nota_min_buscada;

	fscanf(arch_info, "%*[^=]=%[^\n]\n", nombre_arch_alumnos);
	fscanf(arch_info, "%*[^=]=%[^\n]\n", nombre_corrector_buscado);
	fscanf(arch_info, "%*[^=]=%i\n", &nota_min_buscada);

	FILE *arch_alumnos = fopen(nombre_arch_alumnos, "r");

	if (!arch_alumnos) {
		perror("Error al abrir el archivo");
		return -1;
	}

	alumno_t alumno_temp;
	fread(&alumno_temp, sizeof(alumno_temp), 1, arch_alumnos);

	int comp;
	while (!feof(arch_alumnos)) {
		comp = strcmp(alumno_temp.nombre_corrector, nombre_corrector_buscado);
		if (comp == 0 && alumno_temp.nota >= nota_min_buscada) {
			printf("Alumno: %s\n", alumno_temp.nombre);
		}
	}

	fclose(arch_info);
	fclose(arch_alumnos);

	return 0;
}
