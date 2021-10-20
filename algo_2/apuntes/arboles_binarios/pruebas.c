#include <stdio.h>
#include <stdlib.h>

#include "pa2mm.h"
#include "src/arbol.h"

typedef struct _alumno_t {
    int dni;
    char* nombre;
    double promedio;
} alumno_t;

int
comparador_alumnos(void* _alumno_1, void* _alumno_2) {
    alumno_t* alumno_1 = _alumno_1;
    alumno_t* alumno_2 = _alumno_2;
    return alumno_1 -> dni - alumno_2 -> dni;
}

bool
imprimir_alumno(void* _alumno, void* aux) {
    alumno_t* alumno = _alumno;
    printf("{ dni: %i, nombre: '%s' }\n", alumno -> dni, alumno -> nombre);
    return true;
}

void
pruebas_varias() {
    abb_t* abb = abb_crear();

    alumno_t alumno_0 = { .dni = 1, .nombre = "Carlos0", .promedio = 90 };
    alumno_t alumno_1 = { .dni = 2, .nombre = "Carlos1", .promedio = 76 };
    alumno_t alumno_2 = { .dni = 3, .nombre = "Carlos2", .promedio = 83 };
    alumno_t alumno_3 = { .dni = 4, .nombre = "Carlos3", .promedio = 82 };
    alumno_t alumno_4 = { .dni = 5, .nombre = "Carlos4", .promedio = 84 };
    alumno_t alumno_5 = { .dni = 6, .nombre = "Carlos5", .promedio = 72 };
    alumno_t alumno_6 = { .dni = 7, .nombre = "Carlos6", .promedio = 90 };
    alumno_t alumno_7 = { .dni = 8, .nombre = "Carlos7", .promedio = 91 };
    alumno_t alumno_8 = { .dni = 9, .nombre = "Carlos8", .promedio = 80 };
    alumno_t alumno_9 = { .dni = 10, .nombre = "Carlos9", .promedio = 78 };

    abb = abb_insertar(abb, &alumno_0, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_1, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_2, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_3, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_4, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_5, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_6, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_7, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_9, comparador_alumnos);
    abb = abb_insertar(abb, &alumno_8, comparador_alumnos);

    abb_con_cada_elemento(abb, PREORDEN, imprimir_alumno, NULL);

    abb_destruir(abb);
}

int
main()
{
    pruebas_varias();
}
