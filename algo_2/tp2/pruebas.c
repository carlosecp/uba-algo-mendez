#include <stdbool.h>

#include "pa2mm.h"
#include "src/heap.h"
#include "src/hospital.h"
#include "src/juego.h"
#include "src/simulador.h"
#include "string.h"

bool ignorar_pokemon(pokemon_t* p) {
    p = p;
    return true;
}

/* No intenten esto en sus casas */
/* Ya vamos a ver como evitar esto en el TDA Lista */
struct {
    pokemon_t* pokemon[500];
    size_t cantidad;
} acumulados;

void resetear_acumulados() {
    acumulados.cantidad = 0;
}

bool acumular_pokemon(pokemon_t* p) {
    acumulados.pokemon[acumulados.cantidad] = p;
    acumulados.cantidad++;
    return true;
}

bool acumular_pokemon_hasta_miltank(pokemon_t* p) {
    acumulados.pokemon[acumulados.cantidad] = p;
    acumulados.cantidad++;
    return strcmp(pokemon_nombre(p), "miltank");
}

bool acumulados_en_orden_correcto() {
    if (acumulados.cantidad < 2)
        return true;
    pokemon_t* anterior = acumulados.pokemon[0];
    for (int i = 1; i < acumulados.cantidad; i++) {
        pokemon_t* actual = acumulados.pokemon[i];
        if (strcmp(pokemon_nombre(anterior), pokemon_nombre(actual)) > 0)
            return false;
    }
    return true;
}

/* Pruebas: Hospital */

void puedoCrearYDestruirUnHospital() {
    hospital_t* h = NULL;

    pa2m_afirmar((h = hospital_crear()), "Crear un hospital devuelve un hospital");

    pa2m_afirmar(hospital_cantidad_entrenadores(h) == 0, "Un hospital se crea con cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h) == 0, "Un hospital se crea con cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon) == 0, "Recorrer los pokemon resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnHospitalNULL_lasPuedoAplicarLasOperacionesDelHospitalSinProblema() {
    hospital_t* h = NULL;

    pa2m_afirmar(hospital_cantidad_entrenadores(h) == 0, "Un hospital NULL tiene cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h) == 0, "Un hospital NULL tiene cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon) == 0, "Recorrer los pokemon de un hospital NULL resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnArchivoVacio_NoSeAgreganPokemonAlHospital() {
    hospital_t* h = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/archivo_vacio.hospital"), "Puedo leer un archivo vacío");

    pa2m_afirmar(hospital_cantidad_entrenadores(h) == 0, "Un hospital vacío tiene cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h) == 0, "Un hospital vacío tiene tiene cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon) == 0, "Recorrer los pokemon resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnArchivoConUnEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital() {
    hospital_t* h = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/un_entrenador.hospital"), "Puedo leer un archivo con un entrenador");

    pa2m_afirmar(hospital_cantidad_entrenadores(h) == 1, "El hospital tiene 1 entrenador");
    pa2m_afirmar(hospital_cantidad_pokemon(h) == 3, "El hospital tiene 3 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon) == 3, "Recorrer los pokemon resulta en 3 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

void dadoUnArchivoConVariosEntrenadores_SeAgreganLosEntrenadoresYSusPokemonAlHospital() {
    hospital_t* h = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(h) == 5, "El hospital tiene 5 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h) == 24, "El hospital tiene 24 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon) == 24, "Recorrer los pokemon resulta en 24 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

void dadosVariosArchivos_puedoAgregarlosTodosAlMismoHospital() {
    hospital_t* h = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer otro archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un tercer archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(h) == 15, "El hospital tiene 15 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h) == 72, "El hospital tiene 72 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon) == 72, "Recorrer los pokemon resulta en 72 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

/* Pruebas simulador */

void dadoUnHospital_alCrearUnSimulador_seRetornaElSimulador() {
    simulador_t* simulador = simulador_crear(NULL);

    pa2m_afirmar(simulador == NULL, "Al crear un simulador con un hospital NULL, el simulador es igual a NULL");

    hospital_t* hospital = hospital_crear();
    simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL, "Al crear un simulador con un hospital valido, se retorna un simulador valido");

    simulador_destruir(simulador);
}

/* Pruebas evento "ObtenerEstadisticas" */

void dadosLosDatosDelSimulador_alObtenerLasEstadisticas_seRetornaElResultadoEsperado() {
    hospital_t* hospital = hospital_crear();
    hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital");

    simulador_t* simulador = simulador_crear(hospital);

    ResultadoSimulacion res;
    EstadisticasSimulacion e = {0};

    res = simulador_simular_evento(simulador, ObtenerEstadisticas, NULL);
    pa2m_afirmar(res == ErrorSimulacion, "Al obtener las estadisticas del simulador pasando un dato NULL, se retorna ErrorSimulacion");

    res = simulador_simular_evento(simulador, ObtenerEstadisticas, &e);
	pa2m_afirmar((e.entrenadores_totales == hospital_cantidad_entrenadores(hospital)) &&
			(e.pokemon_totales == hospital_cantidad_pokemon(hospital)),
			"Las cantidades de entrenadores y pokemones de las estadisticas coinciden con las cantidades del hospital");

    simulador_destruir(simulador);
}

/* Pruebas evento "AtenderProximoEntrenador" */

void dadoUnSimuladorConUnHospitalVacio_alAtenderUnEntrenador_seRetornaError() {
    hospital_t* hospital = hospital_crear();
    hospital_leer_archivo(hospital, "ejemplos/archivo_vacio.hospital");

    simulador_t* simulador = simulador_crear(hospital);

	ResultadoSimulacion res;
	
	res = simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
	pa2m_afirmar(res == ErrorSimulacion, "Al atender el proximo entrendor en un hospital sin entrenadores, se retorna ErrorSimulacion");

    simulador_destruir(simulador);
}

struct _simulador_t {
    hospital_t* hospital;
    EstadisticasSimulacion estadisticas;
    heap_t* recepcion_pokemones;
};

void dadoUnSimulador_alAtenderUnEntrenador_suPokemonesSonAgregadosALaSalaDeEspera() {
	hospital_t* hospital = hospital_crear();
	hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital");

	simulador_t* simulador = simulador_crear(hospital);

	ResultadoSimulacion res;

	res = simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
	pa2m_afirmar(res == ExitoSimulacion, "Al atender a un entrenador correctamente se retorna ExitoSimulacion");

	simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);

	simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
	simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
	simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);
	res = simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);

	pa2m_afirmar(res == ErrorSimulacion, "Luego de atender a todos los entrenadores de un hospital, si se intenta antender al proximo, se retorna ErrorSimulacion");

	simulador_destruir(simulador);
}

/* Pruebas heap */

int comparador(void* _a, void* _b) {
    int* a = _a;
    int* b = _b;

    if (*a > *b)
        return 1;
    else if (*a < *b)
        return -1;

    return 0;
}

void dadoUnComparador_alCrearUnHeap_seCreaCorrectamente() {
    heap_t* heap = heap_crear(NULL);

    pa2m_afirmar(heap == NULL, "Al crear un heap con un comparador NULL, el comparador es igual a NULL");

    heap = heap_crear(comparador);
    pa2m_afirmar(heap != NULL, "Al crear un heap con un comparador valido, se retorna un heap");
    pa2m_afirmar(heap_tamanio(heap) == 0, "Al crear un heap el tamanio inicial es igual a 0");

    heap_destruir(heap);
}

void dadoUnHeap_alInsertarElementos_seInsertanCorrectamente() {
    heap_t* heap = NULL;

    int e0 = 3019, e1 = 5828, e2 = 1257;

    size_t res;
    res = heap_insertar(heap, &e0);

    pa2m_afirmar(res == 0, "Al insertar en un heap NULL, se retorna la cantidad de elementos que es igual a 0");

    heap = heap_crear(comparador);

    res = heap_insertar(heap, &e0);
    res = heap_insertar(heap, &e1);
    res = heap_insertar(heap, &e2);

    pa2m_afirmar(res == heap_tamanio(heap), "Al insertar elementos en un heap se retorna el tamanio correcto del heap");
    pa2m_afirmar(res == 3, "Al insertar 3 elementos en un heap, se retorna la cantidad de elementos que es igual a 3");

    heap_destruir(heap);
}

void dadoUnHeapMinimal_alQuitarElementos_seRetornaElMenorElementoDelHeap() {
    heap_t* heap = NULL;

    pa2m_afirmar(heap_extraer_raiz(heap) == NULL, "Al extraer la raiz de un heap NULL, se retorna NULL");

    heap = heap_crear(comparador);
    pa2m_afirmar(heap_extraer_raiz(heap) == NULL, "Al extraer la raiz de un heap vacio, se retorna NULL");

    int e0 = 3019, e1 = 5828, e2 = 1257, e3 = 4761, e4 = 2779, e5 = 629,
        e6 = 9689, e7 = 2728, e8 = 2783, e9 = 2774;

    heap_insertar(heap, &e0);
    heap_insertar(heap, &e1);
    heap_insertar(heap, &e2);
    heap_insertar(heap, &e3);
    heap_insertar(heap, &e4);
    heap_insertar(heap, &e5);
    heap_insertar(heap, &e6);
    heap_insertar(heap, &e7);
    heap_insertar(heap, &e8);
    heap_insertar(heap, &e9);

    int extraido = *(int*)heap_extraer_raiz(heap);

    pa2m_afirmar(extraido == e5, "Al extraer la raiz de un heap minimal, se obtiene el elemento de menor valor entre todos los insertados");
    pa2m_afirmar(heap_tamanio(heap) == 9, "Al extraer la raiz de un heap su tamanio se reduce");

    extraido = *(int*)heap_extraer_raiz(heap);
    pa2m_afirmar(extraido == e2, "Al extraer la raiz de un heap minimal por segunda vez, se obtiene el segundo elemento de menor valor entre todos los insertados");

    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);
    heap_extraer_raiz(heap);

    pa2m_afirmar(heap_tamanio(heap) == 0, "Al extraer todos los elementos de un heap, el tamanio es igual a 0");

    heap_destruir(heap);
}

int main() {
    pa2m_nuevo_grupo("Pruebas de creación y destrucción");
    puedoCrearYDestruirUnHospital();

    pa2m_nuevo_grupo("Pruebas con NULL");
    dadoUnHospitalNULL_lasPuedoAplicarLasOperacionesDelHospitalSinProblema();

    pa2m_nuevo_grupo("Pruebas con un archivo vacío");
    dadoUnArchivoVacio_NoSeAgreganPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con un archivo de un entrenador");
    dadoUnArchivoConUnEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con un archivo de varios entrenadores");
    dadoUnArchivoConVariosEntrenadores_SeAgreganLosEntrenadoresYSusPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con mas de un archivo");
    dadosVariosArchivos_puedoAgregarlosTodosAlMismoHospital();

    pa2m_nuevo_grupo("Pruebas simulador");
    dadoUnHospital_alCrearUnSimulador_seRetornaElSimulador();

    pa2m_nuevo_grupo("Pruebas evento \"ObtenerEstadisticas\"");
    dadosLosDatosDelSimulador_alObtenerLasEstadisticas_seRetornaElResultadoEsperado();

    pa2m_nuevo_grupo("Pruebas evento \"AtenderProximoEntrenador\"");
	dadoUnSimuladorConUnHospitalVacio_alAtenderUnEntrenador_seRetornaError();
	dadoUnSimulador_alAtenderUnEntrenador_suPokemonesSonAgregadosALaSalaDeEspera();

    pa2m_nuevo_grupo("Pruebas heap");
    dadoUnComparador_alCrearUnHeap_seCreaCorrectamente();
    dadoUnHeap_alInsertarElementos_seInsertanCorrectamente();
    dadoUnHeapMinimal_alQuitarElementos_seRetornaElMenorElementoDelHeap();

    return pa2m_mostrar_reporte();
}
