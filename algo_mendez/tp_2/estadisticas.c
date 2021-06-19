#include "estadisticas.h"

void renderizar_estadisticas(personaje_t personaje)
{
	renderizar_tiempo_elapsado();
	renderizar_ultimo_movimiento(personaje.ultimo_movimiento);
	renderizar_mochila(personaje);
}

void renderizar_tiempo_elapsado()
{
	printf(" » Tiempo Elapsado: %.0fs\n", tiempo_actual());
}

void renderizar_ultimo_movimiento(char ultimo_movimiento)
{
	printf(" » Ultimo Movimiento: ");
	switch (ultimo_movimiento)
	{
	case TECLA_MOVER_ARRIBA:
		printf("Arriba");
		break;
	case TECLA_MOVER_ABAJO:
		printf("Abajo");
		break;
	case TECLA_MOVER_DERECHA:
		printf("Derecha");
		break;
	case TECLA_MOVER_IZQUIERDA:
		printf("Izquierda");
		break;
	case TECLA_ENCENDER_LINTERNA:
		printf("Linterna Encendida");
		break;
	case TECLA_ENCENDER_VELA:
		printf("Vela Encendida");
		break;
	case TECLA_VER_TIEMPO_RESTANTE:
		printf("Ver Tiempo Restante");
		break;
	case MOVIMIENTO_INVALIDO:
		printf("Movimiento Invalido");
		break;
	case SIN_MOVIMIENTOS:
		printf("Sin Movimientos Aún");
	}
	printf("\n");
}

void renderizar_mochila(personaje_t personaje)
{
	int cantidad_usos_linterna_disponibles = 0;
	int cantidad_velas_disponibles = 0;
	int cantidad_bengalas_disponibles = 0;

	printf("\n » Mochila: [");
	for (int i = 0; i < personaje.cantidad_elementos; i++)
	{
		if (i == personaje.cantidad_elementos - 1)
		{
			printf("%c", personaje.mochila[i].tipo);
		}
		else
		{
			printf("%c,", personaje.mochila[i].tipo);
		}
	}
	printf("]\n");

	printf(" » Usos Herramientas: [");
	for (int i = 0; i < personaje.cantidad_elementos; i++)
	{
		if (i == personaje.cantidad_elementos - 1)
		{
			printf("%i", personaje.mochila[i].movimientos_restantes);
		}
		else
		{
			printf("%i,", personaje.mochila[i].movimientos_restantes);
		}
	}
	printf("]\n\n");

	printf(" » Herramienta Utilizada: %i\n", personaje.elemento_en_uso);

	printf(" » Herramientas Disponibles:\n");
	printf(" • Usos Linterna: %i\n", cantidad_usos_linterna_disponibles);
	printf(" • Velas: %i\n", cantidad_velas_disponibles);
	printf(" • Bengalas: %i\n", cantidad_bengalas_disponibles);
}
