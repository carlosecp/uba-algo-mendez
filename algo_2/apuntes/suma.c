#include <stdlib.h>
#include <stdio.h>

int* suma(int a, int b) {
	int* c = malloc(sizeof(int));
	*c = a + b;
	return c;
}

int main() {
	printf("Suma: %i", *suma(5, 7));
	return 0;
}
