#include <stdlib.h>
#include <stdio.h>
#include "hospital.h"
#include "parser.h"

int main(int argc, char *argv[]) {
	hospital_t* hospital = hospital_crear();
	hospital_leer_archivo(hospital, "test.txt");
	hospital_destruir(hospital);
	return 0;
}
