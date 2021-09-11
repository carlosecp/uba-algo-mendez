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

int ordernar_generos(genero_t generos[], int tope)
{
	int min, comp;
	genero_t temp;

	for (int i = 0; i < (tope - 1); i++)
	{
		min = i;
		for (int j = (i + 1); j < tope; j++)
		{
			comp = strcmp(generos[i].nombre, generos[min].nombre);
			if (comp < 0)
			{
				min = j;
			}
		}

		temp = generos[i];
		generos[i] = generos[min];
		generos[min] = temp;
	}
}

// En estos casos lo que conviene hacer es volcar el archivo sobre un vector
int mostrar_genero_de_cancion(char nombre_arch_canciones[], char nombre_colab[])
{
	FILE *arch_generos = fopen("generos.dat", "w");

	if (!arch_generos)
	{
		perror("Error al abrir el archivo");
		return -1;
	}

	const int MAX_GENEROS = 100;
	genero_t generos[MAX_GENEROS];
	size_t tope_generos = fread(generos, sizeof(genero_t), MAX_GENEROS, arch_generos);

	ordernar_generos(generos, tope_generos);

	fclose(arch_generos);

	return 0;
}