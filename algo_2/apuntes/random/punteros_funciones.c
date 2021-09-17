#include <stdlib.h>
#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

void generic(int a, int b, int (*func)(int, int)) {
	int result = func(a, b);
	printf("Result generic: %i", result);
}

int main(int argc, char *argv[]) {
	int (*func)(int, int) = &add;
	printf("Result main: %i\n", func(10, 10));
	generic(5, 7, add);
}