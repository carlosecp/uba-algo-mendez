#include "utils.h"

int partition(int vector[], int low, int high)
{
	int pivot = vector[high];
	int i = (low - 1); // Greater element index

	int temp;
	for (int j = low; j < high; j++)
	{
		if (vector[j] <= pivot)
		{
			i++;
			temp = vector[i];
			vector[i] = vector[j];
			vector[j] = temp;
		}
	}

	temp = vector[high];
	vector[high] = vector[i + 1];
	vector[i + 1] = temp;

	return (i + 1);
}

void quicksort(int vector[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(vector, low, high);
		quicksort(vector, low, pi - 1);
		quicksort(vector, pi + 1, high);
	}
}

int main(int argc, char *argv[])
{
	int vector[MAX_VECTOR];
	int tope = 0;

	cargar_vector(vector, &tope, argc, argv);

	imprimir_vector(vector, tope);
	quicksort(vector, 0, tope - 1);
	imprimir_vector(vector, tope);

	return 0;
}