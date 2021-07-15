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

#define DURACION 6

int main() {
	FILE* canciones_colab = fopen("canciones.dat", "r");
	FILE* canciones_colab_aux = fopen("canciones_aux.dat", "w");

	if (canciones_colab == NULL) {
		perror("No se pudo abrir archivo");
		return -1;
	}

	cancion_t cancion;
	int leidos = fread(&cancion, sizeof(cancion_t), 1, canciones_colab);
	while (leidos == 1) {
		if (strcmp(cancion.colaborador, "Charly") != 0 || cancion.duracion < DURACION) {
			fwrite(&cancion, sizeof(cancion_t), 1, canciones_colab_aux);
		}

		leidos = fread(&cancion, sizeof(cancion_t), 1, canciones_colab);
	}

	fclose(canciones_colab);
	fclose(canciones_colab_aux);

	FILE* canciones_colab_aux_lectura = fopen("canciones_aux.dat", "r");
	leidos = fread(&cancion, sizeof(cancion_t), 1, canciones_colab);
	while (leidos == 1) {
		fread(&cancion, sizeof(cancion_t), 1, canciones_colab_aux_lectura);
		printf("%s - %s\n", cancion.nombre, cancion.artista);

		leidos = fread(&cancion, sizeof(cancion_t), 1, canciones_colab);
	}

	// rename("canciones_aux.dat", "canciones.dat");
	return 0;
}
