#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct victoria
{
	char nombre_enemigo[100];
	bool es_monstruo;
	int dificultad;
} victoria_t;

void agregar_victorias_olvidadas(victoria_t originales[], int *tope_originales, victoria_t olvidadas[], int tope_olvidadas)
{
	int i = 0, j = 0;

	int comp;
	while (i < *tope_originales && j < tope_olvidadas)
	{
		comp = strcmp(originales[i].nombre_enemigo, olvidadas[j].nombre_enemigo);
		if (comp == 0)
		{
			i++;
			j++;
		}
		else if (comp < 0)
		{
			(*tope_originales)++;
			for (int k = i; i < *tope_originales; i++)
			{
				originales[i + 1] = originales[i];
			}
			originales[i] = olvidadas[j];
			j++;
		}
		else
		{
			i++;
		}
	}
}