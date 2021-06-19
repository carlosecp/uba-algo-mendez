#include "herramientas.h"

void jugada_utilizar_herramienta(juego_t *juego, char jugada)
{
	juego->personaje.elemento_en_uso = buscar_herramienta_en_mochila(juego->personaje, jugada);
}

int buscar_herramienta_en_mochila(personaje_t personaje, char tipo_herramienta)
{
	bool herramienta_disponible = false;
	int ubicacion_herramienta = NINGUNA_HERRAMIENTA_EN_USO;

	int i = 0;
	while ((i < personaje.cantidad_elementos) && !herramienta_disponible && (personaje.mochila[personaje.elemento_en_uso].tipo != tipo_herramienta))
	{
		if ((personaje.mochila[i].tipo == tipo_herramienta) && (personaje.mochila[i].movimientos_restantes > 0))
		{
			ubicacion_herramienta = i;
		}
		i++;
	}

	return ubicacion_herramienta;
}
