#include <stdio.h>
#include <unistd.h>
#include "menu.h"
#include "fifo.h"
#include "ftp.h"
#include "request_struct.h"

int menu_handle_main(Connection connection)
{
    int request = menu_show_main();
    menu_request_main(connection, request);

    return 0;
}

int menu_show_main(void)
{
    int pedido;
    do
    {
        printf("Client Menu\n");
        printf("1 - Receber Ficheiro do Servidor.\n");
        printf("2 - Operar mensagens.\n");
        printf("\n");
        printf("0 - Sair.\n");
        printf("Opcao: ");

        if (scanf("%d", &pedido) != 1)
        {
            printf("Aborting connection - please enter an integer\n");
            return 0;
        }

    } while (pedido != 1 && pedido != 2 && pedido != 0);

    return pedido;
}

int menu_request_main(Connection connection, int request)
{
    switch (request)
    {
    case 0:
    default:
        request = 0;
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        break;

    case 1:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        ftp_request(connection);
        break;

    case 2:
        //Manda o pedido ao servidor
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
        printf("1 - Filas existentes.\n");
        printf("2 - Adicionar uma fila.\n");
        printf("3 - Visualizar msg de uma fila.\n");
        printf("4 - Ver conteudo de uma msg.\n");
        printf("5 - Adicionar msg a uma fila.\n");
        printf("6 - Remover msg de uma fila\n");
        printf("\n");
        printf("0 - Sair.\n");
        printf("Opcao: ");

        if (scanf("%d", &request) != 1)
        {
            printf("Aborting connection - please enter an integer\n");
            return 0;
        }

    } while (!(request >= 0 && request <=6));

    return request;
}

int menu_request_msg(Connection connection, int request)
{   
    switch (request)
    {
    case 0:
    default:
        request = 0;
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        break;

    case 1:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        request_fila(connection);
        break;

    case 2:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        request_fila_add(connection);
        break;
    case 3:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        request_fila_msg(connection);
        break;
    case 4:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        request_msg_content(connection);
        break;
    case 5:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        request_msg_add(connection);
        break;
    case 6:
        //Manda o pedido ao servidor
        write(connection.fifocfd, &request, sizeof(int));
        request_msg_remove(connection);
        break;
    }
    return 0;
}