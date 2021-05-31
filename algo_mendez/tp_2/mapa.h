#ifndef __MAPA_H__
#define __MAPA_H__

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

coordenada_t generar_coordenada_aleatoria();

void llenar_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);

void posicionar_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion_elemento, char representacion_elemento);

void mover_elemento(coordenada_t *posicion_actual, int incremento_fila, int incremento_columna);

#endif /* MAPA_H */