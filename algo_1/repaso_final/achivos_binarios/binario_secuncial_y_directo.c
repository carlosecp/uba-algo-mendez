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

typedef struct genero
{
	char nombre[100];
	int id;
} genero_t;

int mostrar_genero_de_cancion(char nombre_arch_canciones[], char nombre_colab[])
{
	FILE *arch_canciones = fopen(nombre_arch_canciones, "r");
	FILE *arch_generos = fopen("generos.dat", "r");

	if (!arch_canciones)
	{
		perror("Error al abrir el archivo");
		return -1;
	}

	if (!arch_generos)
	{
		perror("Error al abrir el archivo");
		return -1;
	}

	cancion_t cancion_temp;
	genero_t genero_temp;

	fread(&cancion_temp, sizeof(cancion_t), 1, arch_canciones);

	int comp;
	while (!feof(arch_canciones))
	{
		comp = strcmp(cancion_temp.colaborador, nombre_colab);
		if (comp == 0)
		{
			fseek(arch_generos, sizeof(genero_t) * (cancion_temp.id_genero - 1), SEEK_SET);
			fread(&genero_temp, sizeof(genero_t), 1, arch_generos);
			printf("Cancion: %s - Genero: %s", cancion_temp.nombre, genero_temp.nombre);
		}

		fread(&cancion_temp, sizeof(cancion_t), 1, arch_canciones);
	}

	fclose(arch_canciones);
	fclose(arch_generos);

	return 0;
}