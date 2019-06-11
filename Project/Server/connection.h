#ifndef CONNECTION_H
#define CONNECTION_H

#include <pthread.h>

#define MAX_CONNECTIONS 10

typedef struct CONNECTION
{
    int index;
    int fifosfd;
    int fifocfd;
    pthread_t thread_id;
    char fifos_path[20];
    char fifoc_path[20];

} Connection;


/*
* return index disponivel ou -1 em caso de erro
*/
int can_connect(int *L, int size);

void connection_open(int writefd, Connection *connection, int *available_connection);

void connection_close(Connection *connection, int *available_connections);




#endif // CONNECTION_H