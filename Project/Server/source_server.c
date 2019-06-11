#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "server.h"
#include "fifo.h"

void server_kill();

int main(void)
{
    umask(0);
    MainConnection mainConnection;

    //Cria os FIFOS de comunicação
    if (mkfifo(FIFO_COM_C, 0666) == ERROR)
    {
        perror("Error creating fifo - FIFO_COM_C ");
        return -1;
    }
    if (mkfifo(FIFO_COM_S, 0666) == ERROR)
    {
        perror("Error creating fifo - FIFO_COM_S ");
        return -1;
    }

    // Abre as comunicações
    mainConnection.readfd = open(FIFO_COM_C, O_RDONLY);
    mainConnection.writefd = open(FIFO_COM_S, O_WRONLY);

    if (mainConnection.readfd == ERROR || mainConnection.writefd == ERROR)
    {
        perror("Error creating connections ");
        return -1;
    }

    // Inicia o servidor
    pthread_create(&mainConnection.thread_id, NULL, server, &mainConnection);
    pthread_detach(mainConnection.thread_id);

    // Espera pelo comando para terminar
    server_kill();

    // Fecha as comunicações
    close(mainConnection.readfd);
    close(mainConnection.writefd);

    // Fecha os FIFOS de comunicação
    unlink(FIFO_COM_S);
    unlink(FIFO_COM_C);

    return 0;
}

// ToDo: Terminar todas as threads
void server_kill()
{
    char c = 'a';
    do
    {
        scanf("%c", &c);

        if (shutdown_main_thread() != 1)
        {
            printf("Server: Não pode desligar o servidor enquanto existem clientes ligados\n");
            c = 'a';
        }

    } while (c != 'q');
}
