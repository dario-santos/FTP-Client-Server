#ifndef CONNECTION_H
#define CONNECTION_H

#define CONNECTION_FIFO_PATH_SIZE 20

typedef struct CONNECTION
{
    int fifosfd;
    int fifocfd;
    char fifos_path[CONNECTION_FIFO_PATH_SIZE];
    char fifoc_path[CONNECTION_FIFO_PATH_SIZE];

} Connection;

int can_connect(int readfd, int writefd);

void connection_open(Connection *connection, int index);

void connection_close(Connection *connection);

#endif // CONNECTION_H