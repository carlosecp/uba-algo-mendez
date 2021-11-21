#include "pa2mm.h"
#include "src/hash.h"
#include "./src/casilla.h"

#define EXITO 0
#define ERROR -1

struct hash {
	casilla_t** casillas;
	size_t cantidad_casillas;
	size_t cantidad_elementos;
	hash_destruir_dato_t destruir_elemento;
};

						 /* Auxiliares para pruebas */

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

void destruir_estudiante(void* est) {
	free(est);
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

						  /* Pruebas Hash: Creacion */

void dadoUnDestructorYUnValorInicialValido_alCrearUnHash_seRetornaUnHashCon0Elementos() {
	hash_t* hash = hash_crear(destruir_estudiante, 3);
	pa2m_afirmar(hash != NULL, "Al crear un hash con un destructor y valor inicial valido, se retorna un hash no NULL");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Al crear un hash, la cantidad de elementos es 0");
	hash_destruir(hash);
}

						  /* Pruebas Hash: Insertar */

void dadoUnHashNULL_alInsertarUnElemento_seRetornaError() {
	hash_t* hash = NULL;
	pa2m_afirmar(hash_insertar(hash, "clave", NULL) == ERROR, "Al insertar en un hash NULl se retorna ERROR (-1)");
	hash_destruir(hash);
}

void dadaUnaClaveNULL_alInsertarUnElemento_seRetornaError() {
	hash_t* hash = hash_crear(destruir_estudiante, 3);
	pa2m_afirmar(hash_insertar(hash, NULL, NULL) == ERROR, "Al insertar con una clave NULL se retorna ERROR (-1)");
	hash_destruir(hash);
}

void dadoUnHash_alInsertarVariosElementos_seInsertanCorrectamente() {
	hash_t* hash = hash_crear(destruir_estudiante, 10);

	estudiante_t* est0 = crear_estudiante(25, "Alejandro Schamun");
	estudiante_t* est1 = crear_estudiante(20, "Cami Fiorotto");
	estudiante_t* est2 = crear_estudiante(36, "Carolina Aramay");
	estudiante_t* est3 = crear_estudiante(10, "Facundo Sanso");
	estudiante_t* est4 = crear_estudiante(22, "Joaquin Dopazo");

	pa2m_afirmar(hash_insertar(hash, "primero", est0) == EXITO, "Al insertar un elemento correctamente se retorna EXITO (0)");

	hash_insertar(hash, "segundo", est1);
	hash_insertar(hash, "tercero", est2);
	hash_insertar(hash, "cuarto",  est3);
	hash_insertar(hash, "quinto",  est4);

	pa2m_afirmar(hash_cantidad(hash) == 5, "Al insertar 5 elementos en un hash la cantidad de elementos es 5");

	hash_destruir(hash);
}

void dadoUnHash_alInsertarUnElementoConUnaClaveRepetida_seInsertaCorrectamente() {
	hash_t* hash = hash_crear(destruir_estudiante, 10);

	estudiante_t* est0 = crear_estudiante(25, "Alejandro Schamun");
	estudiante_t* est1 = crear_estudiante(20, "Cami Fiorotto");

	hash_insertar(hash, "primero", est0);

	pa2m_afirmar(hash_insertar(hash, "primero", est1) == EXITO, "Al insertar un elemento con clave repetida correctamente se retorna EXITO (0)");
	pa2m_afirmar(hash_cantidad(hash) == 1, "Al insertar un elemento con clave repetida, la cantidad de elementos en el hash se mantiene igual");

	hash_destruir(hash);
}

						   /* Pruebas Hash: Quitar */

void dadoUnHashNULL_alQuitarUnElemento_seRetornaError() {
	hash_t* hash = NULL;
	pa2m_afirmar(hash_quitar(hash, "clave"), "Al quitar un elemento de un hash NULL se devuelve -1");
	hash_destruir(hash);
}

void dadaUnaClaveNULL_alQuitarUnElemento_seRetornaError() {
	hash_t* hash = hash_crear(destruir_estudiante, 3);
	pa2m_afirmar(hash_quitar(hash, NULL) == ERROR, "Al quitar con una clave NULL se retorna ERROR (-1)");
	hash_destruir(hash);
}

void dadoUnHash_alQuitarVariosElementos_seQuitanCorrectamente() {
	hash_t* hash = hash_crear(destruir_estudiante, 3);

	estudiante_t* est0 = crear_estudiante(25, "Alejandro Schamun");
	estudiante_t* est1 = crear_estudiante(20, "Cami Fiorotto");
	estudiante_t* est2 = crear_estudiante(36, "Carolina Aramay");
	estudiante_t* est3 = crear_estudiante(10, "Facundo Sanso");
	estudiante_t* est4 = crear_estudiante(22, "Joaquin Dopazo");
	estudiante_t* est5 = crear_estudiante(22, "Joaquin Dopazo");

	hash_insertar(hash, "primero", est0);

	pa2m_afirmar(hash_quitar(hash, "primero") == EXITO, "Al quitar un elemento correctamente se retorna EXITO (0)");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Al quitar un elemento la cantidad de elementos disminuye");
	pa2m_afirmar(hash_quitar(hash, "no_existe") == ERROR, "Al intentar quitar un elemento con una clave que no existe, se retorna ERROR (-1)");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Al intentar quitar un elemento con una clave que no existe, la cantidad no se disminuye");

	hash_insertar(hash, "segundo", est1);
	hash_insertar(hash, "tercero", est2);
	hash_insertar(hash, "cuarto",  est3);
	hash_insertar(hash, "quinto",  est4);
	hash_insertar(hash, "sexto",   est5);

	hash_quitar(hash, "segundo");
	hash_quitar(hash, "tercero");
	hash_quitar(hash, "cuarto");
	hash_quitar(hash, "quinto");
	hash_quitar(hash, "sexto");

	pa2m_afirmar(hash_cantidad(hash) == 0, "Al quitar todos los elementos la cantidad de elementos es 0");

	hash_destruir(hash);
}

						  /* Pruebas Hash: Obtener */

void dadoUnHashNULL_alObtenerUnElemento_seRetornaFalse() {
	hash_t* hash = NULL;
	pa2m_afirmar(hash_obtener(hash, "no_existe") == false, "");
	hash_destruir(hash);
}

void dadaUnaClaveNULL_alObtenerUnElemento_seRetornaError() {
	hash_t* hash = hash_crear(destruir_estudiante, 3);
	pa2m_afirmar(hash_obtener(hash, NULL) == false, "");
	hash_destruir(hash);
}

int main() {
	pa2m_nuevo_grupo("Pruebas Hash: Creacion");
	dadoUnDestructorYUnValorInicialValido_alCrearUnHash_seRetornaUnHashCon0Elementos();
	
	pa2m_nuevo_grupo("Pruebas Hash: Insertar");
	dadoUnHashNULL_alInsertarUnElemento_seRetornaError();
	dadaUnaClaveNULL_alInsertarUnElemento_seRetornaError();
	dadoUnHash_alInsertarVariosElementos_seInsertanCorrectamente();
	dadoUnHash_alInsertarUnElementoConUnaClaveRepetida_seInsertaCorrectamente();

	pa2m_nuevo_grupo("Pruebas Hash: Quitar");
	dadoUnHashNULL_alQuitarUnElemento_seRetornaError();
	dadaUnaClaveNULL_alQuitarUnElemento_seRetornaError();
	dadoUnHash_alQuitarVariosElementos_seQuitanCorrectamente();

    return pa2m_mostrar_reporte();
}
