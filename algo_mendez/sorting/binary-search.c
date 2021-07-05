#include <stdio.h>
#include <stdlib.h>

int binary_search_recursive(int array[], int element, int low, int high) {
  if (high >= low) {
    int mid = low + (high - low) / 2;
    if (array[mid] == element)
      return mid;

    if (array[mid] < element)
      return binary_search_recursive(array, element, (mid + 1), high);

    return binary_search_recursive(array, element, low, (mid - 1));
  }

  return -1;
}

int main() {
  int array[] = {1, 2, 3, 4, 5, 6, 6, 7, 8, 8, 9, 10, 100, 200, 300};
  int n = sizeof(array) / sizeof(array[0]);
  int element;
  printf("Elemento a buscar: ");
  scanf("%i", &element);

  int result = binary_search_recursive(array, element, 0, (n - 1));
  printf("Resultado: %i", result);

  return 0;
}
