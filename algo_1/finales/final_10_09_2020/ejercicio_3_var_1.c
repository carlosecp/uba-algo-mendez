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

1. Determinar cuántas fichas deberían estar en un borde y no lo están. */

bool ficha_deberia_estar_en_borde(ficha_t ficha) {
    return (ficha.id_ficha_derecha == -1 || ficha.id_ficha_izquierda == -1 ||
            ficha.id_ficha_abajo == -1 || ficha.id_ficha_abajo == -1);
}

bool ficha_esta_en_borde(int fila_ficha, int columna_ficha) {
    return (fila_ficha == 0 || fila_ficha == MAX_FILAS - 1) ||
           (columna_ficha == 0 || columna_ficha == MAX_COLUMNAS - 1);
}

int main() {
    ficha_t fichas[MAX_FILAS][MAX_COLUMNAS];
	int cantidad_fichas_incorrectas = 0;

    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; i < MAX_COLUMNAS; j++) {
            if (ficha_deberia_estar_en_borde(fichas[i][j]) && !ficha_esta_en_borde(i, j)) {
				cantidad_fichas_incorrectas++;
			}
        }
    }

    return 0;
}
