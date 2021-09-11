#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct alma
{
	char nombre[100];
	int vejz;
	bool fue_recolectada;
	bool fue_buena_persona;
};

typedef struct alma alma_t;

void actualizar_almas(char nombre_arch_almas[], char nombre_arch_actualizaciones[])
{
	FILE *arch_almas = fopen(nombre_arch_almas, "r");
	FILE *arch_actualizaciones = fopen(nombre_arch_actualizaciones, "r");
	FILE *arch_final = fopen("arch_almas_temp.dat", "w");

	alma_t alma;
	alma_t alma_actualizacion;

	fread(&alma, sizeof(alma_t), 1, arch_almas);
	fread(&alma_actualizacion, sizeof(alma_t), 1, alma_actualizaciones);

	int comp;
	while (!feof(arch_almas) && !feof(arch_actualizaciones))
	{
		comp = strcmp(alma.nombre, alma_actualizacion.nombre);
		if (comp == 0)
		{
			fwrite(&alma_actualizacion, sizeof(alma_t), 1, arch_final);
			fread(&alma, sizeof(alma_t), 1, arch_almas);
			fread(&alma_actualizacion, sizeof(alma_t), 1, alma_actualizaciones);
		}
		else if (comp < 0)
		{
			fwrite(&alma, sizeof(alma_t), 1, arch_final);
			fread(&alma, sizeof(alma_t), 1, arch_almas);
		}
	}

	while (!feof(arch_almas))
	{
		fwrite(&alma, sizeof(alma_t), 1, arch_final);
		fread(&alma, sizeof(alma_t), 1, arch_almas);
	}

	fclose(arch_almas);
	fclose(arch_actualizaciones);
	fclose(arch_final);
}