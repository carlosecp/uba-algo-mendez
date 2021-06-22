#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "estadisticas.h"

/* ==== CANALES DE TELEVISION ==== */
#define ANIME 'A'
#define POP 'M'
#define LIMPIEZA 'L'

/* ==== TIPOS DE ALIMENTO ==== */
#define BAMBU 'B'
#define PESCADO 'P'
#define FOCAS 'F'

/* ==== MULTIPLICADORES DE PUNTAJE ==== */
#define PTS_LIMPIEZA 1
#define PTS_ANIME 2
#define PTS_POP 3
#define PTS_FOCAS 3
#define PTS_BAMBU 6
#define PTS_PESCADO 9

/* ==== MAXIMOS Y MINIMOS DE INTERVALOS ==== */
#define MAX_PISOS_TORRE 18
#define MIN_PISOS_TORRE 1
#define MAX_NIVEL_GRITO 18
#define MIN_NIVEL_GRITO 1

/* ==== INTERVALOS RESULTADOS ==== */
#define MIN_PUNTAJE 5
#define MAX_POLAR 24
#define MAX_PANDA 43
#define MAX_PARDO 63

/* ==== LIMITE MINISCULA Y MAYUSCULA ==== */
#define MIN_MINUSCULA 'a'
#define MAX_MINUSCULA 'z'

/** 
 * Determina si el canal de televisión ingresado es válido (Ánime, Pop o Limpieza).
 * @param letra_ingresada Canal de televisión ingresado por el usuario. Debe ser un caracter ASCII válido.
 * @return Verdadero si el canal de televisión ingresado es válido.
*/
bool es_canal_tv_valido(char letra_ingresada);

/** 
 * Determina si el tipo de alimento ingresado es válido (Focas, Bambú o Pescado).
 * @param letra_ingresada Tipo de alimento ingresado por el usuario. Debe ser un caracter ASCII válido.
 * @return Verdadero si el tipo de alimento ingresado es válido.
*/
bool es_alimento_valido(char alimento_ingresado);

/** 
 * Determina si un número ingresado por el usuario cabe dentro de un intervalo numérico determinado.
 * @param cota_inferior Número real que representa el mínimo valor permitido en el intervalo (incluyente).
 * @param cota_superior Número real que representa el máximo valor permitido en el intervalo (incluyente).
 * @param valor_a_evaluar Número ingresado por el usuario.
 * @return Verdadero número ingresado cabe dentro del intervalo numérico especificado.
*/
bool esta_incluido_en_intervalo(int cota_inferior, int cota_superior, int valor_a_evaluar);

/** 
 * Determina si el nivel de grito ingresado por el usuario es válido.
 * @param nivel_grito Nivel de grito ingresado por el usuario.
 * @return Verdadero si el nivel de grito ingresado por el usuario es válido.
*/
bool es_nivel_grito_valido(int nivel_grito);

/** 
 * Determina si el piso de la torre ingresado por el usuario es válido.
 * @param nivel_grito Piso de la torre ingresado por el usuario.
 * @return Verdadero si el piso de la torre ingresado por el usuario es válido.
*/
bool es_piso_torre_valido(int piso_torre);

/** 
 * Determina si la letra ingresada por el usuario es minúscula.
 * @param letra_evaluada Letra ingresada por el usuario. Debe ser un caracter ASCII válido.
 * @return Verdadero si el caracter evaluado es minúscula.
*/
bool es_letra_minuscula(char letra_evaluada);

/** 
 * Calcula el puntaje correcto según el canal de televisión ingresado.
 * @param canal_ingresado Recibe un caracter que corresponda a alguna de las opciones válidas de canales de televisión 'A', 'M' o 'L' (case sensitive).
 * @return Retorna el puntaje correcto según el canal de televisión ingresado.
*/
int calcular_puntaje_segun_canal_tv(char canal_ingresado);

/** 
 * Calcula el puntaje correcto según el tipo de alimento ingresado.
 * @param alimento_ingresado Recibe un caracter que corresponda a alguna de las opciones válidas de tipos de alimentos 'B', 'P' o 'F' (case sensitive).
 * @return Retorna el puntaje correcto según el tipo de alimento ingresado.
*/
int calcular_puntaje_segun_alimento(char alimento_ingresado);

/**
 * Calcula el puntaje total del test de personalidad.
 * @param pts_segun_alimento Recibe el punta según el tipo de alimento ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @param pts_segun_canal_tv Recibe el punta según el canal de televisión ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @param pts_nivel_grito Recibe el punta según el nivel de grito ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @param pts_piso_torre Recibe el punta según el piso de la torre ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @return Puntaje total del test de personalidad.
*/
int calcular_puntaje_total(int pts_segun_alimento, int pts_segun_canal_tv, int pts_nivel_grito, int pts_piso_torre);

/** 
 * Realiza la pregunta sobre el tipo de alimento preferido para el usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al tipo de alimento preferido para el usuario.
*/
int resultados_alimento();

/** 
 * Realiza la pregunta sobre el canal de televisión preferido para el usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al canal de televisión preferido para el usuario.
*/
int resultados_canal_tv();

/** 
 * Realiza la pregunta sobre el nivel de grito del usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al nivel de grito del usuario.
*/
int resultados_nivel_grito();

/** 
 * Realiza la pregunta sobre el piso de la torre preferido para el usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al piso de la torre preferido para el usuario.
*/
int resultados_piso_torre();

/** 
 * Determina la personalidad del pesronaje del usuario en base a las preguntas respondidas.
 * @pre Deben haberse calculado los resultados individuales de cada pregunta del test de personalidad.
 * @param pts_totales Puntaje final del test de personalidad, calculado utilizando la fórmula especificada.
 * @return Letra que representa la personalidad que se le ha asignado al personaje del usuario.
*/
char asignar_personalidad(int pts_totales);

/** 
 * Inicializa la encuesta del test de personalidad.
 * @return Letra que representa la personalidad que se le ha asignado al personaje del usuario.
*/
char test_de_personalidad();