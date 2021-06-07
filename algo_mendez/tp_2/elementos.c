#include <stdlib.h>
#include "osos_contra_reloj.h"
#include "tablero.h"
#include "elementos.h"

void generar_personaje(personaje_t *personaje, char tipo_personaje)
{
	personaje->tipo = tipo_personaje;
	personaje->posicion = generar_coordenada_aleatoria();
	llenar_mochila(personaje->mochila);
	personaje->cantidad_elementos = 10;
	personaje->elemento_en_uso = 1;
	personaje->tiempo_perdido = 1;
	personaje->ultimo_movimiento = 'W';
}

void generar_obstaculos(juego_t *juego)
{
	for (int i = 0; i < CANTIDAD_ARBOLES; i++)
	{
		elemento_del_mapa_t nuevo_obstaculo;
		nuevo_obstaculo.posicion = generar_coordenada_aleatoria();
		nuevo_obstaculo.tipo = ARBOL;
		nuevo_obstaculo.visible = true;

		juego->obstaculos[i] = nuevo_obstaculo;
		juego->cantidad_obstaculos++;
	}

	for (int i = CANTIDAD_ARBOLES; i < MAX_OBSTACULOS; i++)
	{
		elemento_del_mapa_t nuevo_obstaculo;
		nuevo_obstaculo.posicion = generar_coordenada_aleatoria();
		nuevo_obstaculo.tipo = PIEDRA;
		nuevo_obstaculo.visible = true;

		juego->obstaculos[i] = nuevo_obstaculo;
		juego->cantidad_obstaculos++;
	}
}

void llenar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS])
{
	elemento_mochila_t elemento = {'C', 1};
	for (int i = 0; i < MAX_HERRAMIENTAS; i++)
	{
		mochila[i] = elemento;
	}
}