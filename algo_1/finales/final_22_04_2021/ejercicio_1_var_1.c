#include <stdio.h>
#include <stdlib.h>

/* Coraje tuvo una buena caza de huesos durante sus vacaciones. Recolectó
taaantos taaaantos huesos, que tuvo que hacer un archivo de texto llamado
huesitos.csv para poder guardar la información sobre estos. El archivo se
encuentra ordenado por zona descendentemente, luego por fecha ascendentemente, y
finalmente por hueso alfabéticamente. Ahora que ya está tranquilo en su casa,
antes de enterrarlos, quiere clasificarlos para tener un mayor control, y saber
hasta cuando los puede comer sin que le caigan mal. Cómo anduvo por muchos
lados, primero le gustaría clasificarlos por lugar y luego por fecha.  */

typedef struct fecha {
	int dia;
	int mes;
	int anio;
} fecha_t;

typedef struct hueso {
	char zona[100];
	fecha_t fecha;
	char nombre[100];
} hueso_t;

int main() { 
	FILE *archivo_huesos = fopen("huesitos.csv", "r");

	hueso_t huesos[1000];

	fclose(archivo_huesos);

	return 0; 
}
