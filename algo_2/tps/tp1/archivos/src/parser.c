#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "split.h"

char*
leer_linea(char* buffer, size_t longitud_buffer, FILE* archivo) {
	char* linea_leida = fgets(buffer, (int)longitud_buffer, archivo);
	if (!linea_leida)
		return NULL;

	size_t longitud_string = strlen(buffer);
	if (longitud_string == 0 || buffer[longitud_string - 1] != '\n') {
		char resto_string[MAX_LECTURA];
		leer_linea(resto_string, MAX_LECTURA, archivo);
	}

	buffer[longitud_string - 1] = 0;
	return buffer;
}

char**
obtener_informacion_linea(char* linea_archivo) {
	char** informacion_linea = split(linea_archivo, ';');
	if (!informacion_linea)
		return NULL;

	return informacion_linea;
}

void
free_vector_strings(char** vector_strings) {
	while (*vector_strings) {
		free(*vector_strings);
		vector_strings++;
	}
}

