#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANCION 100
#define MAX_ARTISTA 100
#define MAX_COLAB 100
#define MAX_GENERO 20

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
4. Sabiendo que el archivo generos.dat no contiene más de 20 géneros, ordénelo por
nombre.
 */

void inicializar_generos(genero_t generos[], int tope) {
	genero_t genero_temp;
	int min;

	for (int i = 0; i < (tope - 1); i++) {
		min = i;
		for (int j = i + 1; i < tope; j++) {
			if (strcmp(generos[j].nombre, generos[min].nombre) < 0) {
				min = j;
			}
		}

		genero_temp = generos[i];
		generos[i] = generos[min];
		generos[min] = genero_temp;
	}
}

void ordenar_generos(FILE *archivo_generos_aux) {

}

int main() {
    FILE *archivo_generos = fopen("generos.dat", "r");
	FILE *archivo_generos_aux = fopen("generos_aux.dat", "r");

    if (!archivo_generos || !archivo_generos_aux) {
        perror("Error al abrir los archivos");
        return -1;
    }

	genero_t generos[MAX_GENERO];
	size_t tope = fread(generos, sizeof(genero_t), MAX_GENERO, archivo_generos);
	ordenar_generos(archivo_generos_aux);

    return 0;
}
