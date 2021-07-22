#include "utils.h"

void imprimir_vector(int vector[], int tope)
{
	printf("[");
	for (int i = 0; i < tope; i++)
	{
		if (i == (tope - 1))
		{
			printf("%i", vector[i]);
		}
		else
		{
			printf("%i, ", vector[i]);
		}
	}
	printf("]\n");
}
