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
 * Inicializa la encuesta del test de personalidad.
 * @return Letra que representa la personalidad que se le ha asignado al personaje del usuario.
*/
void test_de_personalidad(char *personalidad_detectada);