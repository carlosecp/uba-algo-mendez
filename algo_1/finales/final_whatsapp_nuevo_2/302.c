#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct alumno
{
	char nombre[100];
	char nombre_corrector[100];
	int nota;
} alumno_t;

void mostrar_alumnos_por_corrector_nota(char nombre_arch_info[])
{
	FILE *arch_info = fopen(nombre_arch_info, "r");

	char nombre_arch_alumnos[100];
	char nombre_corrector_buscado[100];
	int nota_min_buscada;

	fscanf(arch_info, "%[^=]=%[^\n]\n", NULL, nombre_arch_alumnos);
	fscanf(arch_info, "%[^=]=%[^\n]\n", NULL, nombre_corrector_buscado);
	fscanf(arch_info, "%[^=]=%i", NULL, nota_min_buscada);

	FILE *arch_alumnos = fopen(nombre_arch_alumnos, "r");

	alumno_t alumno_temp;
	fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);

	int comp;
	while (!feof(arch_alumnos))
	{
		comp = strcmp(alumno_temp.nombre_corrector, nombre_corrector_buscado);
		if (comp == 0 && alumno_temp.nota >= nota_min_buscada)
		{
			printf("Alumno...");
		}

		fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
	}

	fclose(arch_info);
	fclose(arch_alumnos);
}