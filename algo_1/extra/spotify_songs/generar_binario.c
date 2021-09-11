#include "canciones.h"

void cargar_canciones_a_binario(FILE *archivo_canciones_csv,
                                FILE *archivo_canciones_bin) {
    cancion_t cancion_temp;

    int leidos = fscanf(
        archivo_canciones_csv, "%[^;];%[^;];%i;%f;%i;%[^;];%i/%i/%i;%f;%f\n",
        cancion_temp.id, cancion_temp.nombre, &cancion_temp.popularidad,
        &cancion_temp.duracion_ms, &cancion_temp.explicita,
        cancion_temp.artista, &cancion_temp.fecha_lanzamiento.dia,
        &cancion_temp.fecha_lanzamiento.mes,
        &cancion_temp.fecha_lanzamiento.anio, &cancion_temp.bailabilidad,
        &cancion_temp.energia);

    int cantidad_agregadas = 0;
    while (leidos == CANTIDAD_CAMPOS_LEIDOS) {
        printf("%3i. Agregando... ", cantidad_agregadas + 1);
        printf("%s - %s\n", cancion_temp.nombre, cancion_temp.artista);

        fwrite(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones_bin);
        cantidad_agregadas++;

        leidos = fscanf(archivo_canciones_csv,
                        "%[^;];%[^;];%i;%f;%i;%[^;];%i/%i/%i;%f;%f\n",
                        cancion_temp.id, cancion_temp.nombre,
                        &cancion_temp.popularidad, &cancion_temp.duracion_ms,
                        &cancion_temp.explicita, cancion_temp.artista,
                        &cancion_temp.fecha_lanzamiento.dia,
                        &cancion_temp.fecha_lanzamiento.mes,
                        &cancion_temp.fecha_lanzamiento.anio,
                        &cancion_temp.bailabilidad, &cancion_temp.energia);
    }
}

int main() {
    FILE *archivo_canciones_csv = fopen(NOMBRE_ARCHIVO_CSV, "r");
    FILE *archivo_canciones_bin = fopen(NOMBRE_ARCHIVO_BIN, "w");

    if (archivo_canciones_csv == NULL) {
        fprintf(stderr, "Error al abrir el archivo: %s", NOMBRE_ARCHIVO_CSV);
        return ERROR;
    }

    if (archivo_canciones_bin == NULL) {
        fprintf(stderr, "Error al crear el archivo: %s", NOMBRE_ARCHIVO_BIN);
        return ERROR;
    }

	cargar_canciones_a_binario(archivo_canciones_csv, archivo_canciones_bin);

    fclose(archivo_canciones_csv);
    fclose(archivo_canciones_bin);

    return EXITO;
}
