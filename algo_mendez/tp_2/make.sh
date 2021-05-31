export CFLAGS="-std=c99 -Wall -Wconversion -Werror -lm"
gcc $CFLAGS -c *.c
gcc $CFLAGS *.c utiles.o -o juego
