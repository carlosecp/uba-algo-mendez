#include "sube.h"
#include <math.h>

sube_t*
sube_crear(unsigned int id, unsigned int dni, bool tiene_beneficio)
{
	sube_t* sube = malloc(sizeof(sube_t));
	if (!sube)
		return NULL;

	sube -> id = id;
	sube -> dni = dni;
	sube -> saldo = 0;
	sube -> tiene_beneficio = tiene_beneficio;

	return sube;
}

void sube_destruir(sube_t* sube);

// Si hay un error devuelve NaN
double sube_cargar_saldo(sube_t* sube, double saldo);

void
sube_consultar_saldo(sube_t* sube)
{
	return NAN;
}

// Devuelve lo que pago o NaN en caso de error
void sube_pagar_viaje(sube_t* sube, double costo, unsigned int transporte);

bool sube_habilitar(sube_t* sube);

bool sube_deshabilitar(sube_t* sube);

bool sube_transferir_saldo(sube_t* sube);
