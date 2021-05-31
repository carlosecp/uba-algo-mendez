#include <stdlib.h>
#include "osos_contra_reloj.h"
#include "tablero.h"
#include "elementos.h"

void generar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos)
{
	for (int i = 0; i < CANTIDAD_ARBOLES; i++)
	{
		coordenada_t nueva_coordenada = generar_coordenada_aleatoria();
		elemento_del_mapa_t obstaculo_arbol = {ARBOL, nueva_coordenada, false};
		obstaculos[i] = obstaculo_arbol;
		(*cantidad_obstaculos)++;
	}

	for (int i = (*cantidad_obstaculos); i < ((*cantidad_obstaculos) + CANTIDAD_PIEDRAS); i++)
	{
		coordenada_t nueva_coordenada = generar_coordenada_aleatoria();
		elemento_del_mapa_t obstaculo_piedra = {PIEDRA, nueva_coordenada, false};
		obstaculos[i] = obstaculo_piedra;
		(*cantidad_obstaculos)++;
	}
}

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

void llenar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS])
{
	elemento_mochila_t elemento = {'C', 1};
	for (int i = 0; i < MAX_HERRAMIENTAS; i++)
	{
		mochila[i] = elemento;
	}
}