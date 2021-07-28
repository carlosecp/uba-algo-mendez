#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VECTOR 100

void imprimir_vector(int vector[], int tope);

void cargar_vector(int vector[], int *tope, int argc, char *argv[]);

#endif