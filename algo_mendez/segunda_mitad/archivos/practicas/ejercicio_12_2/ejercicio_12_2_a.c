#include <stdlib.h>
#include <stdio.h>

#define MAX_NOMBRE 100

typedef struct firma
{
	char nombre[MAX_NOMBRE];
	int voto;
} firma_t;

void mostrar_firmas(FILE *archivo_firmas)
{
	firma_t firma;
	int leidos = fscanf(archivo_firmas, "%[^;];%i\n", firma.nombre, &(firma.voto));

	while (leidos == 2)
	{
		if (firma.voto == 1)
			printf("%s voto a favor!\n", firma.nombre);
		else if (firma.voto == 0)
			printf("%s voto a en contra!\n", firma.nombre);

		leidos = fscanf(archivo_firmas, "%[^;];%i\n", firma.nombre, &(firma.voto));
	}
}

int main(int argc, char *argv[])
{
	FILE *archivo_firmas = fopen("firmas_para_la_liberacion_del_insta.txt", "r");

	if (archivo_firmas == NULL)
	{
		perror("Error al abrir el archivo firmas_para_la_liberacion_del_insta.txt");
		return -1;
	}

	mostrar_firmas(archivo_firmas);

	fclose(archivo_firmas);

	return 0;
}