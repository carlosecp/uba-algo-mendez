VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

all: clean pruebas

valgrind: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	gcc $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1 && ./pruebas

clean:
	rm -f *.o pruebas 2>&1
