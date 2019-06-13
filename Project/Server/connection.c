#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "connection.h"

#define FIFOS "/tmp/FIFOS.%d"
#define FIFOC "/tmp/FIFOC.%d"

#define MAX_CONNECTIONS 10

static int *connections_status = NULL;
static int connections_status_size = 0;

static Connection *connections_info = NULL;
static int connections_info_size = 0;

void connection_init(void)
{
    connections_status_size = MAX_CONNECTIONS;
    connections_status = (int *)calloc(connections_status_size, sizeof(int));

    connections_info_size = MAX_CONNECTIONS;
    connections_info = (Connection *)malloc(connections_info_size * sizeof(Connection));
}

Connection *get_connection_info(int index)
{
    return &connections_info[index];
}

int connection_can_connect(void)
{
    int i = 0;
    for (i = 0; i < connections_status_size; i++)
        if (connections_status[i] == 0)
            return i;

    return -1;
}

void connection_open(int writefd, int index)
{
    connections_info[index].index = index;

    snprintf(connections_info[index].fifoc_path, 20, FIFOC, index);
    snprintf(connections_info[index].fifos_path, 20, FIFOS, index);

    //Cria a nova conexão
    mkfifo(connections_info[index].fifos_path, 0666);
    mkfifo(connections_info[index].fifoc_path, 0666);

    //Envia a informação da conexão ao cliente
    write(writefd, &index, sizeof(int));

    //Abre a nova conexão
    connections_info[index].fifocfd = open(connections_info[index].fifoc_path, O_RDONLY);
    connections_info[index].fifosfd = open(connections_info[index].fifos_path, O_WRONLY);

    //Informa o servidor que esta conexão está bloqueada
    connections_status[index] = 1;
}

void connection_close(int index)
{
    // Fecha as comunicações
    close(connections_info[index].fifosfd);
    close(connections_info[index].fifocfd);

    // Fecha os FIFOS de comunicação
    unlink(connections_info[index].fifos_path);
    unlink(connections_info[index].fifoc_path);

    connections_status[index] = 0;
}

void connection_free(void)
{
    free(connections_status);
    connections_status_size = 0;
    free(connections_info);
    connections_info_size = 0;
}
