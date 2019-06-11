#include "request_struct.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int request_fila(Connection connection)
{
    int id;

    printf("Lista de filas (id):\n");

    while (read(connection.fifosfd, &id, sizeof(id)) > 0)
    {
        if (id == -1)
            break;

        printf("id: %d\n", id);
    }

    printf("Fim da fila\n");

    return 0;
}

int request_fila_add(Connection connection)
{
    int id;

    read(connection.fifosfd, &id, sizeof(id));

    printf("Id da nova fila criada: %d\n", id);

    return 0;
}

int request_fila_msg(Connection connection)
{
    int id = 0;
    int erro = -1;

    printf("Insira o id que pretende procurar: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Input invalido, a terminar ligação\n");
        return -1;
    }

    //Envia id ao servidor
    write(connection.fifocfd, &id, sizeof(id));

    read(connection.fifosfd, &erro, sizeof(erro));
    if (erro == -1)
    {
        printf("A fila requisitada não existe.\n");
        return -1;
    }

    printf("Lista de msg (id):\n");

    while (read(connection.fifosfd, &id, sizeof(id)) > 0)
    {
        if (id == -1)
            break;

        printf("id: %d\n", id);
    }

    printf("Fim da fila\n");

    return 0;
}

int request_msg_content(Connection connection)
{
    char str[BUFSIZ];
    int id = 0;
    int n = 0;
    int erro = -1;

    // Id da fila
    printf("Insira o id da fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Input invalido, a terminar ligação\n");
        return -1;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(erro));
    if (erro == -1)
    {
        printf("A fila requisitada não existe.\n");
        return -1;
    }

    //id da Mensagem
    printf("Insira o id da mensagem pretendida: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Input invalido, a terminar ligação\n");
        return -1;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(int));
    if (erro == -1)
    {
        printf("Client: A mensagem requisitada não existe.\n");
        return -1;
    }

    n = read(connection.fifosfd, str, BUFSIZ);
    str[n] = '\0';

    printf("O conteudo da mensagem %d é: %s\n", id, str);

    return 0;
}

int request_msg_add(Connection connection)
{
    char conteudo[512];
    int id = 0;
    int erro = -1;

    // Id da fila
    printf("Insira o id da fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Client: Input invalido, a terminar ligação\n");
        return -1;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(erro));
    if (erro == -1)
    {
        printf("Clinet: A fila requisitada não existe.\n");
        return -1;
    }

    // Content da mensagem
    printf("Insira o conteudo da mensagem: ");
    scanf("%s", conteudo);
    //enviar
    write(connection.fifocfd, conteudo, strlen(conteudo));

    printf("Client: Mensagem adicionada\n");
    return 0;
}

int request_msg_remove(Connection connection)
{
    int id = 0;
    int erro = -1;

    // Id da fila
    printf("Insira o id da fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Input invalido, a terminar ligação\n");
        return -1;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(erro));
    if (erro == -1)
    {
        printf("A fila requisitada não existe.\n");
        return -1;
    }

    //id da Mensagem
    printf("Insira o id da mensagem pretendida: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Input invalido, a terminar ligação\n");
        return -1;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(int));
    if (erro == -1)
    {
        printf("Client: A mensagem requisitada não existe.\n");
        return -1;
    }

    printf("Client: Mensagem removida\n");
    return 0;
}
