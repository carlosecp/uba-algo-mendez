#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void invertir_string(char string[], size_t min, size_t max)
{
	if (min >= max)
	{
		return;
	}

	char temp;
	temp = string[min];
	string[min] = string[max];
	string[max] = temp;

	return invertir_string(string, min + 1, max - 1);
}

int main()
{
	char string[] = "testing";
	size_t tope = strlen(string);

	invertir_string(string, 0, tope - 1);
	for (int i = 0; i < tope; i++)
	{
		printf("%c", string[i]);
	}
}