#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>

typedef struct buffer {
	char* contenido;
	size_t cantidad_caracteres;
	size_t max_caracteres;
} buffer_t;

buffer_t* buffer_leer();

char** parser_obtener_lineas(buffer_t* buffer, char separador);

#endif
