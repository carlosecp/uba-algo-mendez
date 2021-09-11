#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int imprimir_cancion()
{
	FILE *arch_cancion = fopen("cancion.txt", "r");

	if (!arch_cancion)
	{
		perror("Error");
		return -1;
	}

	char verso[100];
	int leidos = fscanf(arch_cancion, "%[^\n]\n", verso);
	while (leidos == 1)
	{
		printf("%s", verso);
		leidos = fscanf(arch_cancion, "%[^\n]\n", verso);
	}

	fclose(arch_cancion);

	return 0;
}