#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "menu.h"

#define FIFO_COM_S "/tmp/FIFO_COM_S.X"
#define FIFO_COM_C "/tmp/FIFO_COM_C.X"

#define ERROR -1

int main(void)
{
    umask(0);
    
    Connection connection;
    int status = ERROR;

    // Opens HandShake communications
    int writefd = open(FIFO_COM_C, O_WRONLY);
    int readfd = open(FIFO_COM_S, O_RDONLY);

    // Sends a connection request
    if (readfd == ERROR || writefd == ERROR)
    {
        perror("Error: No server found.");
        return ERROR;
    }

    // Receives answer from Server 
    status = connection_can_connect(readfd, writefd);
    
    if(status != ERROR)
    {
        connection_open(&connection, status);
        printf("Client: Conectado ao servidor.\n");
        menu_handle_main(connection);
        connection_close(&connection);
    }

    // Closes HandShake communications
    close(readfd);
    close(writefd);
    return 0;
}
