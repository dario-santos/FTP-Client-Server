#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "request_struct.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

int request_fila(Connection connection)
{
    int id;

    printf("Fila list (id):\n");

    while (read(connection.fifosfd, &id, sizeof(id)) > 0)
    {
        if (id == ERROR)
            break;

        printf("id: %d\n", id);
    }

    printf("End of list\n");

    return TRUE;
}

int request_fila_add(Connection connection)
{
    int id;

    read(connection.fifosfd, &id, sizeof(id));
    if(id == ERROR)
    {
        printf("There's a user in the requested node.\n");
        return FALSE;
    }
    printf("Id of the new Fila: %d\n", id);

    return TRUE;
}

int request_fila_msg(Connection connection)
{
    int erro = -1;
    int id = 0;


    printf("Insert the id of the Fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input, closing connection.\n");
        return FALSE;
    }

    // Sends FilaId
    write(connection.fifocfd, &id, sizeof(id));

    read(connection.fifosfd, &erro, sizeof(erro));
    if (erro == ERROR)
    {
        printf("The Fila does not exist or is being used by another client.\n");
        return FALSE;
    }

    printf("Msg list:\n");

    while (read(connection.fifosfd, &id, sizeof(id)) > 0)
    {
        if (id == ERROR)
            break;

        printf("id: %d\n", id);
    }

    printf("End of Msg\n");

    return TRUE;
}

int request_msg_content(Connection connection)
{
    char str[BUFSIZ];
    int id = 0;
    int n = 0;
    int erro = -1;

    printf("Insert the id of Fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input, closing connection.\n");
        return FALSE;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(erro));
    if (erro == ERROR)
    {
        printf("The Fila does not exist or is being used by another client.\n");
        return FALSE;
    }

    printf("Insert the id of the Msg: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input, closing connection.\n");
        return FALSE;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &erro, sizeof(int));
    if (erro == ERROR)
    {
        printf("The Msg does not exist.\n");
        return FALSE;
    }

    n = read(connection.fifosfd, str, BUFSIZ);
    str[n] = '\0';

    printf("The content of the %d msg is %s\n", id, str);

    return TRUE;
}

int request_msg_add(Connection connection)
{
    char content[512];
    int id = 0;
    int error = -1;

    printf("Insert the id of Fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input, closing connection.\n");
        return FALSE;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &error, sizeof(int));
    if (error == ERROR)
    {
        printf("The Fila does not exist or is being used by another client.\n");
        return FALSE;
    }

    printf("Insert the content of the Msg: ");
    scanf("%s", content);

    write(connection.fifocfd, content, strlen(content));

    printf("Msg Added.\n");

    return TRUE;
}

int request_msg_remove(Connection connection)
{
    int id = 0;
    int error = -1;

    printf("Insert the id of Fila: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input, closing connection.\n");
        return FALSE;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &error, sizeof(int));
    if (error == ERROR)
    {
        printf("The Fila does not exist or is being used by another client.\n");
        return FALSE;
    }

    printf("Insert the id of the Msg: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input, closing connection.\n");
        return FALSE;
    }
    write(connection.fifocfd, &id, sizeof(int));

    read(connection.fifosfd, &error, sizeof(int));
    if (error == ERROR)
    {
        printf("The Msg does not exist.\n");
        return FALSE;
    }

    printf("Msg Removed.\n");
    return TRUE;
}
