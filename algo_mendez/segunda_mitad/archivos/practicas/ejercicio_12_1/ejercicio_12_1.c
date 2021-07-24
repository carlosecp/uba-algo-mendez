#include <stdlib.h>
#include <stdio.h>

#define MAX_LETRAS 1000

void mostrar_cancion(FILE *archivo_cancion)
{
	char verso_cancion[MAX_LETRAS];
	int leidos = fscanf(archivo_cancion, "%[^\n]\n", verso_cancion);

	while (leidos == 1)
	{
		printf("%s\n", verso_cancion);
		leidos = fscanf(archivo_cancion, "%[^\n]\n", verso_cancion);
	}
}

int main(int argc, char *argv[])
{
	FILE *archivo_cancion = fopen("cancion_especial.txt", "r");

	if (archivo_cancion == NULL)
	{
		perror("Error al abrir el archivo cancion_especial.txt");
		return -1;
	}

	mostrar_cancion(archivo_cancion);
	fclose(archivo_cancion);

	return 0;
}