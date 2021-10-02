#include "sube.h"

void
alCrearUnaSube_seCreaExitosamente()
{
	sube_t* sube = sube_crear(0, 0, false);

	// pa2m_afirmar(sube != NULL, "La sube se crea");
	// pa2m_afirmar(sube_consultar_saldo(sube) == 0.0, "La sube se crea sin saldo");

	sube_destruir(sube);
}
