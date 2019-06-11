#include "fila.h"
#include <stdio.h>
#include <string.h>

int teste_fila_make_node(void);
int teste_fila_insert_node(void);
int teste_fila_find_node(void);
int teste_fila_max_id(void);
int teste_fila_free(void);

int main()
{
	if (teste_fila_make_node() == 1)
		printf("test_fila_make_node() - OK\n");
	else
		printf("test_fila_make_node() - NOT OK\n");

	if (teste_fila_insert_node() == 1)
		printf("test_fila_insert_node() - OK\n");
	else
		printf("test_fila_insert_node() - NOT OK\n");

	if (teste_fila_find_node() == 1)
		printf("test_fila_find_node() - OK\n");
	else
		printf("test_fila_find_node() - NOT OK\n");

	if (teste_fila_max_id() == 1)
		printf("test_fila_max_id() - OK\n");
	else
		printf("test_fila_max_id() - NOT OK\n");

	if (teste_fila_free() == 1)
		printf("test_fila__free() - OK\n");
	else
		printf("test_fila_free() - NOT OK\n");
}

int teste_fila_make_node(void)
{
	Msg *msg = msg_make_node(2, "Ola");
	Fila *fila = fila_make_node(2, msg);

	if (strcmp("Ola", fila->mensagens->content) != 0 || fila->id != 2)
		return 0;

	return 1;
}

int teste_fila_insert_node(void)
{
	Fila *fila = fila_make_node(2, NULL);
	fila = fila_insert_node(fila, fila_make_node(3, NULL));
	fila = fila_insert_node(fila, fila_make_node(4, NULL));

	int count = 0;

	while (fila != NULL)
	{
		count++;
		fila = fila->p_seg;
	}

	if (count != 3)
		return 0;

	return 1;
}

int teste_fila_find_node(void)
{
	Fila *fila = fila_make_node(2, NULL);
	fila = fila_insert_node(fila, fila_make_node(3, NULL));
	fila = fila_insert_node(fila, fila_make_node(4, NULL));

	Fila *aux = fila_find_node(fila, 4);

	if (aux->id != 4)
		return 0;

	return 1;
}

int teste_fila_max_id(void)
{
	Fila *fila = fila_make_node(2, NULL);
	fila = fila_insert_node(fila, fila_make_node(5, NULL));
	fila = fila_insert_node(fila, fila_make_node(4, NULL));

	int id = fila_max_id(fila);
	
	if (id != 5)
		return 0;

	return 1;
}

int teste_fila_free(void)
{
	Fila *fila = fila_make_node(2, NULL);
	fila = fila_free(fila);

	if (fila != NULL)
		return 0;

	return 1;
}
