#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "server.h"
#include "MainConnection.h"

#define FIFO_COM_S "/tmp/FIFO_COM_S.X"
#define FIFO_COM_C "/tmp/FIFO_COM_C.X"

#define ERROR -1

void server_kill(pthread_t thread_id);

int main(void)
{
    umask(0);
    MainConnection mainConnection;

    // Creates the HandShake FIFOS
    if (mkfifo(FIFO_COM_C, 0666) == ERROR)
    {
        perror("Error creating fifo - FIFO_COM_C ");
        return ERROR;
    }
    if (mkfifo(FIFO_COM_S, 0666) == ERROR)
    {
        perror("Error creating fifo - FIFO_COM_S ");
        return ERROR;
    }

    // Opens the HandShake communications
    mainConnection.readfd = open(FIFO_COM_C, O_RDONLY);
    mainConnection.writefd = open(FIFO_COM_S, O_WRONLY);

    if (mainConnection.readfd == ERROR || mainConnection.writefd == ERROR)
    {
        perror("Error creating connections ");
        return ERROR;
    }

    // Starts the Server
    pthread_create(&mainConnection.thread_id, NULL, server, &mainConnection);
    pthread_detach(mainConnection.thread_id);

    server_kill(mainConnection.thread_id);

    // Closes the HandShake communications
    close(mainConnection.readfd);
    close(mainConnection.writefd);

    // Deletes the HandShake FIFOS
    unlink(FIFO_COM_S);
    unlink(FIFO_COM_C);

    return 0;
}

void server_kill(pthread_t pthread_id)
{
    char c = 'a';
    do
    {
        scanf("%c", &c);
        if (c == 'q')
            if (shutdown_main_thread(pthread_id) != 1)
            {
                printf("Server: Can't shutdown because there are still clients connected to the server.\n");
                c = 'a';
            }

    } while (c != 'q');
}
