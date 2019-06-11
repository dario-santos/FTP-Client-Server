#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "fifo.h"
#include "menu.h"

int main(void)
{
    umask(0);
    
    Connection connection;
    int status = ERROR;

    // Abre as comunicações
    int writefd = open(FIFO_COM_C, O_WRONLY);
    int readfd = open(FIFO_COM_S, O_RDONLY);

    if (readfd == ERROR || writefd == ERROR)
    {
        perror("Error: No server found.");
        return -1;
    }
    // Comunicação com o servidor
    status = can_connect(readfd, writefd);
    
    if(status != ERROR)
    {
        connection_open(&connection, status);
        printf("Client: Conectado ao servidor.\n");
        menu_handle_main(connection);
        connection_close(&connection);
    }

    // Fecha as comunicações
    close(readfd);
    close(writefd);
    return 0;
}
