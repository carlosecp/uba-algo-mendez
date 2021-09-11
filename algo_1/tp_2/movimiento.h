#ifndef __MOVIMIENTO_H__
#define __MOVIMIENTO_H__

#include <string.h>
#include "osos_contra_reloj.h"
#include "inicializar_elementos.h"
#include "mapa.h"

#define MOVIMIENTO_INVALIDO 'X'
#define TECLA_MOVER_ARRIBA 'W'
#define TECLA_MOVER_ABAJO 'S'
#define TECLA_MOVER_DERECHA 'D'
#define TECLA_MOVER_IZQUIERDA 'A'
#define TECLA_VER_TIEMPO_RESTANTE 'T'

#define TIEMPO_PERDIDO_ARBOL 1
#define TIEMPO_PERDIDO_ARBOL_PARDO 0.5
#define TIEMPO_PERDIDO_PIEDRA 2
#define TIEMPO_PERDIDO_PIEDRA_POLAR 0
#define TIEMPO_PERDIDO_ACTIVAR_GPS 30

static const coordenada_t MOVER_PERSONAJE_ARRIBA = {.fil = -1, .col = 0};
static const coordenada_t MOVER_PERSONAJE_ABAJO = {.fil = 1, .col = 0};
static const coordenada_t MOVER_PERSONAJE_DERECHA = {.fil = 0, .col = 1};
static const coordenada_t MOVER_PERSONAJE_IZQUIERDA = {.fil = 0, .col = -1};

/* ==== DESPLAZAMIENTO ===== */

/**
 * Evalua el movimiento que el jugador desea hacer. 
 * @pre Requiere que se haya inicializado el personaje. 
 * @param juego Referencia a la instancia única del juego ya inicializada. 
 * @param jugada Movimiento que se desea que el personaje realice.
 */
void jugada_movimiento(juego_t *juego, char jugada);

/**
 * Evalua el movimiento que el jugador desea hacer. 
 * @pre Requiere que se haya inicializado el personaje. 
 * @param coordenada_actual Referencia a la coordenada actual el personaje (antes de realizar el movimiento). 
 * @param jugada Incremento en las coordenadas del personaje según la dirección de movimiento (MOVER_PERSONAJE_ARRIBA, MOVER_PERSONAJE_ABAJO, MOVER_PERSONAJE_DERECHA, MOVER_PERSONAJE_IZQUIERDA).
 */
void mover_personaje(coordenada_t *coordenada_actual, coordenada_t direccion_movimiento);

/**
 * Determina si la coordenada buscada está dentro de los límites del mapa o no. 
 * @param coordenada_buscada Coordenada que se quiere comprobar. 
 * @return Verdadero si la coordenada buscada está dentro de los límites del mapa.
 */
bool coordenada_esta_en_el_mapa(coordenada_t coordenada_buscada);

/* ==== COLISIONES ==== */

/**
 * Dictamina si el personaje está en colisión con algún elemento del mapa y asigna una acción según el tipo de elemento con el que se está colisionando.
 * @pre Tanto obstáculos como herramientas recolectables deben estar ubicadas en el mapa.
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para comparar las coordenadas de todos los elementos del mapa.
 */
void manejar_colision(juego_t *juego);

/**
 * Evalúa la acción a realizar si se ha colisionado con un obstáculo de cualquier tipo (Ej.: Tiempo perdido que se debe añadir al jugador).
 * @param juego Referencia a la instancia única del juego.
 * @param tipo_obstaculo Tipo de obstáculo con el que se ha detectado la colisión.
 */
void accion_colision_con_obstaculo(juego_t *juego, char tipo_obstaculo);

/* ==== RECOLECCIÓN DE HERRAMIENTAS ==== */

/**
 * Evalúa la acción a realizar si se ha colisionado con una herramienta de cualquier tipo (recolectable).
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para determinar el tipo de herramienta que se encuentra en la ubicación del personaje.
 * @param indice_herramienta Ubicación en el vector de obstáculos del mapa en el que se encuentra el recolectable actual.
 */
void accion_colision_con_herramienta(juego_t *juego, int indice_herramienta);

/**
 * Si se puede, agrega la herramienta recolectable encontrada en el mapa a la mochila del personaje.
 * @pre Se debe haber inicializado un personaje con mochila y tope específico.
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para determinar si se pueden agregar herramientas a la mochila del personaje, y si se puede, agregarlas.
 * @param tipo_herramienta Ubicación en el vector de obstáculos del mapa en el que se encuentra el recolectable actual.
 */
void agregar_herramienta_a_mochila(personaje_t *personaje, char tipo_herramienta);

/**
 * Si el personaje ha recolectado una herramienta del mapa, esta se elimina del mismo.
 * @pre Se debe haber encontrado una herramienta recolectable y haber agregado esta herramienta a la mochila del personaje.
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para eliminar la herramienta recogida del registro.
 * @param indice_herramienta Ubicación en el vector de obstáculos del mapa en el que se encuentra el recolectable actual.
 */
void remover_herramienta_del_mapa(juego_t *juego, int indice_herramienta);

/**
 * Si se puede (alcanzan nuevas pilas), agrega pilas a la linterna del personaje.
 * @pre Se debe haber inicializado un personaje con linterna en su mochila.
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada remover la herramienta recolectable pila del mapa si se ha agregado a la linterna del personaje.
 */
void agregar_pilas_a_linterna(juego_t *juego, int indice_pila);

#endif