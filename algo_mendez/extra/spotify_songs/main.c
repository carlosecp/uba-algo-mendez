#include "canciones.h"

#define NOMBRE_ARTISTA "The Weeknd"

#define NOMBRE_ARCHIVO_ELIMINADAS "canciones_eliminadas.dat"

void buscar_cancion_artista(FILE *archivo_canciones,
                            char nombre_artista[MAX_ARTISTA]) {
  cancion_t cancion_temp;
  bool se_encontraron_canciones = false;

  printf("Canciones encontradas: \n");

  int leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones);
  while (leidos != 0) {
    if (strcmp(cancion_temp.artista, nombre_artista) == 0) {
      se_encontraron_canciones = true;

      printf("ID: %s\n", cancion_temp.id);
      printf("Nombre: %s\n", cancion_temp.nombre);
      printf("Popularidad: %i\n", cancion_temp.popularidad);
      printf("Duracion: %0.fs\n", cancion_temp.duracion_ms / 1000);
      printf("Explicita: %s\n", cancion_temp.explicita == 1 ? "Si" : "No");
      printf("Fecha Lanzamiento: %i/%i/%i\n",
             cancion_temp.fecha_lanzamiento.dia,
             cancion_temp.fecha_lanzamiento.mes,
             cancion_temp.fecha_lanzamiento.anio);
      printf("Bailabilidad: %f\n", cancion_temp.bailabilidad);
      printf("Energia: %f\n\n", cancion_temp.energia);
    }
    leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_canciones);
  }
}

void eliminar_canciones_duracion(FILE *archivo_original, FILE *archivo_nuevo,
                                 char nombre_artista[MAX_ARTISTA], float duracion_minima) {
	cancion_t cancion_temp;

	int leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_original);
	while (leidos != 0) {
		if (strcmp(cancion_temp.artista, nombre_artista) != 0 && cancion_temp.duracion_ms >= duracion_minima) {
			fwrite(&cancion_temp, sizeof(cancion_t), 1, archivo_nuevo);
		}

		leidos = fread(&cancion_temp, sizeof(cancion_t), 1, archivo_original);
	}
}

int main() {
  FILE *archivo_canciones = fopen(NOMBRE_ARCHIVO_BIN, "r");

  if (archivo_canciones == NULL) {
    fprintf(stderr, "Error al abrir el archivo: %s", NOMBRE_ARCHIVO_BIN);
    return ERROR;
  }

  buscar_cancion_artista(archivo_canciones, NOMBRE_ARTISTA);

	FILE *archivo_canciones_eliminadas = fopen(NOMBRE_ARCHIVO_ELIMINADAS, "w");

  if (archivo_canciones == NULL) {
    fprintf(stderr, "Error al crear el archivo: %s", NOMBRE_ARCHIVO_ELIMINADAS);
    return ERROR;
  }

  fclose(archivo_canciones);
	fclose(archivo_canciones_eliminadas);

  return EXITO;
}
