#include <stdlib.h>
#include <stdio.h>

// 1 + 1 + {n * 1} + 1 --> n + 3 --> O(n)
int sumar_numeros_1(int n) {
	int suma = 0; // 1
	for (int i = 0; i < n; i++) { // n
		suma += i; // 1
	}
	return suma; // 1
}

// 1 --> O(1)
int sumar_numeros_2(int n) {
	return n * (n + 1) / 2; // 1
}

// 1 + 1 + 1 + 1 --> 4 --> O(1)
int sumar_numeros_3(int n) {
	int suma = n; // 1
	suma = suma * (n + 1); // 1
	suma /= 2; // 1
	return suma; // 1
}

// OPT1 (if): 1 + 1 + 1 --> 3 --> O(1)
// OPT2 (else): 1 + {n * 1} + 1 --> n + 1 --> O(n)
// O(n)
int sumar_numeros_4(int n) {
	int suma = 0; // 1

	if (n < 10)
		suma = n * (n + 1) / 2; // 1
	else {
		for (int i = 0; i < n; i++) { // n * (1)
			suma += i; // 1
		}
	}

	return suma; // 1
}

// ### TEOREMA DEL MAESTRO ###
// Solo aplicable en algoritmos divide-and-conquer, no a toda funcion recursiva
// T(n) = aT(n/b) + f(n)
int binary_search(int array[], int low, int high, int elem) {
	if (low <= high) {
		int mid = (high + low) / 2;

		/* b = 2 --> binary_search va a llamar a binary_search con el problema divido en 2 */
		/* a = 1 --> binary_search solo hace una llamada recursiva, o if o else */
		if (array[mid] == elem) return mid;
		else if (array[mid] < elem) return binary_search(array, low, mid - 1, elem);
		else return binary_search(array, mid + 1, high, elem);
	}
	else return -1;
}

// Entonces: T(n) = 1*T(n/2) + f(n)
/* El resto (f(n)) seria O(1): (ignoramos la parte recursiva)
int binary_search(int array[], int low, int high, int elem) {
	// if: 1 + 1 --> 2 --> O(1)
	if (low <= high) {
		int mid = (high + low) / 2;
		if (array[mid] == elem) return mid;
		...
	}
	// else: O(1)
	else return 1;
}
*/

// Soluciones del teorema
/*
	-> Si f(n) < n^(log_b a) --> T(n) = O(n^(log_b a))
	-> Si f(n) == n^(log_b a) --> T(n) = O(n^(log_b a)log n)
	-> Si f(n) polinomicamente > n^(log_b a) --> T(n) = O(f(n))
*/