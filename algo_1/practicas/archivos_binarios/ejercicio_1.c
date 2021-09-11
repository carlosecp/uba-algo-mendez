#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANCION 100
#define MAX_ARTISTA 100
#define MAX_COLAB 100
#define MAX_GENERO 10

/* Es sabido que la federalidad y democracia reinan en la cátedra y uno, solo
uno de los ámbitos donde se ve reflejada la diversidad es en la música. El
departamento de Recursos Humanos armó una bella playlist con varias canciones
que cada colaborador seleccionó a su gusto y piacere, sin limitaciones, sin
juzgar, sin preguntar. */

/* Se nos disponibilizaron 2 archivos, uno binario de acceso secuencial, llamado
canciones.dat con las canciones elegidas por los integrantes de la cátedra,
compuesto de registros del tipo cancion_t y otro, también binario de acceso
directo llamado generos.dat donde se guardaron todos los géneros musicales, con
la particularidad de que este archivo contiene ids de género únicos y
correlativos, empezando desde el 1. */

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

/*
1. Crear un procedimiento que reciba cómo argumento el nombre de un colaborador
y muestre por pantalla las canciones elegidas por ese colab.
 */

void mostrar_canciones_de_colab(FILE *archivo_canciones, char nombre_colab[]) {
	cancion_t cancion_temp;

	int leidos = fread(&cancion_temp, sizeof(cancion_temp), 1, archivo_canciones);
	while(!feof(archivo_canciones)) {
		if (strcmp(cancion_temp.colaborador, nombre_colab) == 0) {
			printf("%s - %s\n", cancion_temp.nombre, cancion_temp.artista);
		}
		leidos = fread(&cancion_temp, sizeof(cancion_temp), 1, archivo_canciones);
	}
}

int main() { 
	FILE *archivo_canciones = fopen("canciones.dat", "r");

	if (archivo_canciones == NULL) {
		perror("Error al abrir el archivo");
		return -1;
	}

	return 0; 
}
