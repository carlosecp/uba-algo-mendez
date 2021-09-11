#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct amigo {
	char nombre[100];
	int vejez;
	char color[100];
	int altura;
} amigo_t;

void encontrar_amigos_sin_vacaciones(amigo_t total_amigos[], int tope_total_amigos,
									 amigo_t amigos_vacaciones[], int tope_amigos_vacaciones, 
									 amigo_t amigos_sin_vacaciones[], int *tope_amigos_sin_vacaciones) {
	int i = 0, j = 0;

	int comp;
	while (i < tope_total_amigos && j < tope_amigos_vacaciones) {
		comp = strcmp(total_amigos[i].nombre, amigos_vacaciones[j].nombre);
		if (comp == 0) {
			i++;
			j++;
		} else if (comp < 0) {
			amigos_sin_vacaciones[*tope_amigos_sin_vacaciones] = total_amigos[i];
			(*tope_amigos_sin_vacaciones)++;
			i++;
		} else {
			j++;
		}
	}

	while (i < tope_total_amigos) {
		amigos_sin_vacaciones[*tope_amigos_sin_vacaciones] = total_amigos[i];
		(*tope_amigos_sin_vacaciones)++;
		i++;
	}
}
