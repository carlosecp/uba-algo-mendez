#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vector {
	void** elementos;
	size_t cantidad_elementos;
} vector_t;

typedef struct persona {
	char* nombre;
	unsigned dni;
} persona_t;

vector_t*
vector_crear()
{
	return calloc(1, sizeof(vector_t));
}

void
vector_agregar_elementos(vector_t* vector, void* elemento)
{
	vector -> elementos = realloc(vector -> elementos, sizeof(void*) * (vector -> cantidad_elementos + 1));
	vector -> elementos[vector -> cantidad_elementos] = elemento;
	vector -> cantidad_elementos++;
}

int
main(int argc, char* argv[])
{
	vector_t* vector = vector_crear();

	int i = 10;
	persona_t persona;
	persona.nombre = "Carlos";
	persona.dni = 96113425;

	vector_agregar_elementos(vector, &i);
	vector_agregar_elementos(vector, &persona);

	printf("Numero: %i\n", *(int*)(vector -> elementos[0]));
	printf("Persona: {%s, %d}", (*(persona_t*)(vector -> elementos[1])).nombre, (*(persona_t*)(vector -> elementos[1])).dni);

	return 0;
}
