#include "parser_archivo.h"

char* leer_contenido_archivo(FILE* archivo, size_t max_caracteres_inicial) {
	if (!archivo)
		return NULL;

	size_t cantidad_caracteres = 0;
	size_t max_caracteres = max_caracteres_inicial;
	char* contenido = malloc((max_caracteres_inicial + 1) * sizeof(char));
	if (!contenido)
		return NULL;

	char caracter_leido;
	while ((caracter_leido = (char)fgetc(archivo)) != EOF) {
		if (cantidad_caracteres >= (max_caracteres - 1)) {
			char* contenido_aux = realloc(contenido, (max_caracteres * 2) + 1);
			if (!contenido_aux) {
				free(contenido);
				return NULL;
			}
			contenido = contenido_aux;
			max_caracteres *= 2;
		}
		contenido[cantidad_caracteres] = caracter_leido;
		cantidad_caracteres++;
	}
	contenido[cantidad_caracteres] = 0;

	fclose(archivo);
	return contenido;
}