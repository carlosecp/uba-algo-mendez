#include "jugabilidad.h"

/* ==== MOVIMIENTO ===== */

void jugada_movimiento(juego_t *juego, char jugada)
{
	juego->personaje.ultimo_movimiento = jugada;
	switch (jugada)
	{
	case TECLA_MOVER_ARRIBA:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_ARRIBA);
		break;
	case TECLA_MOVER_ABAJO:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_ABAJO);
		break;
	case TECLA_MOVER_DERECHA:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_DERECHA);
		break;
	case TECLA_MOVER_IZQUIERDA:
		mover_personaje(&(juego->personaje.posicion), MOVER_PERSONAJE_IZQUIERDA);
		break;
	}

	manejar_colision(juego);

	if (hay_herramienta_en_uso(juego->personaje))
	{
		utilizar_linterna(juego, true);
	}
}

void mover_personaje(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento)
{
	coordenada_t coordenada_objetivo = {
			.fil = coordenada_actual->fil + direccion_movimiento.fil,
			.col = coordenada_actual->col + direccion_movimiento.col};

	if (coordenada_esta_en_el_mapa(coordenada_objetivo))
	{
		coordenada_actual->fil = coordenada_objetivo.fil;
		coordenada_actual->col = coordenada_objetivo.col;
	}
}

bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada)
{
	return ((coordenada_buscada.fil >= 0) && (coordenada_buscada.fil < CANTIDAD_FILAS)) && ((coordenada_buscada.col >= 0) && (coordenada_buscada.col < CANTIDAD_COLUMNAS));
}

/* ==== HERRAMIENTAS ===== */

void jugada_utilizar_herramienta(juego_t *juego, char tipo_herramienta)
{
	juego->personaje.elemento_en_uso = hay_herramienta_en_uso(juego->personaje) ? NINGUN_ELEMENTO_EN_USO : buscar_herramienta_en_mochila(&(juego->personaje), tipo_herramienta);

	bool iluminar = hay_herramienta_en_uso(juego->personaje);
	switch (tipo_herramienta)
	{
	case LINTERNA:
		utilizar_linterna(juego, iluminar);
	}
}

int buscar_herramienta_en_mochila(personaje_t *personaje, char tipo_herramienta)
{
	bool herramienta_disponible = false;
	int ubicacion_herramienta = NINGUN_ELEMENTO_EN_USO;

	int i = 0;
	while ((i < personaje->cantidad_elementos) && !herramienta_disponible)
	{
		if ((personaje->mochila[i].tipo == tipo_herramienta) && (personaje->mochila[i].movimientos_restantes > 0))
		{
			ubicacion_herramienta = i;
		}
		i++;
	}

	return ubicacion_herramienta;
}

bool hay_herramienta_en_uso(personaje_t personaje)
{
	return (personaje.elemento_en_uso > NINGUN_ELEMENTO_EN_USO);
}

void cantidad_herramientas_disponibles(personaje_t personaje, int *cantidad_linternas, int *cantidad_velas, int *cantidad_bengalas)
{
	// for (int i = 0; i < personaje.cantidad_elementos; i++)
	// {
	// 	printf("%c, ", personaje.mochila[i].tipo);
	// }
	// printf("%i", personaje.mochila[0].movimientos_restantes);
	// printf("\n");

	for (int i = 0; i < personaje.cantidad_elementos; i++)
	{
		switch (personaje.mochila[i].tipo)
		{
		case LINTERNA:
			*(cantidad_linternas) += 1;
			break;
		case VELA:
			*(cantidad_velas) += 1;
			break;
		case BENGALA:
			*(cantidad_bengalas) += 1;
			break;
		}
	}
}

/* ==== HERRAMIENTAS: LINTERNA ===== */

void utilizar_linterna(juego_t *juego, bool iluminar)
{
	if (juego->personaje.elemento_en_uso == NINGUN_ELEMENTO_EN_USO)
	{
		printf("NINGUN ELEMENTO EN USO");
	}

	switch (juego->personaje.ultimo_movimiento)
	{
	case TECLA_MOVER_ARRIBA:
		iluminar_columna(juego, false, iluminar);
		break;
	case TECLA_MOVER_ABAJO:
		iluminar_columna(juego, true, iluminar);
		break;
	case TECLA_MOVER_DERECHA:
		iluminar_fila(juego, false, iluminar);
		break;
	case TECLA_MOVER_IZQUIERDA:
		iluminar_fila(juego, true, iluminar);
		break;
	}

	agregar_koala_nom_nom(juego);
}

void esconder_todos_elementos_del_mapa(juego_t *juego)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		juego->obstaculos[i].visible = false;
	}
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

/* ==== ELEMENTOS DEL MAPA ===== */

void manejar_colision(juego_t *juego)
{
	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->obstaculos[i].posicion))
		{
		}
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (son_misma_coordenada(juego->personaje.posicion, juego->herramientas[i].posicion))
		{
			agregar_recolectable_a_mochila(&(juego->personaje), juego->herramientas[i].tipo);
			remover_recolectable_del_mapa(i, juego);
		}
	}
}

void agregar_recolectable_a_mochila(personaje_t *personaje, char tipo_recolectable)
{
	if (personaje->cantidad_elementos < MAX_HERRAMIENTAS)
	{
		agregar_herramienta_del_tipo_a_mochila(tipo_recolectable, 1, personaje->mochila, &(personaje->cantidad_elementos), personaje->tipo);
	}
}

void remover_recolectable_del_mapa(int indice_elemento, juego_t *juego)
{
	for (int i = indice_elemento; i < juego->cantidad_herramientas; i++)
	{
		juego->herramientas[i] = juego->herramientas[i + 1];
	}
	juego->cantidad_herramientas--;
}

/* ==== AUXILIARES UTILIZACION LINTERNA ===== */

/* ==== AUXILIARES UTILIZACION BENGALA ===== */