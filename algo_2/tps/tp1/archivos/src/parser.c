#include <stdlib.h>
#include "parser.h"
#include "split.h"

buffer_t*
buffer_crear() {
	buffer_t* buffer = malloc(sizeof(buffer_t));
	buffer -> cantidad_caracteres = 0;
	buffer -> max_caracteres = buffer -> cantidad_caracteres + 1;
	buffer -> contenido = malloc(((buffer -> max_caracteres) + 1) * sizeof(char));
	if (!(buffer -> contenido)) {
		free(buffer);
		return NULL;
	}

	return buffer;
}

buffer_t*
buffer_leer(FILE* archivo) {
	buffer_t* buffer = buffer_crear();
	if (!buffer)
		return NULL;

	char caracter_leido = (char)fgetc(archivo);
	while (caracter_leido != EOF) {
		if (buffer -> cantidad_caracteres >= (buffer -> max_caracteres) - 1) {
			char* contenido_buffer_aux = realloc(buffer -> contenido, ((buffer -> max_caracteres) * 2) + 1);
			if (!contenido_buffer_aux) {
				free(contenido_buffer_aux);
				return NULL;
			}

			buffer -> contenido = contenido_buffer_aux;
			buffer -> max_caracteres *= 2;
		}

		buffer -> contenido[buffer -> cantidad_caracteres++] = caracter_leido;
		caracter_leido = (char)fgetc(archivo);
	}

	buffer -> contenido[buffer -> cantidad_caracteres] = 0;
	fclose(archivo);
	return buffer;
}

char**
parser_obtener_lineas_archivo(buffer_t* buffer) {
	char** lineas = split(buffer -> contenido, '\n');
	if (!lineas)
		return NULL;

	return lineas;
}

char**
parser_obtener_informacion_linea(char* linea_archivo) {
	char** informacion_linea = split(linea_archivo, ';');
	if (!informacion_linea)
		return NULL;

	return informacion_linea;
}

size_t
parser_obtener_cantidad_registros(char** lineas_archivo) {
	if (!(*lineas_archivo))
		return 0;
	return 1 + parser_obtener_cantidad_registros(lineas_archivo + 1);
}

void
free_vector_strings(char** vector_strings) {
	while (*vector_strings) {
		free(*vector_strings);
		vector_strings++;
	}
}

