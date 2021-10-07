#include <math.h>
#include "sube.h"
#include "sube_interno.h"

sube_t*
sube_crear(unsigned id, unsigned dni, bool tiene_beneficio)
{
	sube_t* sube = malloc(sizeof(sube_t));
	if (!sube)
		return NULL;

	sube -> id = id;
	sube -> saldo = 0;
	sube -> dni = dni;
	sube -> tiene_beneficio = tiene_beneficio;

	return sube;
}

void
sube_destruir(sube_t* sube)
{
	if (sube)
		free(sube);
}

// Devuelve lo que cargo o NAN
double
sube_cargar_saldo(sube_t* sube, double saldo)
{
	if (!sube)
		return NAN;

	sube -> saldo += saldo;
	return saldo;
}

double
sube_consultar_saldo(sube_t* sube)
{
	if (!sube)
		return NAN;

	return sube -> saldo;
}

// Devuelve lo que pago o NAN
double
sube_pagar_viaje(sube_t* sube, double costo, unsigned transporte);

bool
sube_habilitar(sube_t* sube);

bool
sube_deshabilitar(sube_t* sube);

bool
sube_transferir_saldo(sube_t* sube_origen, sube_t* sube_destino, double saldo);
