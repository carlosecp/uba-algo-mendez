#include <stdlib.h>
#include <stdio.h>
#include "hospital.h"

int main(int argc, char *argv[]) {
	hospital_t* hospital = hospital_crear();
	hospital_leer_archivo(hospital, "test.csv");

	size_t cantidad_pokemones = hospital_cantidad_entrenadores(hospital);
	hospital_destruir(hospital);
	return 0;
}