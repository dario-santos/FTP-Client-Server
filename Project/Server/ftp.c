#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ftp.h"
#include "fifo.h"

void ftp_handle(Connection *connection)
{
    char buf[BUFSIZ];
    int request_filefd = -1;
    int n;

    if ((n = read(connection->fifocfd, buf, BUFSIZ)) == -1)
        return;

    buf[n] = '\0';

    if (ftp_valid_filepath(connection, buf, &request_filefd))
        ftp_send(*connection, request_filefd);
}

int ftp_valid_filepath(Connection *connection, char *filepath, int *request_filefd)
{
    int resposta = -1;
    int pedido = -1;

    // Não é do diretório
    if (strncmp(PATH_CURRENT, filepath, strlen(PATH_CURRENT)) != 0)
    {
        resposta = -1;
        write(connection->fifosfd, &resposta, sizeof(int));
        return 0;
    }

    // Se for privado
    if (strncmp(PATH_SECRET, filepath, strlen(PATH_SECRET)) == 0)
    {
        resposta = 0;
        // Pede a pass ao utilizador
        if (write(connection->fifosfd, &resposta, sizeof(int)) == -1)
        {
            return 0;
        }

        // Lê a palavra passe
        if (read(connection->fifocfd, &pedido, sizeof(int)) == -1)
            return 0;
        
        if (PASSWORD != pedido)
        {
            resposta = -1;
            write(connection->fifosfd, &resposta, sizeof(int));
            return 0;
        }
        else if (resposta == 1)
        {
            if (write(connection->fifosfd, &resposta, sizeof(int)) == -1)
                return 0;
        }
    }

    // Se o ficheiro não existe
    if ((*request_filefd = open(filepath, O_RDONLY)) == -1)
    {
        resposta = -2;
        write(connection->fifosfd, &resposta, sizeof(int));
        return 0;
    }

    // Se tudo correr bem
    resposta = 1;
    if (write(connection->fifosfd, &resposta, sizeof(int)) == -1)
        return 0;

    return 1;
}

void ftp_send(Connection connection, int request_filefd)
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(request_filefd, buf, BUFSIZ)) > 0)
        if (write(connection.fifosfd, buf, n) != n)
            break;
            
    close(request_filefd);
}
