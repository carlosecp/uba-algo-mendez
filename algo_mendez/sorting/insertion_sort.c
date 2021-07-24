#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int array[], int n) {
  int key;
  int j;

  for (int i = 1; i < n; i++) {
    key = array[i];
    j = i - 1;

    while ((key < array[j]) && (j >= 0)) {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = key;
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
  insertion_sort(array, n);
  print_array(array, n);

  return 0;
}
