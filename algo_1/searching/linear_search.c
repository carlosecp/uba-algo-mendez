#include "utils.h"

int linear_search(int vector[], int tope, int elemento)
{
	bool encontrado = false;
	int pos = -1;
	int i = 0;

	while (!encontrado && i < tope)
	{
		if (vector[i] == elemento)
		{
			encontrado = true;
			pos = i;
		}
		i++;
	}

	return pos;
}

int main(int argc, char *argv[])
{
	int vector[] = {2418, 8603, 26168, 30197, 24650, 7330, 27114, 14814, 14977, 6253};
	int tope = sizeof(vector) / sizeof(vector[0]);

	imprimir_vector(vector, tope);

	int elemento;
	printf("Buscar: ");
	scanf("%i", &elemento);

	int pos = linear_search(vector, tope, elemento);
	printf("Posicion elemento: %i", pos);

	return 0;
}