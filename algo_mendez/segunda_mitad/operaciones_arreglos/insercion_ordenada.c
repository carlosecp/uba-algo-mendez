#include "utils.h"

void insercion_ordenada(int vector[MAX], int *tope, int elemento)
{
	bool elemento_insertado = false;
	int elemento_aux;

	for (int i = 0; i < (*tope); i++)
	{
		if (elemento < vector[i])
		{
			elemento_aux = vector[i];
			vector[i] = elemento;
			elemento = elemento_aux;
			elemento_insertado = true;
		}
	}

	if (elemento_insertado)
	{
		vector[(*tope)] = elemento_aux;
		(*tope)++;
	}

	if (!elemento_insertado || (*tope) == 0)
	{
		vector[(*tope)] = elemento;
		(*tope)++;
	}
}

int main(int argc, char *argv[])
{
	int vector[MAX] = {2, 5, 7, 10, 12, 15};
	int tope = 6;

	imprimir_vector(vector, tope);

	int elemento;
	printf("Elemento a ingresar: ");
	scanf("%i", &elemento);

	insercion_ordenada(vector, &tope, elemento);
	imprimir_vector(vector, tope);

	return 0;
}