#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NOTA_MIN_APROBADO 4
#define MAX_MAESTROS 6

// Archivo binario secuencial (alumnos.dat):
typedef struct alumno
{
	char nombre[100];
	int id_maestro;
	int nota;
} alumno_t;

// Archivo binario directo (maestros.dat):
typedef struct maestro
{
	int id;
	char nombre[100];
	bool es_malo;
} maestro_t;

void ordenar_maestros_por_id(maestro_t maestros[], int tope_maestros)
{
	int min;
	maestro_t maestro_temp;

	for (int i = 0; i < (tope_maestros - 1); i++)
	{
		min = i;
		for (int j = 0; j < tope_maestros; j++)
		{
			if (maestros[j].id < maestros[min].id)
			{
				min = j;
			}
		}

		maestro_temp = maestros[i];
		maestros[i] = maestros[min];
		maestros[min] = maestro_temp;
	}
}

int encontrar_maestro(maestro_t maestros[], int low, int high, int id_maestro)
{
	int mid;
	if (low <= high)
	{
		mid = (high + low) / 2;
		if (maestros[mid].id == id_maestro)
		{
			return mid;
		}

		if (maestros[mid].id < id_maestro)
		{
			return encontrar_maestro(maestros, low, (mid - 1), id_maestro);
		}

		if (maestros[mid].id > id_maestro)
		{
			return encontrar_maestro(maestros, (mid + 1), high, id_maestro);
		}
	}
}

void imprimir_alumnos_aprobados()
{
	FILE *arch_alumnos = fopen("alumnos.dat", "r");
	FILE *arch_maestros = fopen("maestros.dat", "r");

	maestro_t maestros[MAX_MAESTROS];
	int tope_maestros = fread(maestros, sizeof(maestro_t), MAX_MAESTROS, arch_maestros);
	ordenar_maestros_por_id(maestros, tope_maestros);

	alumno_t alumno_temp;
	int leidos = fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
	while (!feof(arch_alumnos))
	{
		if (alumno_temp.nota >= NOTA_MIN_APROBADO)
		{
			int pos_maestro = encontrar_maestro(maestros, 0, MAX_MAESTROS, alumno_temp.id_maestro);
			printf("Nombre Alumno: %s - Nombre Maestro: %s", alumno_temp.nombre, maestros[pos_maestro].nombre);
		}
		leidos = fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
	}

	fclose(arch_alumnos);
	fclose(arch_maestros);
}