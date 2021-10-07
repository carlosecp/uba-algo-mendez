#ifndef DYNAMIC_STRING_AUX_H_
#define DYNAMIC_STRING_AUX_H_

#include <stdlib.h>

typedef struct {
	char* contenido;
	size_t cantidad_caracteres;
	size_t max_caracteres;
} string_t;

size_t string_cantidad_caracteres(string_t* string);

#endif