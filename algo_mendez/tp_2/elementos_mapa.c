#include <stdlib.h>
#include "elementos_mapa.h"
#include "mapa.h"

void generar_personaje(personaje_t *personaje, char tipo_personaje)
{
	personaje->tipo = tipo_personaje;
	personaje->posicion = generar_coordenada();
	// personaje->mochila;
	// personaje->cantidad_elementos;
	// personaje->elemento_en_uso;
	// personaje->tiempo_perdido;
	// personaje->ultimo_movimiento;
	return;
}

void generar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos)
{
	for (int i = 0; i < CANTIDAD_ARBOLES; i++)
	{
		obstaculos[*cantidad_obstaculos] = generar_nuevo_obstaculo(ARBOL);
		(*cantidad_obstaculos)++;
	}

	for (int i = 0; i < CANTIDAD_PIEDRAS; i++)
	{
		obstaculos[*cantidad_obstaculos] = generar_nuevo_obstaculo(PIEDRA);
		(*cantidad_obstaculos)++;
	}
}

elemento_del_mapa_t generar_nuevo_obstaculo(char tipo_obstaculo)
{
	elemento_del_mapa_t nuevo_obstaculo = {.posicion = generar_coordenada(),
										   .tipo = tipo_obstaculo,
										   .visible = false};
	return nuevo_obstaculo;
}
