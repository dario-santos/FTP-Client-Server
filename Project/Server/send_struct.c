#include <unistd.h>
#include <string.h>
#include "send_struct.h"
#include "lock.h"

int *locks = NULL;
int size = 0;

void send_handle(Connection *connection, Fila **filas)
{
    int request = -1;

    // Receber comando do cliente
    if (read(connection->fifocfd, &request, sizeof(int)) == -1)
        return;

    switch (request)
    {
    case 0:
    default:
        break;
    case 1:
        send_fila(*connection, *filas);
        break;
    case 2:
        send_fila_add(*connection, filas);
        break;
    case 3:
        send_fila_msg(*connection, *filas);
        break;
    case 4:
        send_msg_content(*connection, *filas);
        break;
    case 5:
        send_msg_add(*connection, filas);
        break;
    case 6:
        send_msg_remove(*connection, filas);
        break;
    }

    return;
}

int send_fila(Connection connection, Fila *L)
{
    Fila *aux = L;
    int resposta = -1;
    int lock_error = 0;
    int lock_index_error = 0;
    int i = 0;

    for (i = 0; i < size; i++)
        if (!lock(locks, size, i))
        {
            lock_error = -1;
            lock_index_error = i;
            break;
        }

    if (lock_error == -1)
    {
        for (i = 0; i < lock_index_error; i++)
            unlock(locks, size, i);

        write(connection.fifosfd, &resposta, sizeof(resposta));
        return -1;
    }

    // Enviar os ids
    while (aux != NULL)
    {
        if (write(connection.fifosfd, &aux->id, sizeof(aux->id)) == -1)
        {
            for (i = 0; i < lock_index_error; i++)
                unlock(locks, size, i);

            write(connection.fifosfd, &resposta, sizeof(resposta));
            return -1;
        }

        aux = aux->p_seg;
    }

    // Informar que terminou
    if (write(connection.fifosfd, &resposta, sizeof(resposta)) == -1)
    {
        for (i = 0; i < lock_index_error; i++)
            unlock(locks, size, i);

        write(connection.fifosfd, &resposta, sizeof(resposta));
        return -1;
    }

    for (i = 0; i < lock_index_error; i++)
        unlock(locks, size, i);

    return 0;
}

int send_fila_add(Connection connection, Fila **L)
{
    int id = fila_max_id(*L) + 1;
    int error = -1;

    if (size > 0)
        if (lock(locks, size, id - 2) == 0)
        {
            write(connection.fifosfd, &error, sizeof(int));
            return error;
        }

    *L = fila_insert_node(*L, fila_make_node(id, NULL));
    locks = locks_insert_node(locks, &size);

    if (write(connection.fifosfd, &id, sizeof(int)) == error)
    {
        unlock(locks, size, id - 2);
        return error;
    }

    unlock(locks, size, id - 2);
    return 0;
}

int send_fila_msg(Connection connection, Fila *L)
{
    Fila *fila = NULL;
    Msg *aux = NULL;
    int resposta = -1; // -1 -> fim da fila
    int erro = -1;
    int id = 0;

    // Receber id da Fila
    if (read(connection.fifocfd, &id, sizeof(int)) == -1)
        return -1;

    if (!lock(locks, size, id - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
            return -1;
        if (erro == -1)
            return -1;
    }

    fila = fila_find_node(L, id);
    erro = fila == NULL ? -1 : 1;

    if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
    {
        unlock(locks, size, id - 1);
        return -1;
    }

    if (erro == -1)
    {
        unlock(locks, size, id - 1);
        return -1;
    }

    aux = fila->mensagens;

    // Enviar os ids
    while (aux != NULL)
    {
        if (write(connection.fifosfd, &aux->id, sizeof(int)) == -1)
        {
            unlock(locks, size, id - 1);
            return -1;
        }

        aux = aux->p_seg;
    }

    // Informar que terminou
    if (write(connection.fifosfd, &resposta, sizeof(int)) == -1)
    {
        unlock(locks, size, id - 1);
        return -1;
    }

    unlock(locks, size, id - 1);
    return 1;
}

int send_msg_content(Connection connection, Fila *L)
{
    int filaId = 0;
    int msgId = 0;
    int erro = -1;
    Fila *fila = NULL;
    Msg *msg = NULL;

    // Receber id da Fila
    if (read(connection.fifocfd, &filaId, sizeof(int)) == -1)
        return -1;

    if (!lock(locks, size, filaId - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
            return -1;
        if (erro == -1)
            return -1;
    }

    fila = fila_find_node(L, filaId);
    erro = fila == NULL ? -1 : 1;

    // Fila não existe
    if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }
    if (erro == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    // Receber id da Mensagem
    if (read(connection.fifocfd, &msgId, sizeof(int)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    msg = msg_find_node(fila->mensagens, msgId);
    erro = msg == NULL ? -1 : 1;

    // Msg não existe
    if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    if (erro == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    // Envia o conteudo
    if (write(connection.fifosfd, msg->content, strlen(msg->content)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    unlock(locks, size, filaId - 1);
    return 1;
}

int send_msg_add(Connection connection, Fila **L)
{
    Fila *fila = NULL;
    char content[CONTENT_SIZE];
    int filaId = 0;
    int msgId = 0;
    int erro = -1;
    int n = 0;

    // Receber id da Fila a inserir
    if (read(connection.fifocfd, &filaId, sizeof(int)) == -1)
        return -1;

    if (!lock(locks, size, filaId - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
            return -1;
        if (erro == -1)
            return -1;
    }

    fila = fila_find_node(*L, filaId);
    erro = fila == NULL ? -1 : 1;

    // Fila não existe
    if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }
    if (erro == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    // Receber conteudo da Mensagem a inserir
    if ((n = read(connection.fifocfd, content, CONTENT_SIZE - 1)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    content[n] = '\0';
    msgId = msg_max_id(fila->mensagens) + 1;
    fila->mensagens = msg_insert_node(fila->mensagens, msg_make_node(msgId, content));

    unlock(locks, size, filaId - 1);
    return 1;
}

int send_msg_remove(Connection connection, Fila **L)
{
    int filaId = -1;
    int msgId = -1;
    int erro = -1;
    Fila *fila = *L;

    // Receber id da Fila
    if (read(connection.fifocfd, &filaId, sizeof(int)) == -1)
        return -1;

    if (!lock(locks, size, filaId - 1))
    {
        if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
            return -1;
        if (erro == -1)
            return -1;
    }

    fila = fila_find_node(*L, filaId);
    erro = fila == NULL ? -1 : 1;

    if (write(connection.fifosfd, &erro, sizeof(erro)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }
    if (erro == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    // Receber id da Mensagem
    if (read(connection.fifocfd, &msgId, sizeof(int)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    Msg *msg = msg_find_node(fila->mensagens, msgId);
    fila->mensagens = msg_remove_node(fila->mensagens, msg);

    erro = msg == NULL ? -1 : 1;

    // Msg não existe
    if (write(connection.fifosfd, &erro, sizeof(int)) == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }
    if (erro == -1)
    {
        unlock(locks, size, filaId - 1);
        return -1;
    }

    unlock(locks, size, filaId - 1);
    return 1;
}
