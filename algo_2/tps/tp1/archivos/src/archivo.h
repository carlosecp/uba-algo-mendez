#ifndef ARCHIVO_H__
#define ARCHIVO_H__

#include <stdlib.h>
#include <stdio.h>
#include "hospital.h"

typedef struct _entrenador_t {
    int id;
    char* nombre;
} entrenador_t;

char* archivo_leer(FILE* archivo, size_t max_caracteres_inicial);

char** archivo_separar_lineas_registros(char* contenido_archivo);

size_t archivo_cantidad_registros(char** lineas_registros);

char** archivo_leer_linea_registro(char* linea_registro);

void free_vector_strings(char** vector_strings);

#endif