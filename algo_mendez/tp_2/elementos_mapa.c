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

int agregar_obstaculo(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], char tipo_obstaculo, int cantidad_a_agregar)
{
	if (cantidad_a_agregar <= 0)
	{
		return 0;
	}

	elemento_del_mapa_t nuevo_obstaculo = {
		.tipo = tipo_obstaculo,
		.posicion = generar_coordenada(),
		.visible = true};

	*obstaculos = nuevo_obstaculo;
	return 1 + agregar_obstaculo(++obstaculos, tipo_obstaculo, --cantidad_a_agregar);
}

void generar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos)
{
	*cantidad_obstaculos += agregar_obstaculo(obstaculos, ARBOL, CANTIDAD_ARBOLES) + agregar_obstaculo(obstaculos, PIEDRA, CANTIDAD_PIEDRAS);

	printf("%i", *cantidad_obstaculos);
}
