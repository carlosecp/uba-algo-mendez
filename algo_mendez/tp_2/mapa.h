#ifndef __MAPA_H__
#define __MAPA_H__

#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "movimiento.h"

#define CANTIDAD_FILAS 20
#define CANTIDAD_COLUMNAS 30

#define EMOJI_POLAR "‍❄️"
#define EMOJI_PARDO "🐻"
#define EMOJI_PANDA "🐼"
#define EMOJI_ARBOL "🌲"
#define EMOJI_PIEDRA "🗿"
#define EMOJI_LINTERNA "🔦"
#define EMOJI_PILA "🔋"
#define EMOJI_VELA "🕯️"
#define EMOJI_BENGALA "🎇"
#define EMOJI_KOALA "🐨"
#define ESPACIO_VACIO_MAPA '.'

/* ==== COORDENADAS ==== */

/**
 * Generar una coordenada del mapa aleatoria. 
 * @pre Requiere que se haya establecido una semilla para el randomizado de las coordenadas. 
 * @param juego Instancia única del juego ya inicializada. Utilizada para comparar las coordenadas ya ocupadas en caso de que se desee.
 * @param validar_coordenada Determina si se quiere realizar algún tipo de validación para la coordenada generada (asegura que la coordenada esté vacía).
 * @param validar_coordenada_personaje Determina si se comparará la coordenada generada aleatoriamente con la coordenada del personaje (asegura que la coordenada generada no coincida con la del personaje).
 * @param validar_coordenada_amiga_chloe Determina si se comparará la coordenada generada aleatoriamente con la coordenada de Chloe (asegura que la coordenada generada no coincida con la de Chloe).
 * @return Coordenada aleatoria.
 */
coordenada_t generar_coordenada(juego_t juego, bool validar_coordenada, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe);

/**
 * Determina si la coordenada generada ya ha sido ocupada por otro elemento (en base a los elementos que se deseen validar). 
 * @pre Requiere que se haya establecido una semilla para el randomizado de las coordenadas y que se haya generado una coordenada aleatoria. 
 * @param juego Instancia única del juego ya inicializada. Utilizada para comparar las coordenadas ya ocupadas en caso de que se desee.
 * @param coordenada_buscada Coordenada aleatoria generada previamente que se desea validar.
 * @param validar_coordenada_personaje Determina si se comparará la coordenada generada aleatoriamente con la coordenada del personaje (asegura que la coordenada generada no coincida con la del personaje).
 * @param validar_coordenada_amiga_chloe Determina si se comparará la coordenada generada aleatoriamente con la coordenada de Chloe (asegura que la coordenada generada no coincida con la de Chloe).
 * @return Verdadero si la coordenada generada de manera aleatoria cumple con las validaciones indicadas.
 */
bool es_coordenada_ocupada(juego_t juego, coordenada_t coordenada_buscada, bool validar_coordenada_personaje, bool validar_coordenada_amiga_chloe);

/**
 * Compara dos coordenadas y determina si son iguales (tanto en fila como en columna). 
 * @param coordenada_a Primera coordenada a comparar con la segunda.
 * @param coordenada_b Segunda coordenada a comparar con la primera.
 * @return Verdadero si la coordenadas buscada coinciden.
 */
bool son_misma_coordenada(coordenada_t coordenada_a, coordenada_t coordenada_b);

/* ==== MAPA (BOSQUE) ==== */

/**
 * Llena el mapa (bosque) con los caracteres por defecto, que representan los espacio vacios u ocultos. 
 * @pre Se debe haber generado una matriz mapa de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS.
 * @param mapa Matriz de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS con valores sin inicializar.
 */
void inicializar_mapa_vacio(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);

/**
 * Llena el mapa (bosque) con los caracteres por defecto, que representan los espacio vacios u ocultos. 
 * @pre Se debe haber generado una matriz mapa de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS.
 * @param mapa Matriz de dimensiones CANTIDAD_FILAS * CANTIDAD_COLUMNAS con valores sin inicializar.
 */
void posicionar_todos_elementos_en_mapa(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego);

/* ===== AUXILIARES ==== */

void posicionar_personaje_en_mapa_aux(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], personaje_t personaje);

void posicionar_amiga_chloe_en_mapa_aux(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t amiga_chloe, bool amiga_chloe_es_visible);

void posicionar_elemento_del_tipo_en_mapa_aux(char mapa[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], elemento_del_mapa_t elemento_a_posicionar);

coordenada_t generar_coordenada_colision_koala();

#endif
