#include "split.h"
#include <stdio.h>
#include <stdlib.h>

#define END_OF_STRING '\0'

char** split(const char* string, char separador){
    size_t long_string = 0;
    size_t cant_substrings = 0;

    for (; string[long_string] != '\0'; long_string++)
        if (string[long_string] == separador) cant_substrings++;

    printf("Long: %li\nCant: %li", long_string, cant_substrings);
}

int main() {
    split("testing:testing:testing", ':');
    return 0;
}
