#include "herramientas.h"

/* ==== UTILIZACIÓN DE HERRAMIENTAS ===== */

void jugada_utilizar_herramienta(juego_t *juego, char jugada)
{
	if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == BENGALA)
	{
		juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes--;
		return;
	}

	if ((juego->personaje.elemento_en_uso != NINGUNA_HERRAMIENTA_EN_USO && !es_herramienta_valida(jugada)) || (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == jugada))
	{
		juego->personaje.elemento_en_uso = NINGUNA_HERRAMIENTA_EN_USO;
	}
	else
	{
		juego->personaje.elemento_en_uso = buscar_herramienta_en_mochila(juego->personaje, jugada);
	}

	utilizar_herramienta(juego, jugada);
}

bool es_herramienta_valida(char jugada)
{
	bool herramienta_valida = false;
	switch (jugada)
	{
		case TECLA_ENCENDER_LINTERNA:
		case TECLA_ENCENDER_VELA:
		case TECLA_ENCENDER_BENGALA:
			herramienta_valida = true;
	}
	return herramienta_valida;
}

bool herramienta_se_puede_usar(personaje_t personaje)
{
	return (personaje.elemento_en_uso != NINGUNA_HERRAMIENTA_EN_USO && herramienta_tiene_movimientos(personaje));
}

void utilizar_herramienta(juego_t *juego, char tipo_herramienta)
{
	if (herramienta_se_puede_usar(juego->personaje))
	{
		juego->personaje.mochila[juego->personaje.elemento_en_uso].movimientos_restantes -= 1;
	}
	else if (herramienta_se_puede_eliminar(juego->personaje))
	{
		eliminar_herramienta_de_mochila(&(juego->personaje));
		juego->personaje.elemento_en_uso = NINGUNA_HERRAMIENTA_EN_USO;
	}
	else
	{
		juego->personaje.elemento_en_uso = NINGUNA_HERRAMIENTA_EN_USO;
	}

	bool iluminar = !(juego->personaje.elemento_en_uso == NINGUNA_HERRAMIENTA_EN_USO);

	switch (tipo_herramienta)
	{
		case LINTERNA:
			utilizar_linterna(juego, iluminar);
			break;
		case VELA:
			utilizar_vela(juego, iluminar);
			break;
		case BENGALA:
			utilizar_bengala(juego, iluminar);
			break;
	}
}

void utilizar_misma_herramienta(juego_t *juego)
{
	if (juego->personaje.elemento_en_uso != NINGUNA_HERRAMIENTA_EN_USO)
	{
		utilizar_herramienta(juego, juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo);
	}
}

int buscar_herramienta_en_mochila(personaje_t personaje, char tipo_herramienta)
{
	bool herramienta_disponible = false;
	int ubicacion_herramienta = NINGUNA_HERRAMIENTA_EN_USO;

	int i = 0;
	while ((i < personaje.cantidad_elementos) && !herramienta_disponible)
	{
		if (personaje.mochila[i].tipo == tipo_herramienta)
		{
			ubicacion_herramienta = i;
			herramienta_disponible = true;
		}
		i++;
	}

	return ubicacion_herramienta;
}

bool herramienta_se_puede_eliminar(personaje_t personaje)
{
	return ((personaje.elemento_en_uso != NINGUNA_HERRAMIENTA_EN_USO) && (personaje.mochila[personaje.elemento_en_uso].tipo != LINTERNA) && (!herramienta_tiene_movimientos(personaje)));
}

void eliminar_herramienta_de_mochila(personaje_t *personaje)
{
	for (int i = personaje->elemento_en_uso; i < personaje->cantidad_elementos; i++)
	{
		personaje->mochila[i] = personaje->mochila[i + 1];
	}
	personaje->cantidad_elementos--;
}

bool herramienta_tiene_movimientos(personaje_t personaje)
{
	return (personaje.mochila[personaje.elemento_en_uso].movimientos_restantes > 0);
}

/* ==== LINTERNA ==== */

void utilizar_linterna(juego_t *juego, bool iluminar)
{
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

void iluminar_fila(juego_t *juego, bool revertir_direccion, bool iluminar)
{
	if (iluminar && linterna_fila_es_iluminable(juego->personaje.posicion, juego->amiga_chloe, revertir_direccion))
		juego->chloe_visible = true;
	else
		juego->chloe_visible = false;

	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (iluminar && linterna_fila_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion, revertir_direccion))
			juego->obstaculos[i].visible = true;
		else
			juego->obstaculos[i].visible = false;
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (iluminar && linterna_fila_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion, revertir_direccion))
			juego->herramientas[i].visible = true;
		else
			juego->herramientas[i].visible = false;
	}
}

void iluminar_columna(juego_t *juego, bool revertir_direccion, bool iluminar)
{
	if (iluminar && linterna_columna_es_iluminable(juego->personaje.posicion, juego->amiga_chloe, revertir_direccion))
		juego->chloe_visible = true;
	else
		juego->chloe_visible = false;

	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (iluminar && linterna_columna_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion, revertir_direccion))
			juego->obstaculos[i].visible = true;
		else
			juego->obstaculos[i].visible = false;
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (iluminar && linterna_columna_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion, revertir_direccion))
			juego->herramientas[i].visible = true;
		else
			juego->herramientas[i].visible = false;
	}
}

bool linterna_fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion)
{
	if (!revertir_direccion)
		return ((posicion_elemento.col > posicion_personaje.col) && (posicion_elemento.fil == posicion_personaje.fil));

	return ((posicion_elemento.col < posicion_personaje.col) && (posicion_elemento.fil == posicion_personaje.fil));
}

bool linterna_columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion)
{
	if (!revertir_direccion)
		return ((posicion_elemento.fil < posicion_personaje.fil) && (posicion_elemento.col == posicion_personaje.col));

	return ((posicion_elemento.fil > posicion_personaje.fil) && (posicion_elemento.col == posicion_personaje.col));
}

/* ==== VELA ==== */

void utilizar_vela(juego_t *juego, bool iluminar)
{
	if (iluminar && vela_area_es_iluminable(juego->personaje.posicion, juego->amiga_chloe))
		juego->chloe_visible = true;
	else
		juego->chloe_visible = false;

	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (iluminar && vela_area_es_iluminable(juego->personaje.posicion, juego->obstaculos[i].posicion))
			juego->obstaculos[i].visible = true;
		else
			juego->obstaculos[i].visible = false;
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (iluminar && vela_area_es_iluminable(juego->personaje.posicion, juego->herramientas[i].posicion))
			juego->herramientas[i].visible = true;
		else
			juego->herramientas[i].visible = false;
	}
}

bool vela_area_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento)
{
	return (vela_fila_es_iluminable(posicion_personaje, posicion_elemento) && vela_columna_es_iluminable(posicion_personaje, posicion_elemento));
}

bool vela_fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento)
{
	return ((posicion_personaje.fil == posicion_elemento.fil) || (posicion_elemento.fil) == (posicion_personaje.fil + 1) || (posicion_elemento.fil) == (posicion_personaje.fil - 1));
}

bool vela_columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento)
{
	return ((posicion_personaje.col == posicion_elemento.col) || (posicion_elemento.col) == (posicion_personaje.col + 1) || (posicion_elemento.col) == (posicion_personaje.col - 1));
}

/* ==== BENGALA ==== */

void utilizar_bengala(juego_t *juego, bool iluminar)
{
	coordenada_t coordenada_aleatoria = generar_coordenada(*juego, false, false, false, false);

	if (iluminar && esta_a_distancia_manhattan(coordenada_aleatoria, juego->amiga_chloe))
		juego->chloe_visible = true;
	else
		juego->chloe_visible = false;

	for (int i = 0; i < juego->cantidad_obstaculos; i++)
	{
		if (iluminar && esta_a_distancia_manhattan(coordenada_aleatoria, juego->obstaculos[i].posicion))
			juego->obstaculos[i].visible = true;
		else
			juego->obstaculos[i].visible = false;
	}

	for (int i = 0; i < juego->cantidad_herramientas; i++)
	{
		if (iluminar && esta_a_distancia_manhattan(coordenada_aleatoria, juego->herramientas[i].posicion))
			juego->herramientas[i].visible = true;
		else
			juego->herramientas[i].visible = false;
	}
}

bool esta_a_distancia_manhattan(coordenada_t posicion_centro, coordenada_t posicion_elemento)
{
	int diferencia_filas = abs(posicion_centro.fil - posicion_elemento.fil);
	int diferencia_columnas = abs(posicion_centro.col - posicion_elemento.col);

	return (diferencia_filas + diferencia_columnas) <= 3;
}
