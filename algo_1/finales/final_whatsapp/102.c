#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct amigo {
    char nombre[100];
    int vejez;
    char color[100];
    int altura;
} amigo_t;

void amigos_se_quedaron(amigo_t amigos_mansion[], int tope_mansion,
                        amigo_t amigos_vacaciones[], int tope_vacaciones,
                        amigo_t amigos_se_quedaron[],
                        int *tope_se_quedaron) {
    int i = 0, j = 0;
	int comparacion;
    while (i < tope_mansion && j < tope_vacaciones) {
		comparacion = strcmp(amigos_mansion[i].nombre, amigos_vacaciones[j].nombre);
        if (comparacion == 0) {
			i++;
			j++;
        } else if (comparacion > 0) {
			amigos_se_quedaron[*tope_se_quedaron] = amigos_mansion[i];
			(*tope_se_quedaron)++;
			i++;
		} else {
			j++;
		}
    }

	while (i < tope_mansion) {
		amigos_se_quedaron[*tope_se_quedaron] = amigos_mansion[i];
		(*tope_se_quedaron)++;
		i++;
	}
}
