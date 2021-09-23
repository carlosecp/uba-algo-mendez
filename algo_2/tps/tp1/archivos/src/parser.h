#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>

typedef struct buffer {
	char* contenido;
	size_t cantidad_caracteres;
	size_t max_caracteres;
} buffer_t;

buffer_t* buffer_leer();

char** parser_obtener_lineas_archivo(buffer_t* buffer);

char** parser_obtener_informacion_linea(char* linea_archivo);

size_t parser_obtener_cantidad_registros(char** lineas_archivo);

void free_vector_strings(char** vector_strings);

#endif
