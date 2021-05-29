#include <stdlib.h>
#include <stdio.h>

#include "osos_contra_reloj.h"
#include "mapa.h"

int main()
{
	coordenada_t coordenada = generar_coordenada_aleatoria();
	printf("Coordenada: {%i, %i}\n", coordenada.fil, coordenada.col);

	personaje_t personaje;
	personaje.posicion = coordenada;
	personaje.tipo = 'X';

	juego_t juego;
	juego.personaje = personaje;

	renderizar_mapa(juego);

	return 0;
}