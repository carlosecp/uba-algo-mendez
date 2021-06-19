#include "herramientas.h"

void jugada_utilizar_herramienta(juego_t *juego, char jugada)
{
	if (juego->personaje.ultimo_movimiento == SIN_MOVIMIENTOS)
	{
		return;
	}

	juego->personaje.elemento_en_uso = buscar_herramienta_en_mochila(juego->personaje, jugada);

	if (juego->personaje.elemento_en_uso == NINGUNA_HERRAMIENTA_EN_USO)
	{
		return;
	}

	switch (jugada)
	{
	case TECLA_ENCENDER_LINTERNA:
		utilizar_linterna(juego);
		break;
	}
}

int buscar_herramienta_en_mochila(personaje_t personaje, char tipo_herramienta)
{
	bool herramienta_disponible = false;
	int ubicacion_herramienta = NINGUNA_HERRAMIENTA_EN_USO;
	elemento_mochila_t herramienta_en_uso = personaje.mochila[personaje.elemento_en_uso];

	int i = 0;
	while ((i < personaje.cantidad_elementos) && !herramienta_disponible)
	{
		elemento_mochila_t herramienta = personaje.mochila[i];

		if ((herramienta.tipo == tipo_herramienta) && herramienta_tiene_movimientos(herramienta) && (herramienta_en_uso.tipo != tipo_herramienta))
		{
			ubicacion_herramienta = i;
		}
		i++;
	}

	return ubicacion_herramienta;
}

bool herramienta_tiene_movimientos(elemento_mochila_t herramienta)
{
	return herramienta.movimientos_restantes > 0;
}

void consumir_uso_herramienta(personaje_t *personaje)
{
	if (herramienta_tiene_movimientos(personaje->mochila[personaje->elemento_en_uso]))
	{
		personaje->mochila[personaje->elemento_en_uso].movimientos_restantes -= 1;
	}
	else
	{
		personaje->elemento_en_uso = NINGUNA_HERRAMIENTA_EN_USO;
	}
}

/* ==== LINTERNA ==== */

void utilizar_linterna(juego_t *juego)
{
	consumir_uso_herramienta(&(juego->personaje));

	bool herramienta_disponible = herramienta_tiene_movimientos(juego->personaje.mochila[juego->personaje.elemento_en_uso]);

	if (!herramienta_disponible)
	{
		juego->personaje.elemento_en_uso = -1;
	}

	switch (juego->personaje.ultimo_movimiento)
	{
	case TECLA_MOVER_ARRIBA:
		iluminar_columna(juego, false, herramienta_disponible);
		break;
	case TECLA_MOVER_ABAJO:
		iluminar_columna(juego, true, herramienta_disponible);
		break;
	case TECLA_MOVER_DERECHA:
		iluminar_fila(juego, false, herramienta_disponible);
		break;
	case TECLA_MOVER_IZQUIERDA:
		iluminar_fila(juego, true, herramienta_disponible);
		break;
	}

	agregar_koala_nom_nom(juego);
}

void iluminar_fila(juego_t *juego, bool revertir_direccion, bool iluminar)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (iluminar && fila_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion, revertir_direccion))
			juego->obstaculos[i].visible = true;
		else
			juego->obstaculos[i].visible = false;
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (iluminar && fila_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion, revertir_direccion))
			juego->herramientas[i].visible = true;
		else
			juego->herramientas[i].visible = false;
	}
}

void iluminar_columna(juego_t *juego, bool revertir_direccion, bool iluminar)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (iluminar && columna_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion, revertir_direccion))
			juego->obstaculos[i].visible = true;
		else
			juego->obstaculos[i].visible = false;
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (iluminar && columna_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion, revertir_direccion))
			juego->herramientas[i].visible = true;
		else
			juego->herramientas[i].visible = false;
	}
}

bool fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion)
{
	if (!revertir_direccion)
		return ((posicion_elemento.col > posicion_personaje.col) && (posicion_elemento.fil == posicion_personaje.fil));

	return ((posicion_elemento.col < posicion_personaje.col) && (posicion_elemento.fil == posicion_personaje.fil));
}

bool columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion)
{
	if (!revertir_direccion)
		return ((posicion_elemento.fil < posicion_personaje.fil) && (posicion_elemento.col == posicion_personaje.col));

	return ((posicion_elemento.fil > posicion_personaje.fil) && (posicion_elemento.col == posicion_personaje.col));
}