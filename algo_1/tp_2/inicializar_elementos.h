#ifndef __INICIALIZAR_ELEMENTOS_H__
#define __INICIALIZAR_ELEMENTOS_H__

#include "osos_contra_reloj.h"
#include "mapa.h"
#include "herramientas.h"

/* ==== PERSONAJES ==== */
#define POLAR 'I'
#define PARDO 'G'
#define PANDA 'P'
#define CHLOE 'C'
#define KOALA 'K'

/* ==== ELEMENTOS DEL MAPA ==== */
#define ARBOL 'A'
#define PIEDRA 'R'
#define LINTERNA 'L'
#define VELA 'V'
#define BENGALA 'E'
#define PILA 'B'

#define DURACION_LINTERNA 10
#define DURACION_LINTERNA_PARDO 15
#define DURACION_PILA 5
#define DURACION_VELA 5
#define DURACION_BENGALA 3

#define CANTIDAD_LINTERNAS_MOCHILA 1
#define CANTIDAD_VELAS_MOCHILA 4
#define CANTIDAD_VELAS_POLAR 6
#define CANTIDAD_BENGALAS_MOCHILA 0
#define CANTIDAD_BENGALAS_PANDA 2

#define CANTIDAD_ARBOLES 350
#define CANTIDAD_PIEDRAS 80
#define CANTIDAD_PILAS_MAPA 30
#define CANTIDAD_VELAS_MAPA 30
#define CANTIDAD_BENGALAS_MAPA 10

/* ==== PERSONAJE ==== */

/**
 * Inicializa el personaje del juego, asignándole tipo, posición inicial, llenando su mochila e inicializando su tiempo perdido. 
 * @pre Requiere que se haya inicializado el juego y que se haya determinado el tipo de personaje (resultado del test de personalidad). 
 * @param juego Instancia única del juego ya inicializada.
 * @param tipo_personaje Resultado del test de personalidad.
 */
personaje_t inicializar_personaje(juego_t juego, char tipo_personaje);

/* ==== MOCHILA ==== */

/**
 * Genera un elemento mochila para el personaje. 
 * @pre Requiere que se haya creado el personaje y que este tenga una mochila vacía. 
 * @param mochila Referencia al elemento mochila del personaje.
 * @param tipo_personaje Resultado del test de personalidad. Utilizado para determinar las cantidades iniciales de cada herramienta para cada personaje.
 */
int generar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], char tipo_personaje);

/**
 * Agrega X cantidad de elementos de un tipo especifico a la mochila del personaje. 
 * @pre Requiere que se haya creado el personaje y que este tenga una mochila. 
 * @param tipo_herramienta Tipo de herramienta que se quiere agregar (Linterna, Vela, Bengala).
 * @param cantidad_herramientas_del_tipo Cantidad de herramientas del tipo a agregar.
 * @param mochila Referencia al elemento mochila del personaje.
 * @param tope_mochila Referencia a la cantidad de elementos presentes en la mochila del personaje.
 * @param tipo_personaje Resultado del test de personalidad.
 */
void agregar_multiples_herramientas_del_tipo_a_mochila(char tipo_herramienta, int cantidad_herramientas_del_tipo, elemento_mochila_t mochila[MAX_HERRAMIENTAS], int *tope_mochila, char tipo_personaje);

/**
 * Genera una única herramienta específica para la mochila del personaje. 
 * @pre Requiere que se haya creado el personaje y que este tenga una mochila. 
 * @param tipo_herramienta Tipo de herramienta que se quiere agregar (Linterna, Vela, Bengala).
 * @param tipo_personaje Resultado del test de personalidad. Utilizado para determinar las propiedades de cada tipo de herramienta.
 * @return Elemento de la mochila con valores específicos según el personaje.
 */
elemento_mochila_t generar_una_herramienta_mochila(char tipo_herramienta, char tipo_personaje);

/* ==== AMIGA CHLOE ==== */

/**
 * Genera la posición de Chloe (diferente a la posición del personaje).
 * @pre Requiere que se haya generado la coordenada del personaje. 
 * @param juego Referencia a la instancia única del juego ya inicializada. Utilizada para determinar cuales coordenadas ya han sido ocupadas por otros elementos y para ocultar a Chloe cuando comienza el juego.
 * @return Coordenada generada para Chloe.
 */
coordenada_t inicializar_amiga_chloe(juego_t *juego);

/* ==== OBSTACULOS ==== */

/**
 * Agrega la cantidad específica de obstáculos de todos los tipos al mapa.
 * @pre Requiere que se hayan generado la coordenada del personaje y la coordenada de Chloe. 
 * @param juego Referencia a la instancia única del juego ya inicializada. 
 */
void inicializar_obstaculos(juego_t *juego);

/**
 * Agrega un único Koala Nom Nom al mapa.
 * @pre Requiere que se hayan generado la coordenada del personaje, la coordenada de Chloe, y las coordenadas de los obstáculos y herramientas iniciales. 
 * @param juego Referencia a la instancia única del juego ya inicializada. 
 */
void agregar_koala_nom_nom(juego_t *juego);

/* ==== HERRAMIENTAS ==== */

/**
 * Agrega la cantidad específica de herramientas (recolectables) de todos los tipos al mapa.
 * @pre Requiere que se hayan generado la coordenada del personaje, la coordenada de Chloe y las coordenadas de los obstáculos iniciales.
 * @param juego Referencia a la instancia única del juego ya inicializada. 
 */
void inicializar_herramientas(juego_t *juego);

/**
 * Agrega cualquier obstáculo o herramienta al mapa.
 * @pre Requiere que se hayan generado la coordenada del personaje, la coordenada de Chloe y las coordenadas de los obstáculos iniciales.
 * @param juego Instancia única del juego ya inicializada. 
 * @param tipo_elemento Tipo de elemento que se quiere agregar. 
 * @return Elemento del tipo específico con coordenada válida. 
 */
elemento_del_mapa_t agregar_elemento_del_tipo(juego_t juego, char tipo_elemento);

/* ==== AUXILIARES ==== */

coordenada_t generar_coordenada_personaje_aux(juego_t juego);
coordenada_t generar_coordenada_amiga_chloe_aux(juego_t juego);
coordenada_t generar_coordenada_elemento_aux(juego_t juego);

#endif
