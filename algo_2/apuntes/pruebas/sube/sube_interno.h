#ifndef SUBE_INTERNO_H_
#define SUBE_INTERNO_H_

/*
Aca copio del las cosas a las que generalmente no voy a poder
acceder desde mi archivo de pruebas original, en este caso ambas
structs porque van a ser privadas.
*/

#include <stdbool.h>
#define CANTIDAD_MAXIMA_VIAJES 10

typedef struct {
	double costo;
	unsigned long timestamp;
	unsigned transporte;
} viaje_t;

typedef struct {
	unsigned id;
	double saldo;
	unsigned dni;
	bool tiene_beneficio;
	viaje_t viajes[CANTIDAD_MAXIMA_VIAJES];
} sube_t;

// Defino mis funciones de prueba.
bool saldo_alcanza_para_viaje(sube_t* sube, double saldo, viaje_t viaje);

#endif
