VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc

all: clean valgrind

valgrind: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/nodo.c src/lista.c src/cola.c src/pila.c pruebas.c -o pruebas 2>&1

clean:
	rm -f *.o pruebas 2>&1
