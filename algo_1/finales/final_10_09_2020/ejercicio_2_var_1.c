#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_TIRADAS 100
#define MAX_SECCIONES 10

/*
Gandalf y Saruman fueron los 2 condidatos a quedarse con la presidencia del
ministerio de Magia.

Luego de una reñida y siempre polémica votación, quedaron empatados en 35.
Decidieron, sin mucha discusión, que el próximo presidente se determinará
tirando los dardos. Para ponerle suspenso, el blanco será especial, los
concursantes solo saben a que sección del blanco le pegaron, pero no saben el
puntaje que les otorga.

Las tiradas de Gandalf se volcaron a un archivo binario de acceso secuencial
llamado gandalf.dat y los de saruman a un archivo binario de acceso secuencial
llamado saruman.dat.

Ambos archivos están ordenados por número de tiro y están compuestos de
registros del tipo tiro_t:
 */

typedef struct tiro {
    int tiro_numero;
    int id_seccion;
} tiro_t;

/* Por otro lado, se cuenta con un archivo binario de acceso directo ordenado
por id_seccion, secciones.dat que cuenta con los puntajes de las secciones del
blanco. En este archivo, las secciones son números enteros correlativos que
comienzan desde el 1 y tiene registros del tipo seccion_t: */

typedef struct seccion {
    int id_seccion;
    int puntaje;
} seccion_t;

/* En caso de no haberle acertado al blanco, se guardará -1 en ese tiro en los
 * archivos de Gandalf y Saruman, y ese tiro no sumará puntos. */

/* 1. Determinar quien se consagrará presidente del ministerio de magia. */

int encontrar_puntaje_seccion(FILE *archivo_secciones, int id_seccion) {
	seccion_t seccion_temp;
	bool seccion_encontrada = false;
	int i = 0, puntaje = -1;

	int leidos = fread(&seccion_temp, sizeof(seccion_t), 1, archivo_secciones);
	while (!seccion_encontrada && i < MAX_SECCIONES) {
		if (seccion_temp.id_seccion == id_seccion) {
			seccion_encontrada = true;
			puntaje = seccion_temp.puntaje;
		}
		leidos = fread(&seccion_temp, sizeof(seccion_t), 1, archivo_secciones);
		i++;
	}

	return puntaje;
}

int main() {
	FILE *archivo_gandalf = fopen("gandalf.dat", "r");
	FILE *archivo_saruman = fopen("saruman.dat", "r");
	FILE *archivo_secciones = fopen("secciones.dat", "r");

	if (!archivo_gandalf || !archivo_saruman || !archivo_secciones) {
		perror("Error al abrir los archivos.");
		return -1;
	}

	tiro_t tirada_temp;
	int i = 0;
	int puntaje_temp = 0;

	// Tiradas Gandalf
	tiro_t tiradas_gandalf[MAX_TIRADAS];
	int tope_gandalf = 0, puntos_gandalf = 0;

	int leidos = fread(&tirada_temp, sizeof(tiro_t), 1, archivo_gandalf);
	while(!feof(archivo_gandalf)) {
		puntaje_temp = encontrar_puntaje_seccion(archivo_secciones, tirada_temp.id_seccion);

		if (puntaje_temp == 0) {
			puntos_gandalf += puntaje_temp;
		}

		leidos = fread(&tirada_temp, sizeof(tiro_t), 1, archivo_gandalf);
		tope_gandalf++;
	}
	// Hacer lo mismo para Saruman y luego solo comparar

	// Tiradas Saruman
	tiro_t tiradas_saruman[MAX_TIRADAS];
	int tope_saruman = 0, puntos_saruman = 0;

	// Cerrando los archivos
	fclose(archivo_gandalf);
	fclose(archivo_saruman);
	fclose(archivo_secciones);

	return 0;
}
