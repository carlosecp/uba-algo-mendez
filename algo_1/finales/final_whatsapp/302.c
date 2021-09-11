#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alumno {
    char nombre[100];
    char nombre_corrector[100];
    int nota;
} alumno_t;

void imprimir_alumnos() {
    FILE *arch_info = fopen("informacion.txt", "r");

    char nombre_arch_alumnos[100];
    char nombre_corrector[100];
    int nota_buscada;
    fscanf(arch_info, "%*[^=]=%[^\n]\n", nombre_arch_alumnos);
    fscanf(arch_info, "%*[^=]=%[^\n]\n", nombre_corrector);
    fscanf(arch_info, "%*[^=]=%i\n", &nota_buscada);

    FILE *arch_alumnos = fopen(nombre_arch_alumnos, "r");

    alumno_t alumnos[100];
    int tope_alumnos = 0;

    alumno_t alumno_temp;
    int leidos = fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
    while (!feof(arch_alumnos)) {
        if (strcmp(alumno_temp.nombre_corrector, nombre_corrector) == 0 &&
            alumno_temp.nota == nota_buscada) {
            printf("Alumno...");
        }
        leidos = fread(&alumno_temp, sizeof(alumno_t), 1, arch_alumnos);
    }

    fclose(arch_info);
    fclose(arch_alumnos);
}
