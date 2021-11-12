#include <stdlib.h>

typedef struct _Azul {
	int campo1;
	void** campo2;
} Azul;

int
main(int argc, char* argv[])
{
	Azul* azul = calloc(1, sizeof(Azul));

	azul -> campo2 = calloc(5, sizeof(void*));

	for (size_t i = 0; i < 5; i++) {
		azul -> campo2[i] = calloc(i + 1, sizeof(void*));
	}

	return 0;
}
