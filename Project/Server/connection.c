#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "fifo.h"
#include "connection.h"

int can_connect(int *L, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
        if (L[i] == 0)
            return i;

    return -1;
}

void connection_open(int writefd, Connection *connection, int *available_connection)
{
    snprintf(connection->fifoc_path, 20, FIFOC, connection->index);
    snprintf(connection->fifos_path, 20, FIFOS, connection->index);

    //Cria a nova conexão
    mkfifo(connection->fifos_path, 0666);
    mkfifo(connection->fifoc_path, 0666);

    //Envia a informação da conexão ao cliente
    write(writefd, &connection->index, sizeof(int));

    //Abre a nova conexão
    connection->fifocfd = open(connection->fifoc_path, O_RDONLY);
    connection->fifosfd = open(connection->fifos_path, O_WRONLY);

    //Informa o servidor que esta conexão está bloqueada
    *available_connection = 1;
}

void connection_close(Connection *connection, int *available_connections)
{
    // Fecha as comunicações
    close(connection->fifosfd);
    close(connection->fifocfd);

    // Fecha os FIFOS de comunicação
    unlink(connection->fifos_path);
    unlink(connection->fifoc_path);

    available_connections[connection->index] = 0;
}