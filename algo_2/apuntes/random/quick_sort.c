#include <stdlib.h>
#include <stdio.h>

int partition(int array[], int low, int high) {
	int pivot = array[high];
	int i = (low - 1);

	int temp;
	for (int j = low; j < high; j++) {
		if (array[j] < pivot) {
			i++;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}

	temp = array[i + 1];
	array[i + 1] = array[high];
	array[high] = temp;
	
	return i + 1;
}

void quick_sort(int array[], int low, int high) {
	if (low < high) {
		int pivot_index = partition(array, low, high);

		quick_sort(array, pivot_index + 1, high);
		quick_sort(array, low, pivot_index - 1);
	}
}

int main(int argc, char *argv[]) {
	int* array = calloc(argc - 1, sizeof(int));
	int tope = 0;
	for (int i = 1; i < argc; i++) {
		array[i - 1] = atoi(argv[i]);
		tope++;
	}

	printf("Antes: [");
	for (int i = 0; i < tope; i++) {
		printf(" %i ", array[i]);
	}
	printf("]\n");

	quick_sort(array, 0, tope - 1);
	printf("Despues: [");
	for (int i = 0; i < tope; i++) {
		printf(" %i ", array[i]);
	}
	printf("]");

	free(array);
	return 0;
}