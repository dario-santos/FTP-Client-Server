#include <stdio.h>
#include <stdlib.h>
#include "connection.h"

int teste_connection_init(void);

int main(void)
{
    teste_connection_init();

    return 1;
}

int teste_connection_init(void)
{
    connection_init();
    int teste = connection_can_connect();
    printf("%d \n", teste);

    return 1;
}
