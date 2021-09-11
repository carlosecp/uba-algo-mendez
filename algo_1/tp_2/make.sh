export CFLAGS="-std=c99 -Wall -Wconversion -Werror -lm -g"
gcc $CFLAGS -c *.c
gcc $CFLAGS *.c utiles.o
