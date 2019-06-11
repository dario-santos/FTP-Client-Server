#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "send_struct.h"
#include "connection.h"
#include "server.h"
#include "ftp.h"
#include "fila.h"
#include "fifo.h"

MainConnection *mainConnection;
Connection *connections;
Fila *filas = NULL;
int *available_connections;
sem_t sem_msg;

void do_nothing(int signum)
{
}

int shutdown_main_thread()
{
    int size = MAX_CONNECTIONS;
    int i;

    // Se tiver alguem conectado não pode desligar
    for (i = 0; i < size; i++)
        if (available_connections[i] == 1)
            return 0;

    fila_free(filas);

    pthread_cancel(mainConnection->thread_id);
    printf("Server: Shutting server down.\n");

    // Descansa para garantir que desliga bem
    sleep(5);

    return 1;
}

void *operation(void *args)
{
    Connection *connection = (Connection *)args;
    int pedido = -1;

    // Receber comando do cliente
    if (read(connection->fifocfd, &pedido, sizeof(int)) == -1)
    {
        connection_close(connection, available_connections);
        return NULL;
    }

    switch (pedido)
    {
    case 0:
    default:
        connection_close(connection, available_connections);
        break;
    case 1:
        ftp_handle(connection);
        connection_close(connection, available_connections);
        break;
    case 2:
        sem_wait(&sem_msg);
        send_handle(connection, &filas);
        connection_close(connection, available_connections);
        sem_post(&sem_msg);
        break;
    }

    return NULL;
}

void *server(void *args)
{
    printf("Server On.\n");
    signal(SIGPIPE, do_nothing);

    int resposta = -1;
    int pedido = 0;
    int index;
    available_connections = (int *)calloc(MAX_CONNECTIONS, sizeof(int));
    mainConnection = (MainConnection *)args;
    connections = (Connection *)malloc(MAX_CONNECTIONS * sizeof(Connection));

    sem_init(&sem_msg, 0, 1);

    while (true)
    {
        // Receber pedido de comunicação
        if (read(mainConnection->readfd, &pedido, sizeof(int)) <= 0)
            continue;

        // Tentar estabelecer comunicação
        index = can_connect(available_connections, MAX_CONNECTIONS);
        if (index != -1)
        {
            // Criar conexão
            connections[index].index = index;
            connection_open(mainConnection->writefd, &connections[index], &available_connections[index]);

            pthread_create(&connections->thread_id, NULL, operation, &connections[index]);
            pthread_detach(connections->thread_id);
        }
        else
        {
            write(mainConnection->writefd, &resposta, sizeof(int));
        }
    }
}