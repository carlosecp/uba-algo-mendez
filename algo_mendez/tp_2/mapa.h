#ifndef __MAPA_H__
#define __MAPA_H__

#include "osos_contra_reloj.h"

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

/**
* Genera una coordenada aleatoria.
* @pre Debe haberse establecido una semilla, de tal forma que las coordenadas generadas sean aleatorias.
* @param juego Instancia del juego actual, del cual se van a obtener las coordenadas de los elementos ya existentes para verificar si no hay conflicto.
* @return Nueva coordenada valida.
*/
coordenada_t generar_coordenada(juego_t juego);

/**
* Compara dos coordenadas entre si.
* @param coordenada_a Primera coordenada a comparar.
* @param coordenada_b Segunda coordenada a comparar.
* @return Determina si las coordenadas son las mismas.
*/
bool son_misma_coordenada(coordenada_t coordenada_a, coordenada_t coordenada_b);

/**
* Compara una coordenada generada de manera aleatoria para ver si esta no ha sido utilizada por otro elemento del mapa.
* @param coordenada_buscada Coordenada generada de manera aleatoria.
* @param juego Instancia del juego que contiene la ubicacion de todos los elementos previamente ubicados.
* @return Validez de la coordenada buscada (si ya existe una previamente en esa posicion).
*/
bool coordenada_esta_ocupada(coordenada_t coordenada_buscada, juego_t juego);

/**
* Genera el estado inicial del mapa, antes de que se coloquen los personajes y elementos.
* @param mapa Arreglo de caracteres vacio, de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS. Este valor se pasa por referencia para ser "llenado" con los valores iniciales.
*/
void llenar_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);

/**
* Ubica todos los elementos presentes en el mapa en base a sus actuales ubicaciones. Se ejecuta previo a cada renderizado, de tal forma que el mapa siempre se muestre con la posicion mas actual de cada elemento.
* @pre El elemento mapa debe estar lleno de valores por defecto.
* @param mapa Arreglo de caracteres lleno de valores por defecto, de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS. Este valor se pasa por referencia para ser "llenado" con las ubicaciones de todos los elementos.
* @param juego Instancia del juego, la cual contiene las posiciones actuales de todos los elementos del mapa.
*/
void preparar_mapa_para_renderizado(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego);

/**
* Ubica un unico elemento en el mapa en base a su coordenada y representacion grafica (tipo de elemento).
* @param mapa Arreglo de caracteres lleno de valores por defecto, de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS. Este valor se pasa por referencia para ser "llenado" con las ubicaciones de todos los elementos.
* @param posicion_elemento Coordenada que contiene tanto la fila como la columna en la cual se va a ubicar el elemento actual.
* @param tipo_elemento Representacion grafica (mediante un caracter) del elemento que sera indexado en el mapa.
*/
void posicionar_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion_elemento, char tipo_elemento);

#endif
