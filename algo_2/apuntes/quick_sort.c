#include <stdlib.h>
#include <stdio.h>

void
swap(int vector[], size_t pos_1, size_t pos_2)
{
	int temp = vector[pos_1];
	vector[pos_1] = vector[pos_2];
	vector[pos_2] = temp;
}

size_t
pivot(int vector[], size_t tope)
{
	size_t pos_pivote = tope - 1, pos_pivote_final = 0;

	for (size_t i = 0; i < pos_pivote; i++) {
		if (vector[i] < vector[pos_pivote]) {
			swap(vector, i, pos_pivote_final);
			pos_pivote_final++;
		}
	}

	swap(vector, pos_pivote, pos_pivote_final);

	return pos_pivote_final;
}

void
quick_sort(int vector[], size_t tope)
{
	if (tope <= 1)
		return;

	size_t pos_pivot = pivot(vector, tope);

	quick_sort(vector, pos_pivot);
	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
}

void
mostrar_vector(int vector[], size_t tope)
{
	printf("[");
	for (size_t i = 0; i < tope; i++)
		printf(" %i ", vector[i]);
	printf("]\n");
}

int
main(int argc, char* argv[])
{
	int elementos[] = { 5, 4, 2, 6, 3, 7, 1, 1, 55, 3, 7, 8, 19 };
	size_t cantidad = sizeof(elementos) / sizeof(elementos[0]);

	mostrar_vector(elementos, cantidad);

	quick_sort(elementos, cantidad);

	mostrar_vector(elementos, cantidad);

	return 0;
}
