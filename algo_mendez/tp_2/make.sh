#!bin/sh
gcc -c -std=c99 -Wall -Wconversion -Werror osos_contra_reloj.c mapa.c
gcc -std=c99 -Wall -Wconversion -Werror main.c osos_contra_reloj.c mapa.c
