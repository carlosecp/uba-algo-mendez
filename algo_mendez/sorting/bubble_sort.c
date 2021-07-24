#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int array[], int n) {
  int temp;
  for (int i = 0; i < (n - 1); i++) {
    for (int j = 0; j < (n - i) - 1; j++) {
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
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
  bubble_sort(array, n);
  print_array(array, n);

  return 0;
}
