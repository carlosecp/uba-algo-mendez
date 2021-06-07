#ifndef __ELEMENTOS_MAPA_H__
#define __ELEMENTOS_MAPA_H__

#include "osos_contra_reloj.h"

#define CANTIDAD_ARBOLES 350
#define CANTIDAD_PIEDRAS 80
#define ARBOL 'A'
#define PIEDRA 'R'
#define KOALAS 'K'
#define LINTERNA 'L'
#define VELA 'V'
#define BENGALA 'E'
#define PILA 'B'

/** 
 * Toma el personaje de una instancia del juego, genera y asigna sus propiedades: tipo, posicion, mochila y cantidad_elementos, ademas de establecer los valores iniciales para: elemento_en_uso, tiempo_perdido y ultimo_movimiento. La asignacion de todas estas propiedades se realiza mediante el pasaje por referencia de cada una.
 * @pre Se debe crear una instancia del juego actual y un personaje sin propiedades asignadas. Tambien se deben haber obtenido los resultados del "test de personalidad".
 * @param personaje Valor por referencia del personaje controlable por el usuario de la instancia actual del juego. 
 * @param tipo_personaje Resultados del "test de personalidad". Este valor representa al personaje en el tablero.
*/
void generar_personaje(personaje_t *personaje, char tipo_personaje);

/** 
 * Toma el vector que contiene todos los obstculos de una instancia del juego y agrega todos los obstaculos de los diferentes tipos, en sus cantidades correspondientes. 
 * @pre Se debe crear una instancia del juego actual. 
 * @param obstaculos Vector vacio en el que se guardan los obstaculos generados.
 * @param cantidad_obstaculos Cantidad inicial de obstaculos incluidos en el vector. Esta variable se pasa por referencia, ya que su valor va a ir incrementando conforme se vayan agregando nuevos obstaculos.
*/
void generar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos);

/** 
 * Genera un nuevo obstaculo generico (de un tipo especifico) con valores por defecto: posicion valida, tipo indicado y no visible en primera instancia.
 * @param tipo_obstaculo Representacion grafica (caracter) que representa el elemento en el mapa.
 * @return Nuevo obstaculo oculto.
*/
elemento_del_mapa_t generar_nuevo_obstaculo(char tipo_obstaculo);

#endif