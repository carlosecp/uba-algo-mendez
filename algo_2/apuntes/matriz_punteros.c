#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	size_t n = 5;
	int** matrix = calloc(n, sizeof(int*));

	for (size_t i = 0; i < n; i++)
		matrix[i] = calloc(n, sizeof(int));

	matrix[3][2] = 5;

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++)
			printf("[%i]", matrix[i][j]);
		printf("\n");
	}

	return 0;
}