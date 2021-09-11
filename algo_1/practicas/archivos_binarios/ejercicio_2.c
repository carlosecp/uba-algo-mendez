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
2. Crear un procedimiento que reciba cómo argumento el nombre de un colaborador
y un número y elimine del archivo de canciones, todas aquellas cuya duración sea
menor al número ingresado y pertenezcan a ese colaborador.
 */

void eliminar_colab_duracion(FILE *archivo_canciones, FILE *archivo_canciones_aux, char nombre_colab[], int duracion_min) {
	cancion_t cancion_temp;

	int leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones);
	while (!feof(archivo_canciones)) {
		if (strcmp(cancion_temp.colaborador, nombre_colab) != 0 || cancion_temp.duracion < duracion_min) {
			fwrite(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones_aux);
		}

		leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones);
	}
}

int main() {
	FILE *archivo_canciones = fopen("canciones.dat", "r");
	FILE *archivo_canciones_aux = fopen("canciones_aux.dat", "w");

	if (!archivo_canciones || !archivo_canciones_aux) {
		perror("Error al abrir los archivos");
		return -1;
	}

	return 0;
}
