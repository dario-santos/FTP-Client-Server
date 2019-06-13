#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "send_struct.h"
#include "connection.h"
#include "server.h"
#include "fila.h"
#include "MainConnection.h"
#include "lock.h"
#include "ftp.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

Fila *filas = NULL;

void do_nothing(int signum)
{
}

int shutdown_main_thread(pthread_t thread_id)
{
    // Can't shutdown if there are clients connected
    if (connection_can_connect() != 0)
        return FALSE;

    fila_free(filas);
    connection_free();
    locks_free();

    // Ends the main thread as fast as possible
    pthread_cancel(thread_id);
    printf("Server: Shutting server down.\n");

    // Waits 5 seconds to secure a safe shutdown
    sleep(5);

    return TRUE;
}

void *operation(void *args)
{
    Connection *connection = (Connection *)args;
    int pedido = -1;

    // Receber comando do cliente
    if (read(connection->fifocfd, &pedido, sizeof(int)) == ERROR)
    {
        connection_close(connection->index);
        return NULL;
    }

    switch (pedido)
    {
    case 0:
    default:
        connection_close(connection->index);
        break;
    case 1:
        ftp_handle(connection);
        connection_close(connection->index);
        break;
    case 2:
        send_handle(connection, &filas);
        connection_close(connection->index);
        break;
    }

    return NULL;
}

void *server(void *args)
{
    MainConnection *mainConnection = (MainConnection *)args;
    int resposta = -1;
    int pedido = 0;
    int index = 0;

    signal(SIGPIPE, do_nothing);

    locks_sem_init();
    connection_init();

    printf("Server: Online.\n");

    while (TRUE)
    {
        // Waits for client request
        if (read(mainConnection->readfd, &pedido, sizeof(int)) <= 0)
            continue;

        // Tries to open channel
        index = connection_can_connect();
        if (index != ERROR)
        {
            // Opens communication channel
            connection_open(mainConnection->writefd, index);
            pthread_create(&get_connection_info(index)->thread_id, NULL, operation, get_connection_info(index));
            pthread_detach(get_connection_info(index)->thread_id);
        }
        else
        {
            // Sends failure error
            write(mainConnection->writefd, &resposta, sizeof(int));
        }
    }
}