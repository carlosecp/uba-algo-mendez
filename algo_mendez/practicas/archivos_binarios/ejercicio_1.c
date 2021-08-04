#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANCION 100
#define MAX_ARTISTA 100
#define MAX_COLAB 100

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

/*
1. Crear un procedimiento que reciba cómo argumento el nombre de un colaborador
y muestre por pantalla las canciones elegidas por ese colab.

2. Crear un procedimiento que reciba cómo argumento el nombre de un colaborador
y un número y elimine del archivo de canciones, todas aquellas cuya duración sea
menor al número ingresado y pertenezcan a ese colaborador.
 */

void imprimir_canciones(FILE *archivo_canciones, char nombre_colab[]) {
  cancion_t cancion_temp;

  printf("Canciones que escucha: %s", nombre_colab);

  int leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones);
  while (leidos != 0) {
    if (strcmp(nombre_colab, cancion_temp.colaborador) == 0) {
      printf("Nombre: %s - Artista: %s - Duracion: %i - Genero: %i",
             cancion_temp.nombre, cancion_temp.artista, cancion_temp.duracion,
             cancion_temp.id_genero);
    }
		leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones);
  }
}

void eliminar_canciones(FILE *archivo_canciones, FILE *nuevo_archivo, int duracion_maxima) {

}

int main() {
  FILE *archivo_canciones = fopen("canciones.dat", "r");
  FILE *archivos_generos = fopen("generos.dat", "r");

  return 0;
}
