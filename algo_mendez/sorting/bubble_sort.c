#include "utils.h"

void bubble_sort(int vector[], int tope)
{
	int temp;
	for (int i = 0; i < (tope - 1); i++)
	{
		for (int j = 0; j < (tope - i - 1); j++)
		{
			if (vector[j] > vector[j + 1])
			{
				temp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = temp;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int vector[MAX_VECTOR];
	int tope = 0;

	cargar_vector(vector, &tope, argc, argv);

	imprimir_vector(vector, tope);
	bubble_sort(vector, tope);
	imprimir_vector(vector, tope);

	return 0;
}