#include <stdlib.h>
#include <stdio.h>

#define MAX_CANCION 100
#define MAX_ARTISTA 100
#define MAX_COLAB 100


/* Es sabido que la federalidad y democracia reinan en la cátedra y uno, solo uno de los ámbitos
donde se ve reflejada la diversidad es en la música. El departamento de Recursos Humanos
armó una bella playlist con varias canciones que cada colaborador seleccionó a su gusto y
piacere, sin limitaciones, sin juzgar, sin preguntar. */

/* Se nos disponibilizaron 2 archivos, uno binario de acceso secuencial, llamado canciones.dat con
las canciones elegidas por los integrantes de la cátedra, compuesto de registros del tipo
cancion_t y otro, también binario de acceso directo llamado generos.dat donde se guardaron
todos los géneros musicales, con la particularidad de que este archivo contiene ids de género
únicos y correlativos, empezando desde el 1. */

typedef struct cancion {
	char nombre[MAX_CANCION];
	char artista[MAX_ARTISTA];
	char colaborador[MAX_COLAB];
	int duracion;
	int id_genero;
} cancion_t;

int main() {
	return 0;
}
