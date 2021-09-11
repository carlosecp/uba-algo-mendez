#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_MAESTROS 20

const char nombre_arch_alumnos[] = "alumnos.dat";
const char nombre_arch_maestros[] = "maestros.dat";
const int nota_minima = 6;

// Archivo binario secuencial "alumnos.dat"
typedef struct alumno {
	char nombre[100];
	int id_maestro;
	int nota;
} alumno_t;

// Archivo binario directo "maestros.dat"
// El archivo no esta ordenado
typedef struct maestro {
	int id;
	char nombre[100];
	bool es_malo;
} maestro_t;

int buscar_maestro_por_id(maestro_t maestros[MAX_MAESTROS], int tope_maestros, int id_maestro) {
	bool encontrado = false;
	int i = 0, pos = -1;

	while (!encontrado && i < tope_maestros) {
		if (maestros[i].id == id_maestro) {
			encontrado = true;
			pos = i;
		}
		i++;
	}

	return pos;
}

int imprimir_alumnos_maestros() {
	FILE *arch_alumnos = fopen(nombre_arch_alumnos, "r");
	FILE *arch_maestros = fopen(nombre_arch_maestros, "r");

	if (!arch_alumnos) {
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_maestros) {
		perror("Error al abrir el archivo");
		return -1;
	}

	alumno_t alumno_temp;
	fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);

	maestro_t maestros[MAX_MAESTROS];
	size_t tope_maestros = fread(maestros, sizeof(maestro_t), MAX_MAESTROS, arch_maestros);

	int pos_maestro;
	while (!feof(arch_alumnos)) {
		if (alumno_temp.nota >= nota_minima) {
			pos_maestro = buscar_maestro_por_id(maestros, tope_maestros, alumno_temp.id_maestro);
			if (pos_maestro != -1) {
				printf("Alumno: %s - Nota: %i - Maestro: %s", alumno_temp.nombre
						,alumno_temp.nota, maestros[pos_maestro].nombre);
			}
		}
		fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
	}

	return 0;
}
