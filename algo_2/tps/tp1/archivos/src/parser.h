#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>

#define CANTIDAD_CARACTERES 1024

/**
  *
  */
char* leer_linea(FILE* archivo);

/**
  *
  */
char** obtener_informacion_linea(char* linea_archivo);

/**
  *
  */
void free_vector_strings(char** vector_strings);

#endif
