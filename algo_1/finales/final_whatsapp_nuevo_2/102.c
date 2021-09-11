#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct amigo
{
	char nombre[100];
	int vejez;
	char color[100];
	int altura;
} amigo_t;

void amigos_que_no_fueron_de_vacas(amigo_t amigos_mansion[], int tope_mansion, amigo_t amigos_vacaciones[], int tope_vacaciones, amigo_t amigos_se_quedaron[], int *tope_se_quedaron)
{
	int i = 0, j = 0;
	int comp;

	while (i < tope_mansion && j < tope_vacaciones)
	{
		comp = strcmp(amigos_mansion[i].nombre, amigos_vacaciones[j].nombre);
		if (comp == 0)
		{
			i++;
			j++;
		}
		else if (comp < 0)
		{
			amigos_se_quedaron[*tope_se_quedaron] = amigos_mansion[i];
			(*tope_se_quedaron)++;
			i++;
		}
		else
		{
			j++;
		}
	}

	while (i < tope_mansion)
	{
		amigos_se_quedaron[*tope_se_quedaron] = amigos_mansion[i];
		(*tope_se_quedaron)++;
		i++;
	}
}