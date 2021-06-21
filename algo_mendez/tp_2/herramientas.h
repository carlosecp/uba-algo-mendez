#ifndef __HERRAMIENTAS_H__
#define __HERRAMIENTAS_H__

#include "inicializar_elementos.h"

#define NINGUNA_HERRAMIENTA_EN_USO -1
#define TECLA_ENCENDER_LINTERNA LINTERNA
#define TECLA_ENCENDER_VELA VELA
#define TECLA_ENCENDER_BENGALA BENGALA

/* ==== UTILIZACIÓN DE HERRAMIENTAS ===== */

/**
 * Evalua la herramienta que el jugador desea activar/desactivar. 
 * @pre Requiere que se haya inicializado el personaje y este haya hecho algún movimiento previo si se quiere utilizar la linterna. 
 * @param juego Referencia a la instancia única del juego ya inicializada. 
 * @param jugada Herramienta que se desea activar/desactivar.
 */
void jugada_utilizar_herramienta(juego_t *juego, char jugada);

/**
 * Determina si la herramienta que se desea utilizar existe. 
 * @pre Requiere que se haya inicializado el personaje. 
 * @param jugada Herramienta que se desea activar/desactivar.
 */
bool es_herramienta_valida(char jugada);

/**
 * Determina si la herramienta que se desea utilizar tiene movimientos restantes. 
 * @pre Requiere que se haya inicializado el personaje. 
 * @param personaje Instancia única del personaje. Utilizada para verificar si la herramienta que se desea utilizar puede ser activada.
 */
bool herramienta_se_puede_usar(personaje_t personaje);

/**
 * Consume un uno de la herramienta que se está activando. También evalúa el tipo de herramienta deseado y asigna una respuesta (tipo de iluminación) acorde a este tipo de herramienta (Linterna, Vela, Bengala). 
 * @pre Requiere que se haya inicializado el personaje y que se haya decido activar una herramienta válida y utilizable. 
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para determinar la herramienta en uso del personaje e iluminar las casillas del juego que caen en el rango de la herramienta que se está activando.
 * @param tipo_herramienta Tipo de herramienta que se va a activar.
 */
void utilizar_herramienta(juego_t *juego, char tipo_herramienta);

/**
 * Continúa la utilización de la herramienta que se estaba utilizando en el turno anterior (si hay turnos disponibles todavía). 
 * @pre Requiere que se haya realizado un movimiento previo y que el personaje haya tenido una herramienta encendida en ese movimiento. 
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para determinar la herramienta en uso del personaje e iluminar las casillas del juego que caen en el rango de la herramienta que se está activando (a través de utilizar_herramienta).
 */
void utilizar_misma_herramienta(juego_t *juego);

/**
 * Ubica la primera herramienta disponible del tipo buscado dentro de la mochila. 
 * @pre Requiere que se haya inicializado el personaje y que se haya decido activar una herramienta válida y utilizable. 
 * @param personaje Instancia única del personaje. Utilizada para buscar la herramienta deseada dentro de la mochila del personaje.
 * @param tipo_herramienta Tipo de herramienta que se va a buscar dentro de la mochila para ser activada.
 * @return Indice de la primera herramienta del tipo encontrada dentro de la mochila del personaje.
 */
int buscar_herramienta_en_mochila(personaje_t personaje, char tipo_herramienta);

/**
 * Determina si se puede descartar una herramienta cuyos usos ya hayan sido totalmente consumidos y no pueda ser recargada (Vela y Bengala).
 * @pre Requiere que se haya inicializado el personaje y que hayan consumido todos los usos de una herramienta eliminable. 
 * @param personaje Instancia única del personaje. Utilizada para buscar la herramienta gastada dentro de la mochila del personaje.
 * @return Verdadero si se encuentra una herramienta sin movimientos en la mochila del personaje.
 */
bool herramienta_se_puede_eliminar(personaje_t personaje);

/**
 * Descarta una herramienta cuyos usos ya hayan sido totalmente consumidos y no pueda ser recargada (Vela y Bengala).
 * @pre Requiere que se haya inicializado el personaje y que hayan consumido todos los usos de una herramienta eliminable. 
 * @param personaje Referencia a la instancia única personaje. Utilizada eliminar una herramienta sin movimientos dentro de la mochila del personaje.
 */
void eliminar_herramienta_de_mochila(personaje_t *personaje);

/**
 * Determina si una herramienta ya no dispone de movimientos. 
 * @pre Requiere que se haya inicializado el personaje y que hayan consumido todos los usos de una herramienta. 
 * @param personaje Instancia única del personaje. Utilizada para buscar la herramienta gastada dentro de la mochila del personaje.
 * @return Verdadero si la una herramienta aún tiene movimientos disponibles.
 */
bool herramienta_tiene_movimientos(personaje_t personaje);

/* ==== LINTERNA ==== */

/**
 * Determina si una herramienta ya no dispone de movimientos. 
 * @pre Requiere que se haya inicializado el personaje y que hayan consumido todos los usos de una herramienta. 
 * @param personaje Instancia única del personaje. Utilizada para buscar la herramienta gastada dentro de la mochila del personaje.
 * @return Verdadero si la una herramienta aún tiene movimientos disponibles.
 */
void utilizar_linterna(juego_t *juego, bool iluminar);

void iluminar_fila(juego_t *juego, bool revertir_direccion, bool iluminar);

void iluminar_columna(juego_t *juego, bool revertir_direccion, bool iluminar);

bool linterna_fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

bool linterna_columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento, bool revertir_direccion);

/* ==== VELA ==== */

void utilizar_vela(juego_t *juego, bool iluminar);

bool vela_area_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento);

bool vela_fila_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento);

bool vela_columna_es_iluminable(coordenada_t posicion_personaje, coordenada_t posicion_elemento);

/* ==== BENGALA ==== */

void utilizar_bengala(juego_t *juego, bool ilumnar);

bool esta_a_distancia_manhattan(coordenada_t posicion_centro, coordenada_t posicion_elemento);

#endif