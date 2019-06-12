#include <stdlib.h>
#include <string.h>
#include "msg.h"

Msg *msg_insert_first(Msg *L, Msg *node);
Msg *msg_insert_last(Msg *L, Msg *node);

Msg *msg_make_node(int id, char *content)
{
    if (content == NULL)
        return NULL;

    Msg *msg = (Msg *)malloc(sizeof(Msg));
    msg->content = (char *)malloc(sizeof(char) * CONTENT_SIZE);

    msg->id = id;
    strcpy(msg->content, content);

    msg->p_seg = NULL;
    msg->p_ant = NULL;

    return msg;
}

Msg *msg_insert_first(Msg *L, Msg *node)
{
    if (L == NULL)
        return node;

    node->p_seg = L;
    L->p_ant = node;

    return node;
}

Msg *msg_insert_last(Msg *L, Msg *node)
{
    if (L == NULL)
        return node;

    Msg *aux = L;
    while (aux != NULL)
    {
        if (aux->p_seg == NULL)
            break;
        aux = aux->p_seg;
    }

    aux->p_seg = node;
    node->p_ant = aux;

    return L;
}

Msg *msg_insert_node(Msg *L, Msg *node)
{
    if (node == NULL)
        return L;

    Msg *aux = L;

    while (aux != NULL)
    {
        if (aux->id > node->id)
            break;

        aux = aux->p_seg;
    }

    if (aux == NULL)
        return (msg_insert_last(L, node));

    if (aux->p_ant == NULL)
        return (msg_insert_first(L, node));

    if (aux->p_seg == NULL)
    {
        node->p_seg = aux;
        node->p_ant = aux->p_ant;
        (aux->p_ant)->p_seg = node;
        aux->p_ant = node;
    }

    return L;
}

Msg *msg_find_node(Msg *L, int id)
{
    Msg *aux = L;
    while (aux != NULL)
    {
        if (id == aux->id)
            return aux;

        aux = aux->p_seg;
    }
    
    return NULL;
}

Msg* msg_remove_node(Msg *L, Msg *del)
{
    if (L == NULL)
        return NULL;
    if(del == NULL)
        return L;

    if (L->id == del->id)
    {
        if(del->p_seg != NULL)
            (del->p_seg)->p_ant = NULL;
        free(del->content);
        free(del);

        L = L->p_seg;
        return L;
    }

    if (del->p_ant != NULL)
        (del->p_ant)->p_seg = del->p_seg;

    if (del->p_seg != NULL)
        (del->p_seg)->p_ant = del->p_ant;

    free(del->content);
    free(del);

    return L;
}

int msg_max_id(Msg *L)
{
    Msg *aux = L;
    int id = 0;

    while (aux != NULL)
    {
        if (id < aux->id)
            id = aux->id;

        aux = aux->p_seg;
    }

    return id;
}

Msg *msg_free(Msg *L)
{
    Msg *current = L;

    while (current != NULL)
    {
        Msg *next = current->p_seg;
        free(current->content);
        free(current);
        current = next;
    }

    return NULL;
}
