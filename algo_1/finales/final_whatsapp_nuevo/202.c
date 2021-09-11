#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct alma
{
	char nombre[100];
	int vejez;
	bool fue_recolectada;
	bool fue_buena_persona;
} alma_t;

void organizar_almas(char nombre_arch_almas[], char nombre_arch_actualizaciones[])
{
	FILE *arch_almas = fopen(nombre_arch_almas, "r");
	FILE *arch_actualizaciones = fopen(nombre_arch_actualizaciones, "r");

	alma_t alma;
	alma_t alma_actualizacion;

	fread(&alma, sizeof(alma_t), 1, arch_almas);
	fread(&alma_actualizacion, sizeof(alma_t), 1, arch_actualizaciones);

	int comp;
	while (!feof(arch_almas) && !feof(arch_actualizaciones))
	{
		comp = strcmp(alma.nombre, alma_actualizacion.nombre);
		if (comp == 0)
		{
			fwrite(&alma, sizeof(alma_t), 1, arch_almas);
			fread(&alma, sizeof(alma_t), 1, arch_almas);
			fread(&alma_actualizacion, sizeof(alma_t), 1, arch_actualizaciones);
		}
		else if (comp < 0)
		{
			fwrite(&alma, sizeof(alma_t), 1, arch_almas);
			fread(&alma, sizeof(alma_t), 1, arch_almas);
		}
		else
		{
			fread(&alma_actualizacion, sizeof(alma_t), 1, arch_actualizaciones);
		}
	}

	while (!feof(arch_almas))
	{
		fwrite(&alma, sizeof(alma_t), 1, arch_almas);
		fread(&alma, sizeof(alma_t), 1, arch_almas);
	}

	fclose(arch_almas);
	fclose(arch_actualizaciones)
}