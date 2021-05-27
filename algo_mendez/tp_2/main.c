#include <stdlib.h>
#include <stdio.h>

#include "osos_contra_reloj.h"
#include "tablero.h"

int main()
{
	coordenada_t coordenada = generar_coordenada_aleatoria();
	printf("Coordenada: {%i, %i}\n", coordenada.fil, coordenada.col);

	tablero_t tablero;
	inicializar_tablero(&tablero);
	ubicar_personaje(&tablero);
	imprimir_tablero(tablero);

	return 0;
}