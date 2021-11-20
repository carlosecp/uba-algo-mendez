#include "pa2mm.h"
#include "src/hash.h"

void destruir_dato(void* elemento)
{
	return;
}

void dadoUnDestructorNULL_alCrearUnHash_seRetornaNULL()
{
	hash_t* hash = hash_crear(NULL, 3);
	pa2m_afirmar(hash==NULL, "Al crear un hash con un destructor NULL este se crea NULL");
	hash_destruir(hash);
}

void dadoUnHashNULL_alInsertarUnElemento_seRetornaError()
{
	hash_t* hash = NULL;
	pa2m_afirmar(hash_insertar(hash, "clave", NULL)==-1, "Al insertar en un hash NULl se retorna error");
	hash_destruir(hash);
}

void dadaUnaClaveNULL_alInsertarUnElemento_seRetornaError()
{
	hash_t* hash = hash_crear(destruir_dato, 3);
	pa2m_afirmar(hash_insertar(hash, NULL, NULL)==-1, "Al insertar con una clave NULL se retorna error");
	hash_destruir(hash);
}

void dadoUnHash_alInsertarUnElemento_seInsertaCorrectamente()
{
	hash_t* hash = hash_crear(destruir_dato, 3);
	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas Hash: Creacion");
	dadoUnDestructorNULL_alCrearUnHash_seRetornaNULL();
	
	pa2m_nuevo_grupo("Pruebas Hash: Insertar");
	dadoUnHashNULL_alInsertarUnElemento_seRetornaError();
	dadaUnaClaveNULL_alInsertarUnElemento_seRetornaError();

    return pa2m_mostrar_reporte();
}
