#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 100

/*
La cátedra tiene un instagram. Sigannos. Fin del ejercicio.
Los colabs están cansados de pedirle la cuenta de Instagram a Manu, hubo varios intentos, pero
todos fallidos. Es por eso que los colabs están empezando a juntar firmas, en un archivo, para
que Manu largue el insta. Pero, lo peor de todo, es que ninguno de ellos sabe programar, ni
saben abrir un archivo (no le digan a nadie). Así que con la excusa de dar clases les pidieron a
los alumnos una ayuda

Se tiene en el archivo firmas_para_la_liberacion_del_insta.txt las firmas conseguidas. Donde
cada firma está compuesta por los siguientes campos:

● Nombre de la persona
● Voto (0 si está en contra, y 1 si está a favor).

El archivo tiene sus campos separados por un ; (punto y coma).
Un ejemplo del archivo:

Charly;1
Delfi;1
Manu;0

a) Imprimir por pantalla cada firma que hay en el archivo, según si votaron a favor (1) o en
contra (0):

○ "Charly votó a favor! Ya te mando el cuarto de helado prometido.".
○ "Manu votó en contra. No hay helado para él. >:c".

b) Charly se hizo el vivo y firmó varias veces a favor. Borrar todos los votos repetidos de
Charly del archivo.
*/

int main() {
	FILE *archivo_firmas = fopen("firmas_para_la_liberacion_del_insta.txt", "r");
	FILE *archivo_sin_charly = fopen("firmas_sin_charly.txt", "w");

	if (!archivo_firmas) {
		perror("Error al abrir el archivo: firmas_para_la_liberacion_del_insta.txt");
	}

	if (!archivo_sin_charly) {
		perror("Error al abrir el archivo: firmas_sin_charly.txt");
	}

	char nombre_colab[MAX_NOMBRE];
	int voto_colab;

	bool charly_voto = false;

	int leidos = fscanf(archivo_firmas, "%[^;];%i\n", nombre_colab, &voto_colab);
	while (leidos == 2) {
		if (!charly_voto || strcmp(nombre_colab, "Charly") != 0) {
			fprintf(archivo_sin_charly, "%s;%i\n", nombre_colab, voto_colab);
			if (strcmp(nombre_colab, "Charly") == 0) charly_voto = true;
		}
		leidos = fscanf(archivo_firmas, "%[^;];%i\n", nombre_colab, &voto_colab);
	}

	fclose(archivo_firmas);
	fclose(archivo_sin_charly);

	return 0;
}

