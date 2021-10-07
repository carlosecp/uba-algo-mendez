CFLAGS=-ggdb -O0 -std=c99 -Wall -Wconversion -Wtype-limits -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

valgrind: pruebas
	valgrind $(VFLAGS) ./a.out 2>&1

pruebas: pruebas.c *.c *.h
	gcc $(CFLAGS) pruebas.c *.c 2>&1