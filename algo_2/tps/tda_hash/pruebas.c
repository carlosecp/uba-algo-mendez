#include "pa2mm.h"
#include "src/hash.h"
#include "./src/casilla.h"

struct hash {
	casilla_t** casillas;
	size_t cantidad_casillas;
	size_t cantidad_elementos;
	hash_destruir_dato_t destruir_elemento;
};

void destruir_dato(void* elemento) {
	return;
}

void imprimir_casilla(casilla_t* casilla) {
	if (!casilla)
		return;

	printf(" %s ", (char*)(casilla->elemento));
	imprimir_casilla(casilla -> siguiente);
}

void imprimir_hash(hash_t* hash) {
	for (size_t i = 0; i < hash->cantidad_casillas; i++) {
		if (hash->casillas[i] == NULL) {
			printf("\t%li\t---\n", i);
		} else {
			printf("\t%li\t", i);
			imprimir_casilla(hash->casillas[i]);
			printf("\n");
		}
	}
}

void dadoUnDestructorNULL_alCrearUnHash_seRetornaNULL() {
	hash_t* hash = hash_crear(NULL, 3);
	pa2m_afirmar(hash==NULL, "Al crear un hash con un destructor NULL este se crea NULL");
	hash_destruir(hash);
}

void dadoUnHashNULL_alInsertarUnElemento_seRetornaError() {
	hash_t* hash = NULL;
	pa2m_afirmar(hash_insertar(hash, "clave", NULL)==-1, "Al insertar en un hash NULl se retorna error");
	hash_destruir(hash);
}

void dadaUnaClaveNULL_alInsertarUnElemento_seRetornaError() {
	hash_t* hash = hash_crear(destruir_dato, 3);
	pa2m_afirmar(hash_insertar(hash, NULL, NULL)==-1, "Al insertar con una clave NULL se retorna error");
	hash_destruir(hash);
}

void dadoUnHash_alInsertarUnElemento_seInsertaCorrectamente() {
	hash_t* hash = hash_crear(destruir_dato, 10);

	char e0[] = "elemento1";
	char e1[] = "elemento2";
	char e2[] = "elemento3";

	hash_insertar(hash, "a", e0);
	hash_insertar(hash, "dd", e1);
	hash_insertar(hash, "carlos", e2);

	imprimir_hash(hash);

	hash_destruir(hash);
}

int main() {
	pa2m_nuevo_grupo("Pruebas Hash: Creacion");
	dadoUnDestructorNULL_alCrearUnHash_seRetornaNULL();
	
	pa2m_nuevo_grupo("Pruebas Hash: Insertar");
	dadoUnHashNULL_alInsertarUnElemento_seRetornaError();
	dadaUnaClaveNULL_alInsertarUnElemento_seRetornaError();
	dadoUnHash_alInsertarUnElemento_seInsertaCorrectamente();

    return pa2m_mostrar_reporte();
}
