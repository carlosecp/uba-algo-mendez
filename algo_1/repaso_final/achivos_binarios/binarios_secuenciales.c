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

int imprimir_canciones_colab(char nombre_arch_canciones[], char nombre_colab[])
{
	FILE *arch_canciones = fopen(nombre_arch_canciones, "r");

	if (!arch_canciones)
	{
		perror("Error al abrir el archivo");
		return -1;
	}

	cancion_t cancion_temp;
	fread(&cancion_temp, sizeof(cancion_t), 1, arch_canciones);
	while (!feof(arch_canciones))
	{
		if (strcmp(cancion_temp.colaborador, nombre_colab) == 0)
		{
			printf("%s - %s\n", cancion_temp.nombre, cancion_temp.colaborador);
		}
		fread(&cancion_temp, sizeof(cancion_t), 1, arch_canciones);
	}

	fclose(arch_canciones);

	return 0;
}