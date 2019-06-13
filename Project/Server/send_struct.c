#include <unistd.h>
#include <string.h>
#include "send_struct.h"
#include "lock.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

int send_handle(Connection *connection, Fila **filas)
{
    int request = -1;
    int status = 0;

    if (read(connection->fifocfd, &request, sizeof(int)) == ERROR)
        return FALSE;

    switch (request)
    {
    case 0:
    default:
        break;
    case 1:
        status = send_fila(*connection, *filas);
        break;
    case 2:
        status = send_fila_add(*connection, filas);
        break;
    case 3:
        status = send_fila_msg(*connection, *filas);
        break;
    case 4:
        status = send_msg_content(*connection, *filas);
        break;
    case 5:
        status = send_msg_add(*connection, filas);
        break;
    case 6:
        status = send_msg_remove(*connection, filas);
        break;
    }

    return status;
}

int send_fila(Connection connection, Fila *L)
{
    Fila *aux = L;
    int answer = ERROR;

    // Sends the filaIds
    while (aux != NULL)
    {
        if (write(connection.fifosfd, &aux->id, sizeof(aux->id)) == ERROR)
        {
            write(connection.fifosfd, &answer, sizeof(int));
            return FALSE;
        }
        aux = aux->p_seg;
    }

    // Informs the client that the list was ended (-1)
    if (write(connection.fifosfd, &answer, sizeof(int)) == ERROR)
    {
        write(connection.fifosfd, &answer, sizeof(int));
        return FALSE;
    }
    return TRUE;
}

int send_fila_add(Connection connection, Fila **L)
{
    int id = fila_max_id(*L) + 1;
    int error = ERROR;

    if (id - 1 > 0)
        if (!locks_lock_node(id - 2))
        {
            write(connection.fifosfd, &error, sizeof(int));
            return FALSE;
        }

    *L = fila_insert_node(*L, fila_make_node(id, NULL));
    locks_insert_node();

    if (write(connection.fifosfd, &id, sizeof(int)) == ERROR)
    {
        locks_unlock_node(id - 2);
        return FALSE;
    }

    locks_unlock_node(id - 2);
    return TRUE;
}

int send_fila_msg(Connection connection, Fila *L)
{
    Fila *fila = NULL;
    Msg *aux = NULL;
    int resposta = ERROR;
    int erro = ERROR;
    int id = 0;

    // Receives the filaId
    if (read(connection.fifocfd, &id, sizeof(int)) == ERROR)
        return FALSE;

    if (!locks_lock_node(id - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
            return FALSE;
        if (erro == ERROR)
            return FALSE;
    }

    fila = fila_find_node(L, id);
    erro = fila == NULL ? ERROR : 1;

    if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
    {
        locks_unlock_node(id - 1);
        return FALSE;
    }

    if (erro == ERROR)
    {
        locks_unlock_node(id - 1);
        return FALSE;
    }

    aux = fila->mensagens;

    // Sends the msgIds
    while (aux != NULL)
    {
        if (write(connection.fifosfd, &aux->id, sizeof(int)) == ERROR)
        {
            locks_unlock_node(id - 1);
            return FALSE;
        }

        aux = aux->p_seg;
    }

    // Informs the client that there are no more ids
    if (write(connection.fifosfd, &resposta, sizeof(int)) == ERROR)
    {
        locks_unlock_node(id - 1);
        return FALSE;
    }

    locks_unlock_node(id - 1);
    return TRUE;
}

int send_msg_content(Connection connection, Fila *L)
{
    int filaId = 0;
    int msgId = 0;
    int erro = -1;
    Fila *fila = NULL;
    Msg *msg = NULL;

    // Receives the filaId
    if (read(connection.fifocfd, &filaId, sizeof(int)) == ERROR)
        return FALSE;

    if (!locks_lock_node(filaId - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
            return FALSE;
        if (erro == ERROR)
            return FALSE;
    }

    fila = fila_find_node(L, filaId);
    erro = fila == NULL ? ERROR : 1;

    if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }
    if (erro == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    // Receives the msgId
    if (read(connection.fifocfd, &msgId, sizeof(int)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    msg = msg_find_node(fila->mensagens, msgId);
    erro = msg == NULL ? ERROR : 1;

    if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    if (erro == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    // Sends content
    if (write(connection.fifosfd, msg->content, strlen(msg->content)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    locks_unlock_node(filaId - 1);
    return TRUE;
}

int send_msg_add(Connection connection, Fila **L)
{
    Fila *fila = NULL;
    char content[CONTENT_SIZE];
    int filaId = 0;
    int msgId = 0;
    int erro = -1;
    int n = 0;

    // Receives filaId
    if (read(connection.fifocfd, &filaId, sizeof(int)) == ERROR)
        return FALSE;

    if (!locks_lock_node(filaId - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
            return FALSE;
        if (erro == ERROR)
            return FALSE;
    }

    fila = fila_find_node(*L, filaId);
    erro = fila == NULL ? ERROR : 1;

    if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }
    if (erro == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    // Receives the Msg content
    if ((n = read(connection.fifocfd, content, CONTENT_SIZE - 1)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    content[n] = '\0';
    msgId = msg_max_id(fila->mensagens) + 1;
    fila->mensagens = msg_insert_node(fila->mensagens, msg_make_node(msgId, content));

    locks_unlock_node(filaId - 1);
    return TRUE;
}

int send_msg_remove(Connection connection, Fila **L)
{
    int filaId = -1;
    int msgId = -1;
    int erro = -1;
    Fila *fila = *L;

    // Receives filaId
    if (read(connection.fifocfd, &filaId, sizeof(int)) == ERROR)
        return FALSE;

    if (!locks_lock_node(filaId - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
            return FALSE;
        if (erro == ERROR)
            return FALSE;
    }

    fila = fila_find_node(*L, filaId);
    erro = fila == NULL ? ERROR : 1;

    if (write(connection.fifosfd, &erro, sizeof(erro)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }
    if (erro == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    // Receives msgId
    if (read(connection.fifocfd, &msgId, sizeof(int)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    Msg *msg = msg_find_node(fila->mensagens, msgId);
    fila->mensagens = msg_remove_node(fila->mensagens, msg);

    erro = msg == NULL ? ERROR : 1;

    if (write(connection.fifosfd, &erro, sizeof(int)) == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }
    if (erro == ERROR)
    {
        locks_unlock_node(filaId - 1);
        return FALSE;
    }

    locks_unlock_node(filaId - 1);
    return TRUE;
}
