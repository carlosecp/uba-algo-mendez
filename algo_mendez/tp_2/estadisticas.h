#ifndef __ESTADISTICAS_H__
#define __ESTADISTICAS_H__

#include "osos_contra_reloj.h"
#include "utiles.h"
#include "herramientas.h"

#define TIEMPO_LIMITE 120

/**
 * Renderiza la pantalla de bienvenida y la historia inicial.
 */
void renderizar_introduccion();

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Requiere que se haya inicializado el juego. 
 * @param juego Instancia única del juego ya inicializada.
 */
void renderizar_estadisticas(juego_t juego);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_tiempo_elapsado(personaje_t personaje);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_ultimo_movimiento(char ultimo_movimiento);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_mochila(personaje_t personaje);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_gps(juego_t juego);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void finalizar_juego(juego_t juego);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_bordes_mapa(bool border_superior);

/**
 * Muestra la información mas actual del estado del juego, como el tiempo transcurrido, el tiempo perdido, elementos en la mochila e información adicional del personaje.
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_bordes_estadisticas();

#endif