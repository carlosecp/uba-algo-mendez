/*
Delfi el otro día, después del ejercicio de las comidasse quedó pensando, y creyó que era
buena idea cambiar un poco la dieta, y así no comer tanta porquería. Sabemos que ella es un
poco colgada, entonces nosotros queríamos ayudarlaa que se organice. Por eso, pedimos que
dada las comidas que Delfi está acostumbrada a comer,se completen los siguientes algoritmos:

Recordando la estructura comida_t:

typedef struct comida {
	char nombre[MAX_NOMBRE];
	bool es_vegana;
	bool tiene_tacc;
	int precio;
} comida_t;

El vector de comidas está ordenado alfabéticamente.

1.Dado el vector de comidas de Delfi, y otro vectorde comidas que considera que debe
dejar de comer, actualizar el vector de Delfi paraque ya no contenga tales comidas.

2.Por otro lado, ella hizo una encuesta en Instagrampara que le recomienden nuevas
comidas para sumar a su menú, sabemos que estas comidasestán todas ordenadas
alfabéticamente en un nuevo vector de comidas. Crearun algoritmo que dado el vector
de comidas de Delfi y el vector de nuevas comidas,se cree un tercer vector que
contenga ambos.
Observación: Que pasa si hay comidas repetidas?

3.Últimamente Charly y Delfi se venían peleando, supuestamentese amigaron, nosotros les
creemos... o no. Lo importante es que ellos para demostrarnosque se habían amigado se
iban a juntar a comer, pero pusieron como condiciónque ambos coman lo mismo. ¿Por
qué? Y porque hay que practicar la intersección JAJA.Hacer un algoritmo que dado el
vector de comidas de Charly y el de Delfi, cree untercer vector con las comidas que
ambos tienen en su menú.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMIDAS 100
#define MAX_NOMBRE 100

typedef struct comida
{
	char nombre[MAX_NOMBRE];
	bool es_vegana;
	bool tiene_tacc;
	int precio;
} comida_t;

void eliminar_comida(comida_t comidas[])
{
}

int main()
{
	comida_t comidas[MAX_COMIDAS] = {{"batatas", true, true, 100},
									 {"hummus", true, true, 250},
									 {"papitas", false, true, 350},
									 {"ribs", false, false, 500},
									 {"limonada", true, false, 120}};

	return 0;
}
