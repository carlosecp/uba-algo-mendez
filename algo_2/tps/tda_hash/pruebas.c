#include "pa2mm.h"
#include "src/hash.h"

void hash_destruir_dato(void* elemento)
{
	return;
}

void dadoUnDestructorYUnaCapacidadInicial_alCrearUnHash_seCreaYDestruyeCorrectamente()
{
	hash_t* hash = hash_crear(hash_destruir_dato, 10);

	pa2m_afirmar(hash_cantidad(hash)==10, "Al crear un hash con una cantidad "
			"inicial mayor a 3, la cantidad inicial del hash es la "
			"especificada");

	hash_destruir(hash);
}

void dadoUnaCapacidadInicialMenorA3_alCrearUnHash_suCapacidadInicialEs3()
{
	hash_t* hash = hash_crear(hash_destruir_dato, 2);

	pa2m_afirmar(hash_cantidad(hash)==3, "Al crear un hash con una cantidad "
			"inicial menor a 3, la cantidad inicial del hash es 3");

	hash_destruir(hash);
}

int main()
{
	dadoUnDestructorYUnaCapacidadInicial_alCrearUnHash_seCreaYDestruyeCorrectamente();
	dadoUnaCapacidadInicialMenorA3_alCrearUnHash_suCapacidadInicialEs3();
    return pa2m_mostrar_reporte();
}
