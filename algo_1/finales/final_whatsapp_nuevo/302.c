#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const char nombre_arch_info[] = "informacion.txt";

typedef struct alumno
{
	char nombre[100];
	char nombre_corrector[100];
	int nota;
} alumno_t;

void imprimir_alumnos_segun_corrector_nota()
{
	FILE *arch_info = fopen(nombre_arch_info, "r");

	char nombre_arch_alumnos[100];
	char nombre_corrector[100];
	int nota_min_buscada;

	fscanf(nombre_arch_info, "%[^=]=%[^\n]\n", NULL, nombre_arch_alumnos);
	fscanf(nombre_arch_info, "%[^=]=%[^\n]\n", NULL, nombre_corrector);
	fscanf(nombre_arch_info, "%[^=]=%i\n", NULL, &nota_min_buscada);

	FILE *arch_alumnos = fopen(nombre_arch_alumnos, "r");

	alumno_t alumno_temp;
	int leidos = fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
	while (!feof(arch_alumnos))
	{
		if (strcmp(alumno_temp.nombre_corrector, nombre_corrector) == 0 && alumno_temp.nota >= nota_min_buscada)
		{
			printf("Alumno....");
		}
		leidos = fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
	}

	fclose(arch_info);
	fclose(arch_alumnos);
}