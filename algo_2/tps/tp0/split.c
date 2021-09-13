// #include "split.h"
#include <stdio.h>
#include <stdlib.h>

#define END_OF_STRING '\0'

void split(const char* string, char separador){
    size_t long_string = 0;
    size_t cant_substrings = 0;

	size_t i = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (string[i] == separador) cant_substrings++;
		long_string++;
	}

	cant_substrings += 1;
	char** vector_substrings = malloc((cant_substrings + 1) * sizeof(char*));

	size_t long_substring = 0;
	char** substring;

	for (i = 0; string[i] != '\0'; i++) {
		long_substring = 0;
		while (string[long_substring] != separador) long_substring++;

		substring = malloc((long_substring + 1) * sizeof(char));
		memcpy(*vector_substrings, substring, long_substring);
		vector_substrings[long_substring] = '\0';

		long_substring++;
	}

    printf("Long: %li\nCant: %li", long_string, cant_substrings);
}

int main() {
    split("testing:testing:testing", ':');
    return 0;
}
