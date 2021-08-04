#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR -1
#define NOMBRE_ARCHIVO_CSV "canciones.csv"
#define NOMBRE_ARCHIVO_BIN "canciones.dat"

#define MAX_ID 100
#define MAX_NOMBRE 200
#define MAX_ARTISTA 200

#define CANTIDAD_CAMPOS_LEIDOS 11

typedef struct fecha {
  int dia;
  int mes;
  int anio;
} fecha_t;

typedef struct cancion {
  char id[MAX_ID];
  char nombre[MAX_NOMBRE];
  int popularidad;
  float duracion_ms;
  int explicita;
  char artista[MAX_ARTISTA];
  fecha_t fecha_lanzamiento;
  float bailabilidad;
  float energia;
} cancion_t;

