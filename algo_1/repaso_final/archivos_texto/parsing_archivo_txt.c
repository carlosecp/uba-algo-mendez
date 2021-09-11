#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Ejercicio #1
// Leer el archivo y analizar el contentido
typedef struct colab
{
	char nombre[100];
	int voto;
} colab_t;

int imprimi_votos()
{
	FILE *arch_votos = fopen("archivo.txt", "r");

	if (!arch_votos)
	{
		perror("Error al abrir archivo");
		return -1;
	}

	colab_t colab;
	int leidos = fscanf(arch_votos, "%[^;];%i\n", colab.nombre, &colab.voto);
	while (leidos == 2)
	{
		printf("%s - %s", colab.nombre, colab.voto == 1 ? "Voto a favor" : "Voto en contra");
		leidos = fscanf(arch_votos, "%[^;];%i\n", &colab.nombre, &colab.voto);
	}

	fclose(arch_votos);

	return 0;
}

// Ejercicio #2
// Leer el archivo y modificarlo (no solo imprimirlo)
int filtrar_charly()
{
	FILE *arch_votos = fopen("archivo.txt", "r");
	FILE *arch_aux = fopen("archivo_aux.txt", "w");

	if (!arch_votos)
	{
		perror("Error al abrir archivo");
		return -1;
	}

	if (!arch_aux)
	{
		perror("Error al abrir el archivo");
		return -1;
	}

	colab_t colab;
	bool charly_ya_voto = false;

	int leidos = fscanf("%[^;];%i\n", colab.nombre, &(colab.voto));
	while (leidos == 2)
	{
		if (strcmp(colab.nombre, "Charly") != 0 || !charly_ya_voto)
		{
			fprintf(arch_aux, "%s;%i\n", colab.nombre, colab.voto);
			if (strcmp(colab.nombre, "Charly") == 0)
			{
				charly_ya_voto = true;
			}
		}
		leidos = fscanf("%[^;];%i\n", colab.nombre, &(colab.voto));
	}

	fclose(arch_votos);
	fclose(arch_aux);

	return 0;
}