#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"
#include "utiles.h"
#include "movimiento.h"
#include "herramientas.h"
#include "estadisticas.h"

void inicializar_juego(juego_t *juego, char tipo_personaje)
{
	juego->personaje = inicializar_personaje(*juego, tipo_personaje);
	juego->amiga_chloe = inicializar_amiga_chloe(juego);
	inicializar_obstaculos(juego);
	inicializar_herramientas(juego);
	iniciar_cronometro();
}

int estado_juego(juego_t juego)
{
	return son_misma_coordenada(juego.personaje.posicion, juego.amiga_chloe) ? -1 : 0;
}

void realizar_jugada(juego_t *juego, char jugada)
{
	if (!es_jugada_valida(jugada))
	{
		juego->personaje.ultimo_movimiento = MOVIMIENTO_INVALIDO;
		return;
	}

	switch (jugada)
	{
	case TECLA_MOVER_ARRIBA:
	case TECLA_MOVER_ABAJO:
	case TECLA_MOVER_DERECHA:
	case TECLA_MOVER_IZQUIERDA:
		jugada_movimiento(juego, jugada);
		break;
	case TECLA_ENCENDER_LINTERNA:
	case TECLA_ENCENDER_VELA:
	case TECLA_ENCENDER_BENGALA:
		jugada_utilizar_herramienta(juego, jugada);
		break;
	case TECLA_VER_TIEMPO_RESTANTE:
		juego->personaje.ultimo_movimiento = TECLA_VER_TIEMPO_RESTANTE;
		break;
	}
}

void mostrar_juego(juego_t juego)
{
	char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
	posicionar_todos_elementos_en_mapa(mapa, juego);

	renderizar_estadisticas(juego);
	renderizar_bordes_mapa(true);
	for (int i = 0; i < (CANTIDAD_FILAS + 1); i++)
	{
		if (i == 0)
			printf("║    ");
		else
			printf("║ %02i ", (i - 1));

		for (int j = 0; j < CANTIDAD_COLUMNAS; j++)
		{
			if (i == 0)
				printf("%02i ", j);
			else
				renderizar_emoji_en_mapa(mapa[i - 1][j]);
		}
		printf(" ║");
		printf("\n");
	}
	renderizar_bordes_mapa(false);
}

bool es_jugada_valida(char jugada)
{
	bool jugada_valida = false;
	switch (jugada)
	{
	case TECLA_MOVER_ARRIBA:
	case TECLA_MOVER_ABAJO:
	case TECLA_MOVER_DERECHA:
	case TECLA_MOVER_IZQUIERDA:
	case TECLA_ENCENDER_LINTERNA:
	case TECLA_ENCENDER_VELA:
	case TECLA_ENCENDER_BENGALA:
	case TECLA_VER_TIEMPO_RESTANTE:
		jugada_valida = true;
	}

	return jugada_valida;
}
