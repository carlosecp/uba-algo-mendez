#include "pa2mm.h"
#include "dynamic_string.h"
#include "dynamic_string_aux.h"

void
alCrearUnaString_seCrearCorrectamente()
{
	string_t* string = string_crear();

	pa2m_afirmar(string != NULL, "La string se crea correctamente");
	pa2m_afirmar(string_cantidad_caracteres(string) == 0, "La string se crea con 0 caracteres");

	string_destruir(string);
}

int
main()
{
	alCrearUnaString_seCrearCorrectamente();
}