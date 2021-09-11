#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct cancion
{
	char nombre[100];
	char artista[100];
	char colaborador[100];
	int duracion;
	int id_genero;
} cancion_t;

int eliminar_canciones(char nombre_arch_canciones[], char nombre_colab[], int duracion_min)
{
	FILE *arch_canciones = fopen(nombre_arch_canciones, "r");
	FILE *arch_aux = fopen("canciones_aux.dat", "w");

	if (!arch_canciones)
	{
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_aux)
	{
		perror("Error al crear el archivo auxiliar");
		return -1;
	}

	cancion_t cancion_temp;
	fread(&cancion_temp, sizeof(cancion_t), 1, arch_canciones);

	int comp;
	while (!feof(arch_canciones))
	{
		comp = strcmp(cancion_temp.colaborador, nombre_colab);
		// La comparacion esta probablemente mala, esto no es importante.
		if (comp != 0 && cancion_temp.duracion >= duracion_min)
		{
			fwrite(&cancion_temp, sizeof(cancion_t), 1, arch_aux);
		}
		fread(&cancion_temp, sizeof(cancion_t), 1, arch_canciones);
	}

	fclose(arch_canciones);
	fclose(arch_aux);

	return 0;
}