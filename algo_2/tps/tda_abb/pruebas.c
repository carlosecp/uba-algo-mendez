#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

// Auxiliares para pruebas

typedef struct estudiante_fiuba {
	unsigned padron;
	char* nombre;
} estudiante_fiuba_t;

estudiante_fiuba_t*
crear_estudiante_fiuba(unsigned padron, char* nombre) {
	estudiante_fiuba_t* est = malloc(sizeof(estudiante_fiuba_t));
	est -> padron = padron;
	est -> nombre = nombre;
	return est;
}

void  
destruir_estudiante_fiuba(void* _est) {
	free(_est);
}

int
comparador_estudiantes_fiuba(void* _est_1, void* _est_2)
{
	estudiante_fiuba_t* est_1 = _est_1;
	estudiante_fiuba_t* est_2 = _est_2;

	if (est_1 -> padron == est_2 -> padron)
		return 0;

	return est_1 -> padron < est_2 -> padron ? -1 : 1;
}

// Pruebas: Creacion y Destruccion

void
puedoCrearYDestruirUnABB()
{
	abb_t* arbol = abb_crear(comparador_estudiantes_fiuba);

	pa2m_afirmar(arbol -> nodo_raiz == NULL, "Para un arbol nuevo, la raiz es NULL");
	pa2m_afirmar(arbol -> comparador == comparador_estudiantes_fiuba, "Para un arbol nuevo, el comparador es el correcto");
	pa2m_afirmar(abb_vacio(arbol), "Un arbol se crea vacio");

	abb_destruir(arbol);
}

void
dadoUnComparadorNULL_noPuedoCrearUnABB() {
	abb_t* arbol = abb_crear(NULL);

	pa2m_afirmar(arbol == NULL, "No puedo crear un arbol con un comparador NULL");

	abb_destruir(arbol);
}

void
dadoUnABB_puedoDestruirTodosLosElementos() {
    abb_t* arbol = abb_crear(comparador_estudiantes_fiuba);

	estudiante_fiuba_t* est_0 = crear_estudiante_fiuba(103372, "Alejandro Schamun");
	estudiante_fiuba_t* est_1 = crear_estudiante_fiuba(104942, "Cami Fiorotto");
	estudiante_fiuba_t* est_2 = crear_estudiante_fiuba(104898, "Carolina Aramay");
	estudiante_fiuba_t* est_3 = crear_estudiante_fiuba(106818, "Facundo Sanso");
	estudiante_fiuba_t* est_4 = crear_estudiante_fiuba(107057, "Joaquin Dopazo");
	estudiante_fiuba_t* est_5 = crear_estudiante_fiuba(108031, "Julian Calderon");
	estudiante_fiuba_t* est_6 = crear_estudiante_fiuba(108229, "Julian Stiefkens");
	estudiante_fiuba_t* est_7 = crear_estudiante_fiuba(104961, "Manuel Sanchez");
	estudiante_fiuba_t* est_8 = crear_estudiante_fiuba(108665, "Nicolas Celano");
	estudiante_fiuba_t* est_9 = crear_estudiante_fiuba(107180, "Nicolas Tonizzo");

	arbol = abb_insertar(arbol, est_0);
	arbol = abb_insertar(arbol, est_1);
	arbol = abb_insertar(arbol, est_2);
	arbol = abb_insertar(arbol, est_3);
	arbol = abb_insertar(arbol, est_4);
	arbol = abb_insertar(arbol, est_5);
	arbol = abb_insertar(arbol, est_6);
	arbol = abb_insertar(arbol, est_7);
	arbol = abb_insertar(arbol, est_8);
	arbol = abb_insertar(arbol, est_9);

    abb_destruir_todo(arbol, destruir_estudiante_fiuba);
}

// Pruebas: Insertar

void
dadoUnABB_alInsetarUnElemento_seDevuelveElABB() {
	abb_t* arbol = abb_crear(comparador_estudiantes_fiuba);

	abb_destruir(arbol);
}

void
dadoUnABBNULL_alInsertarUnElemento_seDevuelveNULL() {
}

void
dadoUnABBVacio_alInsertarElPrimerElemento_eseElementoPasaASerLaRaiz()
{
}

void
dadoUnABB_alInsertarVariosElementos_seInsertanTodosLosElementos()
{
}

void
dadoUnABBNULL_alRecorrerElABB_seRecorrenCeroElementos()
{
}

void
dadoUnABBVacio_alRecorrerElABB_seRecorrenCeroElementos()
{
}

void
dadaUnABBConVariosElementosYUnVectorNULL_alRecorrerElABB_seRecorrenCeroElementos()
{
}

void
dadoUnABBConVariosElementos_alRecorrerElABB_seRecorrenLaCantidadDeElementosCorrecta()
{
}

void
dadoUnABBConDiezElementos_alRecorrerCincoElementosDelABB_seRecorrenSolamenteCincoElementos()
{
}

void
dadoUnABBConDiezElementos_alRecorrerQuinceElementos_seRecorrenSolamenteDiezElementos()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoHoja_seDevuelveEseElemento()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConUnHijo_seDevuelveEseElemento()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConDosHijos_seDevuelveEseElemento()
{
}

void
dadoUnABBNULL_alQuitarUnElemento_seDevuelveNULL()
{
}

void
dadoUnABBVacio_alQuitarUnElemento_seDevuelveNULL()
{
}

void
dadoUnABB_alQuitarTodosLosElementos_seQuitanExitosamente()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConUnHijo_elABBSigueSiendoUnABB()
{
}

void
dadoUnABB_alQuitarUnElementoEnUnNodoConDosHijos_elABBSigueSiendoUnABB()
{
}

void
dadoUnABBConCincoElementos_alQuitarUnElemento_elTamanioDelABBEsCuatro()
{
}

void
dadoUnABBConVariosElementos_alQuitarTodosLosElementos_elABBQuedaVacio()
{
}

int
main() {
    pa2m_nuevo_grupo("Pruebas: Creacion y Destruccion");
	puedoCrearYDestruirUnABB();
	dadoUnComparadorNULL_noPuedoCrearUnABB();
	dadoUnABB_puedoDestruirTodosLosElementos();

    pa2m_nuevo_grupo("Pruebas: Insertar");

	pa2m_nuevo_grupo("Pruebas: Recorrer");

	pa2m_nuevo_grupo("Pruebas: Quitar");

    return pa2m_mostrar_reporte();
}
