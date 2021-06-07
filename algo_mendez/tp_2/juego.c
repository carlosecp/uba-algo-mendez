#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "osos_contra_reloj.h"

int main()
{
	srand((unsigned)time(NULL));
	juego_t juego;
	inicializar_juego(&juego, 'X');
	return 0;
}
