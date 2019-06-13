#include <stdio.h>
#include <unistd.h>
#include "request_struct.h"
#include "menu.h"
#include "ftp.h"

int menu_handle_main(Connection connection)
{
    int request = menu_show_main();
    menu_request_main(connection, request);

    return 0;
}

int menu_show_main(void)
{
    int request;
    do
    {
        printf("Client Menu\n");
        printf("1 - Request File to Server.\n");
        printf("2 - Operate the Data Structures.\n");
        printf("\n");
        printf("0 - Exit.\n");
        printf("Option: ");

        if (scanf("%d", &request) != 1)
        {
            printf("Aborting connection - please enter an integer\n");
            return 0;
        }

    } while (request != 1 && request != 2 && request != 0);

    return request;
}

int menu_request_main(Connection connection, int request)
{
    switch (request)
    {
    case 0:
    default:
        request = 0;
        write(connection.fifocfd, &request, sizeof(int));
        break;

    case 1:
        write(connection.fifocfd, &request, sizeof(int));
        ftp_request(connection);
        break;

    case 2:
        write(connection.fifocfd, &request, sizeof(int));
        menu_handle_msg(connection);
        break;
    }
    return 0;
}

int menu_handle_msg(Connection connection)
{
    int request = menu_show_msg();
    menu_request_msg(connection, request);

    return 0;
}

int menu_show_msg(void)
{
    int request;
    do
    {
        printf("Client Msg Menu\n");
        printf("1 - Request Fila Ids.\n");
        printf("2 - Add new Fila.\n");
        printf("3 - Visualize Msg Ids of Fila.\n");
        printf("4 - Visualize content of a Msg.\n");
        printf("5 - Add Msg to Fila.\n");
        printf("6 - Remove Msg from Fila\n");
        printf("\n");
        printf("0 - Exit.\n");
        printf("Option: ");

        if (scanf("%d", &request) != 1)
        {
            printf("Aborting connection - please enter an integer\n");
            return 0;
        }

    } while (!(request >= 0 && request <= 6));

    return request;
}

int menu_request_msg(Connection connection, int request)
{
    switch (request)
    {
    case 0:
    default:
        request = 0;
        write(connection.fifocfd, &request, sizeof(int));
        break;

    case 1:
        write(connection.fifocfd, &request, sizeof(int));
        request_fila(connection);
        break;

    case 2:
        write(connection.fifocfd, &request, sizeof(int));
        request_fila_add(connection);
        break;

    case 3:
        write(connection.fifocfd, &request, sizeof(int));
        request_fila_msg(connection);
        break;

    case 4:
        write(connection.fifocfd, &request, sizeof(int));
        request_msg_content(connection);
        break;

    case 5:
        write(connection.fifocfd, &request, sizeof(int));
        request_msg_add(connection);
        break;

    case 6:
        write(connection.fifocfd, &request, sizeof(int));
        request_msg_remove(connection);
        break;
    }
    return 0;
}