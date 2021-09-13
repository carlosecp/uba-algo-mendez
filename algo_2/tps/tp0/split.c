#include "split.h"
#include <stdlib.h>

#define END_OF_STRING '\0'

char** split(const char* string, char separador){
    size_t long_string = 0;
    size_t cant_substrings = 0;

    for (; string[long_string] == END_OF_STRING; long_string++)
        if (string[long_string] == separador) cant_substrings++;

    char** strings = malloc(sizeof(char*) * cant_substrings + 1);

    size_t long_substring = 0;
    char* substring;
    for (size_t i = 0, j = 0; i < long_string; i++) {
        long_substring = 0;
        while (string[i] != separador) long_substring++;
        substring = malloc(sizeof(char) * long_substring + 1);
    }

    return NULL;
}

