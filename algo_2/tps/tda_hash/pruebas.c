#include "pa2mm.h"
#include "src/hash.h"
#include "./src/casilla.h"

struct hash {
	casilla_t** casillas;
	size_t cantidad_casillas;
	size_t cantidad_elementos;
	hash_destruir_dato_t destruir_elemento;
};

typedef struct {
	size_t padron;
	char* nombre;
} estudiante_t;

estudiante_t* crear_estudiante(size_t padron, char* nombre) {
	estudiante_t* est = malloc(sizeof(estudiante_t));
	est->padron = padron;
	est->nombre = nombre;
	return est;
}

void destruir_estudiante(void* _est) {
	free(_est);
}

void imprimir_casilla(casilla_t* casilla) {
	if (!casilla)
		return;

	estudiante_t est = *(estudiante_t*)casilla->elemento;
	printf(" {%s: {%s, %li}} ", casilla->clave, est.nombre, est.padron);
	imprimir_casilla(casilla->siguiente);
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
	hash_t* hash = hash_crear(destruir_estudiante, 3);
	pa2m_afirmar(hash_insertar(hash, NULL, NULL)==-1, "Al insertar con una clave NULL se retorna error");
	hash_destruir(hash);
}

void dadoUnHash_alInsertarUnElemento_seInsertaCorrectamente() {
	hash_t* hash = hash_crear(destruir_estudiante, 10);

	estudiante_t* est0 = crear_estudiante(25, "Alejandro Schamun");
	estudiante_t* est1 = crear_estudiante(20, "Cami Fiorotto");
	estudiante_t* est2 = crear_estudiante(36, "Carolina Aramay");
	estudiante_t* est3 = crear_estudiante(10, "Facundo Sanso");
	estudiante_t* est4 = crear_estudiante(22, "Joaquin Dopazo");

	pa2m_afirmar(hash_insertar(hash, "primero", est0)==0, "Al insertar elemento 'primero' correctamente se retorna 1");
	pa2m_afirmar(hash_insertar(hash, "segundo", est1)==0, "Al insertar elemento 'segundo' correctamente se retorna 1");
	pa2m_afirmar(hash_insertar(hash, "tercero", est2)==0, "Al insertar elemento 'tercero' correctamente se retorna 1");
	pa2m_afirmar(hash_insertar(hash, "cuarto",  est3)==0, "Al insertar elemento 'cuarto' correctamente se retorna 1");
	pa2m_afirmar(hash_insertar(hash, "quinto",  est4)==0, "Al insertar elemento 'quinto' correctamente se retorna 1");

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
