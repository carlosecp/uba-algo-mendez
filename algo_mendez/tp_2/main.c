#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "osos_contra_reloj.h"
#include "tablero.h"

void ubicar_personaje()
{
	coordenada_t coordenada_personaje = generar_coordernada_aleatoria();
	printf("Coordenada: {%i, %i}", coordenada_personaje.fil, coordenada_personaje.col);
}

int main()
{
	coordenada_t coordenada = generar_coordernada_aleatoria();
	printf("Coordenada: {%i, %i}", coordenada.fil, coordenada.col);
	return 0;
}