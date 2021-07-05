#include <stdio.h>
#include <stdlib.h>

void selection_sort(int array[], int n) {
  int minimum;
  int temp;

  for (int i = 0; i < (n - 1); i++) {
    minimum = i;
    for (int j = (i + 1); j < n; j++) {
      if (array[minimum] > array[j]) {
        minimum = j;
      }
    }

    temp = array[i];
    array[i] = array[minimum];
    array[minimum] = temp;
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
  selection_sort(array, n);
  print_array(array, n);

  return 0;
}
