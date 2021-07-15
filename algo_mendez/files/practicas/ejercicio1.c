#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CANCION 100
#define MAX_ARTISTA 100
#define MAX_COLAB 100
#define MAX_GENERO 100

typedef struct cancion {
	char nombre[MAX_CANCION];
	char artista[MAX_ARTISTA];
	char colaborador[MAX_COLAB];
	int duracion;
	int id_genero;
} cancion_t;

typedef struct genero {
	char nombre[MAX_GENERO];
	int id;
} genero_t;

#define COLAB "Sol"

void imprimir_canciones(FILE* canciones) {
	cancion_t cancion;

	/* int leidos = fread(&cancion, sizeof(cancion_t), 1, canciones);
	while (leidos == 1) {
		if (strcmp(cancion.colaborador, COLAB) == 0) {
			printf("- %s : %s\n", cancion.artista, cancion.colaborador);
		}

		leidos = fread(&cancion, sizeof(cancion_t), 1, canciones);
	} */

	int leidos = fread(&cancion, sizeof(cancion_t), 1, canciones);
	while (leidos != EOF) {
		if (strcmp(cancion.colaborador, COLAB) == 0) {
			printf("- %s : %s\n", cancion.artista, cancion.colaborador);
		}

		leidos = fread(&cancion, sizeof(cancion_t), 1, canciones);
	}
}

int main() {
	FILE* canciones = fopen("canciones.dat", "rb");

	if (canciones == NULL) {
		perror("No se pudo abrir archivo");
		return -1;
	}

	imprimir_canciones(canciones);

	fclose(canciones);
	return 0;
}
