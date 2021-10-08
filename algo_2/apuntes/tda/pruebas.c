#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

void
dadaUnaPilaVacia_alPedirElTope_devuelveNULL()
{
	pila_t* pila = pila_crear();

	pa2m_afirmar(pila_tope(pila) == NULL, "Para una pila vacia el tope es NULL");

	pila_destruir(pila);
}

void
dadaUnaPilaConUnElemento_alPedirElTope_devuelveEseElemento()
{
	pila_t* pila = pila_crear();

	int elemento = 20;
	pila_apilar(pila, &elemento);
	pa2m_afirmar(pila_tope(pila) == &elemento, "Para una pila con un elemento el tope ese elemento es el tope");

	pila_destruir(pila);
}

void
dadaUnaPilaVacia_alApilarUnElementoExitosamente_devuelveLaPila()
{
	pila_t* pila = pila_crear();

	int elemento = 20;
	pa2m_afirmar(pila_apilar(pila, &elemento) == pila, "Apilar devuelve una pila");

	pila_destruir(pila);
}

void
dadaUnaPilaVacia_alApilcarUnElementoExitosamente_laPilaQuedaConTamanioUno()
{
	pila_t* pila = pila_crear();

	int elemento = 20;
	pila_apilar(pila, &elemento);
	pa2m_afirmar(pila_tamanio(pila) == 1, "La pila tiene tamanio 1");

	pila_destruir(pila);
}

int main() {
  pa2m_nuevo_grupo("Pruebas y mas pruebas");
  dadaUnaPilaVacia_alPedirElTope_devuelveNULL();

  return pa2m_mostrar_reporte();
}
