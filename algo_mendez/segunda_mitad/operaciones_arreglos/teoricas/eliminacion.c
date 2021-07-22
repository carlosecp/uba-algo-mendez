#include "utils.h"

void eliminar_elemento(int vector[], int *tope, int elemento)
{
	bool elemento_encontrado = false;
	int i = 0, elemento_pos;

	while (!elemento_encontrado || (i < (*tope)))
	{
		if (elemento == vector[i])
		{
			elemento_encontrado = true;
			elemento_pos = i;
		}
		i++;
	}

	if (elemento_encontrado)
	{
		for (int i = elemento_pos; i < (*tope); i++)
		{
			vector[i] = vector[i + 1];
		}
		(*tope)--;
	}
}

int main()
{
	int vector[] = {2, 5, 7, 10, 12, 15};
	int tope = sizeof(vector) / sizeof(int);

	imprimir_vector(vector, tope);

	int elemento;
	printf("Elemento a eliminar: ");
	scanf("%i", &elemento);

	eliminar_elemento(vector, &tope, elemento);
	imprimir_vector(vector, tope);

	return 0;
}