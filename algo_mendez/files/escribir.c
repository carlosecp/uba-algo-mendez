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

void pedir_pelicula(pelicula_t *pelicula) {
	printf("Nombre: ");
	scanf("%[^\n]", pelicula->nombre);

	printf("Anio: ");
	scanf("%hi", &(pelicula->anio));

	printf("Pasa el test de Bechel? [S/otro]: ");
	char respuesta;
	scanf("%c ", &respuesta);
	pelicula->pasa_bechdel_test = respuesta == 'S';

	printf("Opinion: ");
	printf("Bueno (B); Regular (R); Malo(M): ");
	scanf("%c ", &(pelicula->opinion));
}

int main() {
	FILE *resenias = fopen("resenias.dat", "a");

	if (resenias == NULL) {
		perror("No se puede abrir el archivo");
		return -1;
	}

	pelicula_t pelicula;
	pedir_pelicula(&pelicula);

	fwrite(&pelicula, sizeof(pelicula_t), 1, resenias);

	fclose(resenias);

	return 0;
}
