#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_NOMBRE 25
typedef struct pelicula {
	char nombre[MAX_NOMBRE];
	short anio;
	bool pasa_bechdel_test;
	char opinion;
} pelicula_t;

void imprimir_pelicula(pelicula_t pelicula) {
	printf("Nombre: %s\n", pelicula.nombre);
	printf("Anio: %hi\n", pelicula.anio);
	printf("Pasa el test de Bechel?: %c\n", pelicula.pasa_bechdel_test ? 'S' : 'N');
	printf("Opinion: %c\n", pelicula.opinion);
}

int main() {
	FILE *resenias = fopen("resenias.dat", "r");

	if (resenias == NULL) {
		perror("No se puede abrir el archivo");
		return -1;
	}

	pelicula_t pelicula;
	int leidos = fread(&pelicula, sizeof(pelicula_t), 1, resenias);

	while (leidos != EOF) {
		imprimir_pelicula(pelicula);
		leidos = fread(&pelicula, sizeof(pelicula_t), 1, resenias);
	}

	return 0;
}
