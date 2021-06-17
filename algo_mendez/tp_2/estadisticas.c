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

	printf("Herramienta utilizada: % i\n", personaje.elemento_en_uso);

	cantidad_herramientas_disponibles(personaje, &cantidad_usos_linterna_disponibles, &cantidad_velas_disponibles, &cantidad_bengalas_disponibles);

	printf("\n » Herramientas Disponibles:\n");
	printf(" • Linternas: %i\n", cantidad_usos_linterna_disponibles);
	printf(" • Velas: %i\n", cantidad_velas_disponibles);
	printf(" • Bengalas: %i\n", cantidad_bengalas_disponibles);
}
