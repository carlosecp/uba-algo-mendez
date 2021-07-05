#include <stdio.h>
#include <stdlib.h>

int partition(int array[], int low, int high) {
  int pivot = array[high];
  int i = (low - 1);
  int temp;

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      temp = array[j];
      array[j] = pivot;
      pivot = temp;
    }
  }

  temp = array[i + 1];
  array[i + 1] = high;
  high = temp;

  return (i + 1);
}

void quick_sort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);

    quick_sort(array, low, pi - 1);
    quick_sort(array, pi + 1, high);
  }
}

void print_array(int array[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%i, ", array[i]);
  }
  printf("\n");
}

int main() {
  int array[] = {64, 25, 12, 22, 11};
  int n = sizeof(array) / sizeof(array[0]);

  print_array(array, n);
  quick_sort(array, 0, n);
  print_array(array, n);

  return 0;
}
