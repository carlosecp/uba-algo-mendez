#include "archivo.h"
#include "split.h"
#include "string.h"

char*
archivo_leer(FILE* archivo, size_t max_caracteres_inicial) {
	if (!archivo)
		return NULL;

	size_t cantidad_caracteres = 0;
	size_t max_caracteres = max_caracteres_inicial;
	char* contenido_archivo = malloc((max_caracteres_inicial + 1) * sizeof(char));
	if (!contenido_archivo)
		return NULL;

	char caracter_leido;
	while ((caracter_leido = (char)fgetc(archivo)) != EOF) {
		if (cantidad_caracteres >= (max_caracteres - 1)) {
			char* contenido_aux = realloc(contenido_archivo, (max_caracteres * 2) + 1);
			if (!contenido_aux) {
				free(contenido_archivo);
				return NULL;
			}
			contenido_archivo = contenido_aux;
			max_caracteres *= 2;
		}
		contenido_archivo[cantidad_caracteres] = caracter_leido;
		cantidad_caracteres++;
	}
	contenido_archivo[cantidad_caracteres] = 0;

	fclose(archivo);
	return contenido_archivo;
}

size_t
archivo_cantidad_registros(char** lineas_registros) {
	size_t cantidad_registros = 0;
	while (*lineas_registros) {
		cantidad_registros++;
		lineas_registros++;
	}

	return cantidad_registros;
}

char**
archivo_leer_linea_registro(char* linea_registro) {
	if (!linea_registro)
		return NULL;

	return split(linea_registro, ';');
}

void
free_vector_strings(char** vector_strings) {
	for (size_t i = 0; vector_strings[i]; i++)
		free(vector_strings[i]);

	free(vector_strings);
}
