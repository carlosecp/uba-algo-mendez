#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERSO 100

/*
Después de todos estos años de estar molestando constantemente a Manu pero igual
recibiendo, muy de vez en cuando, algún signo de cariño de parte de éste, Charly decide
dedicarle una canción. Esta canción es muy especial porque la escribió él mismo en una noche
de inspiración. La canción va así *prepara la garganta*:

... aqui va la cancion ...

Se pide escribir un programa el cual dada la letra de la canción en un archivo llamado
cancion_especial.txt, imprima por pantalla la letra completa de la misma.
 */

int main() {
	FILE *cancion_especial = fopen("cancion_especial.txt", "r");

	if (!cancion_especial) {
		perror("Error al abrir archivo: cancion_especial.txt");
		return -1;
	}

	char verso[MAX_VERSO];
	int leidos = fscanf(cancion_especial, "%[^\n]\n", verso);
	
	// Solo estoy leyendo un dato, en este caso una string de un solo...
	while (leidos == 1) {
		printf("%s\n", verso);
		leidos = fscanf(cancion_especial, "%[^\n]\n", verso);
	}

	fclose(cancion_especial);

	return 0;
}
