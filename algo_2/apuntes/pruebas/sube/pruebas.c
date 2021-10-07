#include "pa2mm.h"
#include "sube.h"
#include "sube_interno.h"

/*
   void condicionesIniciales_accionQueIniciaLaPrueba_resultadoEsperado() {
   		- Fase de creacion: Se crean los valores necesarios para
		correr la prueba.

		- Fase de afirmacion: Se evaluan los valores arrojados por
		la prueba con los valores esperados.

		- Fase de destruccion: Se retorna al estado previo a la prueba.
   }
*/

// Pruebas de creacion
void
alCrearUnaNuevaSube_seCrearCorrectamente()
{
	sube_t* sube = sube_crear(0, 0, false);

	pa2m_afirmar(sube != NULL, "La sube se crea");
	pa2m_afirmar(sube_consultar_saldo(sube) == 0, "La sube se crea con saldo 0");

	// Ahora vamos a utilizar funciones custom solamente para pruebas

	sube_destruir(sube);
}

// Pruebas de saldo
void
dadoUnSaldoPositivo_alCargarSaldo_elSaldoAumenta()
{
	sube_t* sube = sube_crear(0, 0, true);

	pa2m_afirmar(sube_cargar_saldo(sube, 100) == 100, "Se le cargan 100 pesos a la sube");
	pa2m_afirmar(sube_consultar_saldo(sube) == 100, "La sube tiene 100 pesos de saldo");

	sube_destruir(sube);
}

int
main()
{
	pa2m_nuevo_grupo("Pruebas de creacion");
	alCrearUnaNuevaSube_seCrearCorrectamente();

	pa2m_nuevo_grupo("Pruebas de saldo");
	dadoUnSaldoPositivo_alCargarSaldo_elSaldoAumenta();

	return 0;
}
