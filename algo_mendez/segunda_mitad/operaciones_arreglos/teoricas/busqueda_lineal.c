#include "utils.h"

int busqueda_lineal(int vector[], int tope, int elemento)
{
	bool elemento_encontrado = false;
	int i = 0, pos = -1;

	while (!elemento_encontrado || i < tope)
	{
		if (elemento == vector[i])
		{
			elemento_encontrado = true;
			pos = i;
		}
		i++;
	}

	return pos;
}

int main()
{
	int vector[] = {2, 5, 7, 10, 12, 15};
	int tope = sizeof(vector) / sizeof(int);

	imprimir_vector(vector, tope);

	int elemento;
	printf("Elemento a buscar: ");
	scanf("%i", &elemento);

	int pos = busqueda_lineal(vector, tope, elemento);
	printf("Posicion elemento: %i\n", pos);

	return 0;
}