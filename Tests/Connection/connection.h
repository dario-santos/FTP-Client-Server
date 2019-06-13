#ifndef CONNECTION_H
#define CONNECTION_H

#include <pthread.h>

#define MAX_CONNECTIONS 10

typedef struct CONNECTION
{
    int index;
    int fifosfd;
    int fifocfd;
    char fifos_path[20];
    char fifoc_path[20];
    pthread_t thread_id;

} Connection;


/*
 * return index disponivel ou -1 em caso de erro
 */
int connection_can_connect(void);

void connection_init(void);

void connection_open(int writefd, Connection *connection, int index);

void connection_close(Connection *connection);

#endif // CONNECTION_H