#include "utils.h"

void insertion_sort(int vector[], int tope)
{
	int j, aux;
	for (int i = 0; i < tope; i++)
	{
		j = i;
		aux = vector[i];

		while ((j > 0) && (aux < vector[j - 1]))
		{
			vector[j] = vector[j - 1];
			j--;
		}

		vector[j] = aux;
	}
}

int main(int argc, char *argv[])
{
	int vector[MAX_VECTOR];
	int tope = 0;

	cargar_vector(vector, &tope, argc, argv);

	imprimir_vector(vector, tope);
	insertion_sort(vector, tope);
	imprimir_vector(vector, tope);

	return 0;
}