/*
En la última clase de consulta, Santi notó que elambiente estaba un poco tenso y decidió pasar
una canción por el chat del meet, esta canción es“Es Un Placer - Omar Koonze”. Sol que estaba
atenta apoyó la moción, y se puso a escuchar la canción,le terminó gustando y decidió agregarla
a su playlist de2021 mamehh, el problema es que ellaordena las canciones según la duración
de las mismas, ascendentemente.

typedef struct canción {
	char nombre[MAX_NOMBRE];
	char artista[MAX_ARTISTA];
	int duracion;
} cancion_t;

1.Dado un vector de canciones de la playlist de Sol,se pide agregar la canción que pasó
Santi por el meet, respetando el orden. Sabiendo quela duración de la canción es 4:20.

2.Pero también, hay canciones que Sol ya escuchó muchoy no le gustan tanto como antes,
por lo que necesita un algoritmo que elimine ordenadamenteuna canción de la playlist,
se elimina por nombre.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 100
#define MAX_ARTISTA 100
#define MAX_CANCIONES 100

typedef struct cancion
{
	char nombre[MAX_NOMBRE];
	char artista[MAX_ARTISTA];
	int duracion;
} cancion_t;

void imprimir_canciones(cancion_t canciones[], int tope_canciones)
{
	for (int i = 0; i < tope_canciones; i++)
	{
		printf("Nombre: %s\n", canciones[i].nombre);
		printf("Artista: %s\n", canciones[i].artista);
		printf("Duracion: %i\n\n", canciones[i].duracion);
	}
}

void inicializar_canciones(cancion_t canciones[], int *tope_canciones, int cantidad_canciones)
{
	cancion_t cancion_aux;
	for (int i = 0; i < cantidad_canciones; i++)
	{
		snprintf(cancion_aux.nombre, MAX_NOMBRE, "Cancion %i", i);
		snprintf(cancion_aux.artista, MAX_ARTISTA, "Artista %i", i);
		cancion_aux.duracion = (i * 2) + 10;

		canciones[i] = cancion_aux;
		(*tope_canciones)++;
	}
}

void agregar_cancion(cancion_t canciones[], int *tope_canciones, cancion_t cancion_nueva)
{
	if (*tope_canciones == MAX_CANCIONES)
		return;

	bool canciones_agregada = false;
	cancion_t cancion_temp;

	for (int i = 0; i < *tope_canciones; i++)
	{
		if (cancion_nueva.duracion < canciones[i].duracion)
		{
			cancion_temp = canciones[i];
			canciones[i] = cancion_nueva;
			cancion_nueva = cancion_temp;
		}
	}

	if (canciones_agregada)
	{
		canciones[(*tope_canciones)] = cancion_temp;
		(*tope_canciones)++;
	}

	if (!canciones_agregada || *tope_canciones == 0)
	{
		canciones[(*tope_canciones)] = cancion_nueva;
		(*tope_canciones)++;
	}
}

int eliminar_cancion(cancion_t canciones[], int *tope_canciones, char nombre_cancion[MAX_NOMBRE])
{
	bool cancion_encontrada = false;
	int i = 0, cancion_pos = 0;

	while (!cancion_encontrada && i < *tope_canciones)
	{
		if (strcmp(nombre_cancion, canciones[i].nombre) == 0)
		{
			cancion_encontrada = true;
			cancion_pos = i;
		}
		i++;
	}

	if (cancion_encontrada)
	{
		for (int i = cancion_pos; i < *tope_canciones; i++)
		{
			canciones[i] = canciones[i + 1];
		}
		(*tope_canciones)--;
	}

	return cancion_pos;
}

int main()
{
	cancion_t canciones[MAX_CANCIONES];
	int tope_canciones = 0;
	inicializar_canciones(canciones, &tope_canciones, 5);

	imprimir_canciones(canciones, tope_canciones);

	cancion_t cancion_nueva;
	strcpy(cancion_nueva.nombre, "Nueva Cancion");
	strcpy(cancion_nueva.artista, "Nuevo Artista");
	cancion_nueva.duracion = 15;

	agregar_cancion(canciones, &tope_canciones, cancion_nueva);
	imprimir_canciones(canciones, tope_canciones);

	eliminar_cancion(canciones, &tope_canciones, "Cancion 2");
	imprimir_canciones(canciones, tope_canciones);

	return 0;
}