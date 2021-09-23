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

	char caracter_leido;
	while ((caracter_leido = (char)fgetc(archivo)) != EOF) {
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
	}

	buffer -> contenido[buffer -> cantidad_caracteres] = 0;
	fclose(archivo);
	return buffer;
}

char**
parser_obtener_lineas(buffer_t* buffer, char separador) {
	char** lineas = split(buffer -> contenido, separador);
	if (!lineas)
		return NULL;

	return lineas;
}
