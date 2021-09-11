#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct victoria
{
	char nombre_enemigo[1000];
	bool es_monstruo;
	int dificultad;
} victoria_t;

void insertar_victoria(victoria_t victorias_totales[], int *tope_totales, victoria_t nueva_victoria)
{
	bool insertado = false;
	int comparacion;
	victoria_t victoria_aux;

	for (int i = 0; i < (*tope_totales); i++)
	{
		comparacion = strcmp(nueva_victoria.nombre_enemigo, victorias_totales[i].nombre_enemigo);
		if (comparacion < 0)
		{
			victoria_aux = victorias_totales[i];
			victorias_totales[i] = nueva_victoria;
			nueva_victoria = victoria_aux;
		}
	}

	if (insertado)
	{
		victorias_totales[*tope_totales] = victoria_aux;
		(*tope_totales)++;
	}

	if (!insertado || *tope_totales == 0)
	{
		victorias_totales[*tope_totales] = nueva_victoria;
		(*tope_totales)++;
	}
}

int actualizar_victorias(victoria_t victorias_totales[], int *tope_totales, victoria_t victorias_faltantes[], int tope_faltantes)
{
	int i = 0, j = 0;
	int comparacion;

	while (i < *tope_totales && j < tope_faltantes)
	{
		comparacion = strcmp(victorias_totales[i].nombre_enemigo, victorias_faltantes[j].nombre_enemigo);
		if (comparacion < 0)
		{
			insertar_victoria(victorias_totales, &(*tope_totales), victorias_totales[i]);
			i++;
		}
		else if (comparacion < 0)
		{
			insertar_victoria(victorias_totales, &(*tope_totales), victorias_faltantes[j]);
			j++;
		}
	}
}
