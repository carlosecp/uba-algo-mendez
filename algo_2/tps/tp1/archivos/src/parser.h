#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>

#define MAX_LECTURA 1024

char* leer_linea(char* buffer, size_t longitud_buffer, FILE* archivo);

char** obtener_informacion_linea(char* linea_archivo);

void free_vector_strings(char** vector_strings);

#endif
