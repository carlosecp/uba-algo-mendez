#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void
merge(int v_1[], size_t tope_1, int v_2[], size_t tope_2)
{
	int v_3[tope_1 + tope_2];
	size_t i_1 = 0, i_2 = 0, i_3 = 0;

	while (i_1 < tope_1 && i_2 < tope_2) {
		if (v_1[i_1] <= v_2[i_2])
			v_3[i_3++] = v_1[i_1++];
		else
			v_3[i_3++] = v_2[i_2++];
	}

	while (i_1 < tope_1)
		v_3[i_3++] = v_1[i_1++];

	while (i_2 < tope_2)
		v_3[i_3++] = v_2[i_2++];

	memcpy(v_1, v_3, (tope_1 + tope_2) * sizeof(int));
}

void
merge_sort(int vector[], size_t tope)
{
	if (tope <= 1)
		return;

	size_t mid = tope / 2;

	merge_sort(vector, mid);
	merge_sort(vector + mid, tope - mid);

	merge(vector, mid, vector + mid, tope - mid);
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

	merge_sort(elementos, cantidad);

	mostrar_vector(elementos, cantidad);

	return 0;
}
