#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "connection.h"

static int *connections_status = NULL;
static int connections_status_size = 0;

void connection_init(void)
{
    connections_status_size = MAX_CONNECTIONS;
    connections_status = (int *)calloc(connections_status_size, sizeof(int));
}

int connection_can_connect(void)
{
    int i = 0;
    for (i = 0; i < connections_status_size; i++)
        if (connections_status[i] == 0)
            return i;

    return -1;
}

void connection_open(int writefd, Connection *connection, int index)
{
    snprintf(connection->fifoc_path, 20, FIFOC, connection->index);
    snprintf(connection->fifos_path, 20, FIFOS, connection->index);

    //Cria a nova conexão
    //mkfifo(connection->fifos_path, 0666);
    //mkfifo(connection->fifoc_path, 0666);

    //Envia a informação da conexão ao cliente
    //write(writefd, &connection->index, sizeof(int));

    //Abre a nova conexão
    //connection->fifocfd = open(connection->fifoc_path, O_RDONLY);
    //connection->fifosfd = open(connection->fifos_path, O_WRONLY);

    //Informa o servidor que esta conexão está bloqueada
    connections_status[index] = 1;
}

void connection_close(Connection *connection)
{
    // Fecha as comunicações
    close(connection->fifosfd);
    close(connection->fifocfd);

    // Fecha os FIFOS de comunicação
    unlink(connection->fifos_path);
    unlink(connection->fifoc_path);

    connections_status[connection->index] = 0;
}