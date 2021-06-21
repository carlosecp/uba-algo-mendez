#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "estadisticas.h"

/* ==== PERSONAJES (RESULTADOS DEL TEST) ==== */
#define POLAR 'I'
#define PANDA 'P'
#define PARDO 'G'

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

bool es_canal_tv_valido(char letra_ingresada);

bool es_alimento_valido(char alimento_ingresado);

bool esta_incluido_en_intervalo(int cota_inferior, int cota_superior, int valor_a_evaluar);

bool es_nivel_grito_valido(int nivel_grito);

bool es_piso_torre_valido(int piso_torre);

bool es_letra_minuscula(char letra_evaluada);

int calcular_puntaje_segun_canal_tv(char canal_ingresado);

int calcular_puntaje_segun_alimento(char alimento_ingresado);

int calcular_puntaje_total(int pts_segun_alimento, int pts_segun_canal_tv, int pts_nivel_grito, int pts_piso_torre);

int resultados_alimento();

int resultados_canal_tv();

int resultados_nivel_grito();

int resultados_piso_torre();

char asignar_personalidad(int pts_totales);

char test_de_personalidad();