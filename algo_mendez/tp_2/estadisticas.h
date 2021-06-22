#ifndef __ESTADISTICAS_H__
#define __ESTADISTICAS_H__

#include "osos_contra_reloj.h"
#include "utiles.h"
#include "herramientas.h"

#define EMOJI_POLAR "‍❄️"
#define EMOJI_PARDO "🐻"
#define EMOJI_PANDA "🐼"
#define EMOJI_CHLOE "👧"
#define EMOJI_ARBOL "🌲"
#define EMOJI_PIEDRA "🗿"
#define EMOJI_LINTERNA "🔦"
#define EMOJI_PILA "🔋"
#define EMOJI_VELA "🕯️"
#define EMOJI_BENGALA "🎇"
#define EMOJI_KOALA "🐨"

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
 * Muestra el resultado del test de personalidad. Resultado que representa al personaje del juego.
 * @pre Requiere que se haya completado el test de personalidad. 
 * @param tipo_personaje Caracter que representa el resultado del test de personalidad.
 */
void renderizar_resultado_test_de_personalidad(char tipo_personaje);

/**
 * Muestra el tiempo transcurrido desde que se inicio el juego y el tiempo perdido acumulado por el personaje. 
 * @pre Se debe haber inicializado el cronómetro al empezar el juego. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual además del tiempo perdido por este.
 */
void renderizar_tiempo_elapsado(personaje_t personaje);

/**
 * Utiliza la habilidad especial de GPS para mostrar las coordenadas de Chloe. 
 * @pre El personaje debe poder utilizar la habilidad de GPS y se deben haber acumulado por lo menos 30 segundos de tiempo perdido por el personaje. 
 * @param personaje Instancia única del personaje, utilizada para determinar si este ha solicitado visualizar el tiempo actual. 
 */
void renderizar_gps(juego_t juego);

/**
 * Muestra cual ha sido el último movimiento del personaje (Arriba, Abajo, Derecha, Izquierda). También indica al jugador si se está intentando hacer un movimiento inválido.
 * @pre Requiere que se haya inicializado el juego. 
 * @param ultimo_movimiento Ultimo movimiento realizado por el personaje. 
 */
void renderizar_ultimo_movimiento(char ultimo_movimiento);

/**
 * Muestra los elementos incluídos actualmente en la mochila del personaje, así como los movimientos restantes de cada una y la herramienta que está actualmente en uso. 
 * @pre Se debe haber inicializado el cronómetro al empezar el juego y llenado la mochila. 
 * @param personaje Instancia única del personaje, utilizada mostrar los elementos de su mochila, sus datos correspondientes y la herramienta que esta siendo utilizada en el momemento. 
 */
void renderizar_mochila(personaje_t personaje);

/** 
 * Asigna el emoji a mostrar en el mapa en base al tipo de elemento de cada casilla.
*/
void renderizar_emoji_en_mapa(char tipo_elemento);

/**
 * Renderizar bordes totalmente rectos de manera horizontal, con dimensiones iguales a las dimensiones del mapa. 
 */
void renderizar_bordes_estadisticas();

/**
 * Renderiza bordes horizontales con las mismas dimensiones del mapa. Las esquinas de estos bordes pueden estar orientadas hacia arriba o abajo, en dependencia de si se quiere un borde para la parte superior o inferior del mapa. 
 * @param borde_superior Determina si se quiere un borde para la parte superior o inferior del mapa.
 */
void renderizar_bordes_mapa(bool borde_superior);

/**
 * Dictamina el resultado del juego en base al tiempo total.
 * @pre Se debe haber finalizado el juego. 
 * @param juego Instancia única del juego, utilizada para realizar el cálculo del resultado. 
 */
void renderizar_resultados_juego(juego_t juego);

#endif