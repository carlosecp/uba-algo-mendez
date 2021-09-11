#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILAS 100
#define MAX_COLUMNAS 100

/* Al volver se su laaaaaarga travesía para destruir el anillo, la vida de Sam
se volvió un poco aburrida. No es que este disconforme con la tranquilidad que
consiguió, solo le gustaría tener algunos hobbies.

Probó zumba, yoga, running, pero nada lo conformaba. Pippin le recomendó que
pruebe resolviendo rompecabezas, que lo iban a entretener.

Empezó con uno de elefantes y le encantó el desafío, hoy se encuentra
resolviendo uno con casitas de colores y está un poco trabado, porque puso todas
las fichas pero como que no le cierra.

El rompecabezas se puede ver como una matriz, donde cada celda es una ficha con
la siguiente estructura:
 */

typedef struct ficha {
    int id_ficha;
    int id_ficha_derecha;
    int id_ficha_izquierda;
    int id_ficha_arriba;
    int id_ficha_abajo;
} ficha_t;

/* Si una ficha está en uno de los bordes, tendrá un -1 en los campos
correspondientes.

1. Determinar cuántas fichas no tienen ninguna de sus fichas vecinas (derecha,
izquierda, arriba y abajo) correctamente puestas. */

bool tiene_vecinas_correctas(ficha_t ficha) {
}

int main() {
    ficha_t fichas[MAX_FILAS][MAX_COLUMNAS];

    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; i < MAX_COLUMNAS; j++) {
			if (i > 0) {

			}
        }
    }

    return 0;
}
