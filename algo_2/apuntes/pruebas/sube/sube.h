#ifndef SUBE_H_
#define SUBE_H_

/*
Definimos todo lo que vamos a utilizar en las pruebas
en el archivo interno, si vamos a ocupar esas cosas de 
manera publica, tambien lo ponemos aca. 
*/

// Esto es solo temporalmente
#include "sube_interno.h"

#include <stdlib.h>
#include <stdbool.h>

sube_t* sube_crear(unsigned id, unsigned dni, bool tiene_beneficio);

void sube_destruir(sube_t* sube);

// Devuelve lo que cargo o NAN
double sube_cargar_saldo(sube_t* sube, double saldo);

double sube_consultar_saldo(sube_t* sube);

// Devuelve lo que pago o NAN
double sube_pagar_viaje(sube_t* sube, double costo, unsigned transporte);

bool sube_habilitar(sube_t* sube);

bool sube_deshabilitar(sube_t* sube);

bool sube_transferir_saldo(sube_t* sube_origen, sube_t* sube_destino, double saldo);

#endif
