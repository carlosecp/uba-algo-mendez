#include <stdlib.h>
#include <stdio.h>

size_t strlen(const char* string) {
	if (string == 0) return 0;
	return 1 + strlen(string + 1);
}

int main(int argc, char* argv[]) {
	printf("Len: %li", strlen("test"));
	return 0;
}
