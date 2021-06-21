#include "estadisticas.h"

void renderizar_introduccion()
{
	printf("═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n\n");
	printf(" ██████╗ ███████╗ ██████╗ ███████╗     ██████╗ ██████╗ ███╗   ██╗████████╗██████╗  █████╗     ██████╗ ███████╗██╗      ██████╗      ██╗\n");
	printf("██╔═══██╗██╔════╝██╔═══██╗██╔════╝    ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗    ██╔══██╗██╔════╝██║     ██╔═══██╗     ██║\n");
	printf("██║   ██║███████╗██║   ██║███████╗    ██║     ██║   ██║██╔██╗ ██║   ██║   ██████╔╝███████║    ██████╔╝█████╗  ██║     ██║   ██║     ██║\n");
	printf("██║   ██║╚════██║██║   ██║╚════██║    ██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██╗██╔══██║    ██╔══██╗██╔══╝  ██║     ██║   ██║██   ██║\n");
	printf("╚██████╔╝███████║╚██████╔╝███████║    ╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║  ██║    ██║  ██║███████╗███████╗╚██████╔╝╚█████╔╝\n");
	printf(" ╚═════╝ ╚══════╝ ╚═════╝ ╚══════╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝    ╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝  ╚════╝ \n\n");
	printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
	printf("║                                                Creador: Carlos Eduardo Castillo                                                     ║\n");
	printf("║                                                        Legajo: 108535                                                               ║\n");
	printf("║                                   Cátedra: Algoritmos y Programación I - 75.40 y 95.14 - Méndez                                     ║\n");
	printf("╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
	printf("║ Un día, aburridos de estar encerrados, los Osos y Chloe decidieron salir al bosque y jugar a las escondidas. Sin embargo, se olvi-  ║\n");
	printf("║ daron del toque de queda que rige debido a los aumentos de casos de Covid en la ciudad y ya está oscureciendo. Además tienen otro   ║\n");
	printf("║ problema: Chloe sigue escondida y no sabe que ya tienen que volver a casa.                                                          ║\n");
	printf("║                                                                                                                                     ║\n");
	printf("║ Ayudá a tu oso a encontrar a su amiga antes de que comience el confinamiento obligatorio.                                           ║\n");
	printf("║                                                                                                                                     ║\n");
	printf("║ ¡Pero hay un problema más! Ya se hizo de noche en el bosque y el personaje no podrá ver nada de lo que hay a su alrededor, y debe-  ║\n");
	printf("║ rá ayudarse de su linterna, velas y bengalas para poder llegar a encontrarse con su amiga.                                          ║\n");
	printf("╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
	printf(" » Presiona Cualquier Tecla para Continuar...");
	getchar();
}

void renderizar_estadisticas(juego_t juego)
{
	renderizar_bordes_estadisticas();
	renderizar_tiempo_elapsado(juego.personaje);
	if (juego.personaje.tipo == PARDO)
	{
		renderizar_gps(juego);
	}
	renderizar_ultimo_movimiento(juego.personaje.ultimo_movimiento);
	renderizar_bordes_estadisticas();
	renderizar_mochila(juego.personaje);
}

void renderizar_tiempo_elapsado(personaje_t personaje)
{
	if (personaje.ultimo_movimiento == TECLA_VER_TIEMPO_RESTANTE)
	{
		printf(" » Tiempo Elapsado: %.1fs\n", tiempo_actual());
	}
	else
	{
		printf(" » Tiempo Elapsado: Presionar \"T\" Para Mostrar\n");
	}
	printf(" » Tiempo Perdido: %.1fs\n", personaje.tiempo_perdido);
}

void renderizar_gps(juego_t juego)
{
	if (juego.personaje.tiempo_perdido > TIEMPO_PERDIDO_ACTIVAR_GPS)
	{
		printf(" » Posicion Amiga Chloe: { fil: %02i, col: %02i }\n", juego.amiga_chloe.fil, juego.amiga_chloe.col);
	}
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
	case SIN_MOVIMIENTOS:
		printf("Sin Movimientos Aún");
		break;
	case MOVIMIENTO_INVALIDO:
		printf("Movimiento Inválido");
		break;
	}
	printf("\n");
}

void renderizar_mochila(personaje_t personaje)
{
	printf(" » Mochila: [");
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
	printf("]\n");

	printf(" » Herramienta Utilizada: ");

	switch (personaje.elemento_en_uso)
	{
	case NINGUNA_HERRAMIENTA_EN_USO:
		printf("Ninguna Herramienta en Uso\n");
		break;
	default:
		printf("%c\n", personaje.mochila[personaje.elemento_en_uso].tipo);
	}
}

void renderizar_bordes_estadisticas()
{
	int espacios_extra = 7;
	for (int i = 0; i < (CANTIDAD_COLUMNAS * 3) + espacios_extra; i++)
	{
		printf("═");
	}
	printf("\n");
}

void renderizar_bordes_mapa(bool borde_superior)
{
	int espacios_extra = 7;
	for (int i = 0; i < (CANTIDAD_COLUMNAS * 3) + espacios_extra; i++)
	{
		if (i == 0)
		{
			printf("%s", borde_superior ? "╔" : "╚");
		}
		else if (i == ((CANTIDAD_COLUMNAS * 3) + (espacios_extra - 1)))
		{
			printf("%s", borde_superior ? "╗" : "╝");
		}
		else
		{
			printf("═");
		}
	}
	printf("\n");
}

void renderizar_resultados_juego(juego_t juego)
{
	double tiempo_total = tiempo_actual() + juego.personaje.tiempo_perdido;
	printf("\n");
	if (tiempo_total < TIEMPO_LIMITE)
	{
		printf(" ██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗ █████╗ ██╗██╗██╗\n");
		printf(" ██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗██║██║██║\n");
		printf(" ██║   ██║██║██║        ██║   ██║   ██║██████╔╝██║███████║██║██║██║\n");
		printf(" ╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗██║██╔══██║╚═╝╚═╝╚═╝\n");
		printf("  ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║██║██║  ██║██╗██╗██╗\n");
		printf("   ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚═╝╚═╝╚═╝\n");
	}
	else
	{
		printf(" ██████╗ ███████╗██████╗ ██████╗  ██████╗ ████████╗ █████╗ ██╗██╗██╗\n");
		printf(" ██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██║██║██║\n");
		printf(" ██║  ██║█████╗  ██████╔╝██████╔╝██║   ██║   ██║   ███████║██║██║██║\n");
		printf(" ██║  ██║██╔══╝  ██╔══██╗██╔══██╗██║   ██║   ██║   ██╔══██║╚═╝╚═╝╚═╝\n");
		printf(" ██████╔╝███████╗██║  ██║██║  ██║╚██████╔╝   ██║   ██║  ██║██╗██╗██╗\n");
		printf(" ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝╚═╝\n");
	}
}