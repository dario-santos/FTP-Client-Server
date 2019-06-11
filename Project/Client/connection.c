#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "connection.h"
#include "fifo.h"

int can_connect(int readfd, int writefd)
{
    int pedido = 1;
    int resposta = -1;
    // Informa servidor que este cliente se quer conectar
    write(writefd, &pedido, sizeof(int));

    // Recebe a resposta do cliente -1 em caso de erro
    read(readfd, &resposta, sizeof(int));

    printf("Client: id do canal - %d\n", resposta);
    return resposta;
}

void connection_open(Connection *connection, int index)
{
    //ToDo: snprintf sprintf
    snprintf(connection->fifoc_path, 20, FIFOC, index);
    snprintf(connection->fifos_path, 20, FIFOS, index);

    connection->fifocfd = open(connection->fifoc_path, O_WRONLY);
    connection->fifosfd = open(connection->fifos_path, O_RDONLY);

    if (connection->fifocfd == ERROR)
        perror("Error creating read communication : fifocfd ");

    if (connection->fifosfd == ERROR)
        perror("Error creating read communication : fifosfd ");
}

void connection_close(Connection *connection)
{
    if (close(connection->fifocfd) == ERROR)
        perror("Closing connection - FIFOC");

    if (close(connection->fifosfd) == ERROR)
        perror("Closing connection - FIFOS");
}
