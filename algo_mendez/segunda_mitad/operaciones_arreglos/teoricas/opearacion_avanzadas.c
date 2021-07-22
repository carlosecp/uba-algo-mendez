#include "utils.c"

// Simplemente combina los dos vectores
// Permite repetidos
// tope_final = tope_1 + tope_2 siempre
void mezcla_vectores(int vector_1[], int tope_1, int vector_2[], int tope_2, int mezcla[], int *tope_mezcla)
{
	int i = 0, j = 0;
	(*tope_mezcla) = 0;

	while (i < tope_1 && j < tope_2)
	{
		if (vector_1[i] <= vector_2[j])
		{
			mezcla[(*tope_mezcla)] = vector_1[i];
			i++;
		}
		else
		{
			mezcla[(*tope_mezcla)] = vector_2[j];
			j++;
		}
		(*tope_mezcla)++;
	}

	while (i < tope_1)
	{
		mezcla[(*tope_mezcla)] = vector_2[j];
		(*tope_mezcla)++;
		j++;
	}

	while (j < tope_2)
	{
		mezcla[(*tope_mezcla)] = vector_1[i];
		(*tope_mezcla)++;
		i++;
	}
}

// Solo agrega valores no repetidos
// El tema con la diferencia es que siempre es la diferencia de un vector respecto al otro, no las diferencias de ambos.
// Asi por ejemplo, diferencia(vector_1, vector_2) no es lo mismo que diferencia(vector_2, vector_1).
void diferencia_vectores(int vector_1[], int tope_1, int vector_2[], int tope_2, int diferencia[], int *tope_diferencia)
{
	int i = 0, j = 0;
	(*tope_diferencia) = 0;

	while (i < tope_1 && j < tope_2)
	{
		if (vector_1[i] == vector_2[j])
		{
			// Si son iguales directamente paso, no agrego nada.
			i++;
			j++;
		}
		else if (vector_1[i] < vector_2[j])
		{
			diferencia[(*tope_diferencia)] = vector_1[i];
			(*tope_diferencia)++;
			i++;
		}
		else
		{
			j++;
		}
	}

	// Si nos quedamos sin elementos en el vector_2
	while (i < tope_1)
	{
		diferencia[(*tope_diferencia)] = vector_1[i];
		(*tope_diferencia)++;
		i++;
	}
}

// Bastante sencillo este algoritmo
void interseccion_vectores(int vector_1[], int tope_1, int vector_2[], int tope_2, int interseccion[], int *tope_interseccion)
{
	int i = 0, j = 0;
	(*tope_interseccion) = 0;

	while (i < tope_1 && j < tope_2)
	{
		if (vector_1[i] == vector_2[j])
		{
			interseccion[(*tope_interseccion)] = vector_1[i];
			(*tope_interseccion)++;
			i++;
			j++;
		}
		else if (vector_1[i] < vector_2[j])
		{
			i++;
		}
		else
		{
			j++;
		}
	}
}
