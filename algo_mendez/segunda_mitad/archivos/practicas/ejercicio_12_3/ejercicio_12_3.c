#include <stdlib.h>
#include <stdio.h>

int main()
{
	FILE *archivo_pedidos = fopen("pedidos.txt", "r");
	FILE *archivo_pedidos_aux = fopen("pedidos_aux.txt", "w");

	if (archivo_pedidos == NULL)
	{
		perror("Error al abrir pedidos.txt");
		return -1;
	}

	if (archivo_pedidos_aux == NULL)
	{
		perror("Error al abrir pedidos_aux.txt");
		return -1;
	}

	fclose(archivo_pedidos);
	fclose(archivo_pedidos_aux);

	return 0;
}