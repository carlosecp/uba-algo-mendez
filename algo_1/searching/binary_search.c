#include "utils.h"

int binary_search(int vector[], int low, int high, int elemento)
{
	int mid;
	if (low <= high)
	{
		mid = (high + low) / 2;
		if (elemento == vector[mid])
			return mid;

		if (elemento < vector[mid])
			return binary_search(vector, low, (mid - 1), elemento);

		if (elemento > vector[mid])
			return binary_search(vector, (mid + 1), high, elemento);
	}
	else
		return -1;
}

int main(int argc, char *argv[])
{
	int vector[] = {2418, 6253, 7330, 8603, 14814, 14977, 24650, 26168, 27114, 30197};

	int tope = sizeof(vector) / sizeof(vector[0]);

	imprimir_vector(vector, tope);

	int elemento;
	printf("Buscar: ");
	scanf("%i", &elemento);

	int pos = binary_search(vector, 0, tope, elemento);
	printf("Posicion elemento: %i", pos);

	return 0;
}