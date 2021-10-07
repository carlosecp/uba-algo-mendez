#ifndef DYNAMIC_STRING_H_
#define DYNAMIC_STRING_H_

#include "dynamic_string_aux.h"

#define INITIAL_MAX 10

string_t* string_crear();

void string_destruir(string_t* string);

#endif