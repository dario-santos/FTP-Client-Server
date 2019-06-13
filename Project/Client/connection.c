#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "connection.h"

#define FIFOS "/tmp/FIFOS.%d"
#define FIFOC "/tmp/FIFOC.%d"

#define ERROR -1

int connection_can_connect(int readfd, int writefd)
{
    int request = 1;
    int answer = -1;

    write(writefd, &request, sizeof(int));

    read(readfd, &answer, sizeof(int));

    printf("Client: Channel ID - %d\n", request);

    if(request == -1)
        printf("Error: Server can't handle connections at the momment.\n");
    
    return request;
}

void connection_open(Connection *connection, int index)
{
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
        perror("Error Closing connection : FIFOC");

    if (close(connection->fifosfd) == ERROR)
        perror("Error Closing connection : FIFOS");
}
