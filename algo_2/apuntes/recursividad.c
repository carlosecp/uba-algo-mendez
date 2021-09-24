#include <stdlib.h>
#include <stdio.h>

// Factorial de acumulacion
/* Llevamos el resultado en una variable aparte, asi la funcion
recursiva no tiene que esperar al resultado de la multiplicacion. */ 
unsigned int factorial_rec(unsigned int n, unsigned int res) {
	if (n == 0)
		return res;
	return factorial_rec(n - 1, res * n); 
}

/* Al hacer esto, cada una de nuestras funciones recursivas se 
libera del stack luego de cada llamada. Puedo seguir reutilizando
el stackframe siempre, porque no se vuelven a utilizar los valores 
locales y la funcion recursiva no tiene que esperar el resultado 
de las demas. */
unsigned int factorial(unsigned int n) {
	return factorial_rec(n, 1);
}

// Invertir una string de forma recursiva
void mostrar_invertido(const char* string) {
	if (!*string)
		return;

	mostrar_invertido(string + 1);
	printf("%c", *string);
}

// Sumatoria vector recursivo
int sumar_numeros_vector(int* vector, size_t cantidad_numeros) {
	if (!cantidad_numeros)
		return 0;

	return *vector + sumar_numeros_vector(vector + 1, cantidad_numeros - 1);
}

int main(int argc, char *argv[]) {
	return 0;
}
