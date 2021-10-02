#ifndef SUBA_H__
#define SUBA_H__

#include <stdlib.h>
#include <stdbool.h>

#define MAXIMO_VIAJES 10

typedef struct viaje {
	double costo;
	unsigned long fecha;
	unsigned int transporte;
} viaje_t;

typedef struct sube {
	unsigned int id;
	double saldo;
	unsigned int dni;
	bool tiene_beneficio;
	viaje_t viajes[MAXIMO_VIAJES];
} sube_t;

sube_t* sube_crear(unsigned int id, unsigned int dni, bool tiene_beneficio);

void sube_destruir(sube_t* sube);

// Si hay un error devuelve NaN
double sube_cargar_saldo(sube_t* sube, double saldo);

double sube_consultar_saldo(sube_t* sube);

// Devuelve lo que pago o NaN en caso de error
void sube_pagar_viaje(sube_t* sube, double costo, unsigned int transporte);

bool sube_habilitar(sube_t* sube);

bool sube_deshabilitar(sube_t* sube);

bool sube_transferir_saldo(sube_t* sube);

#endif
