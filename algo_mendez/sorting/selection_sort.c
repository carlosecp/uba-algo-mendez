#include "utils.h"

void selection_sort(int vector[], int tope)
{
	int temp, minimo;
	for (int i = 0; i < (tope - 1); i++)
	{
		minimo = i;
		for (int j = (i + 1); j < tope; j++)
		{
			if (vector[j] < vector[minimo])
			{
				minimo = j;
			}
		}

		temp = vector[i];
		vector[i] = vector[minimo];
		vector[minimo] = temp;
	}
}

int main(int argc, char *argv[])
{
	int vector[MAX_VECTOR];
	int tope = 0;

	cargar_vector(vector, &tope, argc, argv);

	imprimir_vector(vector, tope);
	selection_sort(vector, tope);
	imprimir_vector(vector, tope);

	return 0;
}