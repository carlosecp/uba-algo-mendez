#include "utils.h"

int binary_search(int vector[], int elemento, int low, int high)
{
	int mid = low + (high - low) / 2;

	if (low <= high)
	{
		if (elemento == vector[mid])
			return mid;

		if (elemento < vector[mid])
			return binary_search(vector, elemento, low, (mid - 1));

		if (elemento > vector[mid])
			return binary_search(vector, elemento, (mid + 1), high);
	}

	return -1;
}

int main()
{
	int vector[] = {2, 5, 7, 10, 12, 15};
	int tope = sizeof(vector) / sizeof(int);

	imprimir_vector(vector, tope);

	int elemento;
	printf("Elemento a buscar: ");
	scanf("%i", &elemento);

	int pos = binary_search(vector, elemento, 0, tope);
	printf("Posicion elemento: %i\n", pos);

	return 0;
}