#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "ftp.h"

void ftp_request(Connection connection)
{
    char str[BUFSIZ];
    int resposta = -1;
    int pedido = -1;
    int n = 0;

    printf("Menu Ficheiro\n");
    printf("Insira o nome do ficheiro a descarregar: ");
    scanf("%s", str);

    // Envia o nome do ficheiro
    write(connection.fifocfd, str, sizeof(str));

    // Receber resposta
    read(connection.fifosfd, &resposta, sizeof(int));

    if (resposta == -1)
    {
        printf("Client: Erro apenas pode receber ficheiros da raiz do servidor\n");
        printf("Client: Por favor utilize ./\n");
        return;
    }
    if (resposta == 0)
    {
        printf("Client: O ficheiro que está a tentar aceder é privado\n");
        printf("Client: Por favor insira a palavra passe: ");
        printf("Palavra-pass: ");
        scanf("%d", &pedido);

        // Manda a pass
        write(connection.fifocfd, &pedido, sizeof(int));

        // Recebe a reposta
        read(connection.fifosfd, &resposta, sizeof(int));

        if (resposta == -1)
        {
            printf("Client: Palavra passe incorreta\n");
            return;
        }
    }

    if (resposta == -2)
    {
        printf("Client: O ficheiro não existe\n");
        return;
    }

    // Cria o ficheiro no cliente
    int fd = creat("received.txt", 0666);

    while ((n = read(connection.fifosfd, str, BUFSIZ)) > 0)
    {
        str[n] = '\0';
        write(fd, str, strlen(str));
    }
    if (n < 0)
        perror("Error receiving file");

    printf("Client: Ficheiro Recebido.\n");
    close(fd);
}