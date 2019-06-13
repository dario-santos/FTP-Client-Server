#include <stdlib.h>
#include "fila.h"

static Fila *fila_insert_first(Fila *L, Fila *node);

static Fila *fila_insert_last(Fila *L, Fila *node);

Fila *fila_make_node(int id, Msg *msg)
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->mensagens = msg;
    fila->id = id;

    fila->p_seg = NULL;
    fila->p_ant = NULL;

    return fila;
}

Fila *fila_insert_first(Fila *L, Fila *node)
{
    if (L == NULL)
        return node;

    node->p_seg = L;
    L->p_ant = node;

    return node;
}

Fila *fila_insert_last(Fila *L, Fila *node)
{
    if (L == NULL)
        return node;

    Fila *aux = L;
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

Fila *fila_insert_node(Fila *L, Fila *node)
{
    if (node == NULL)
        return L;

    Fila *aux = L;

    while (aux != NULL)
    {
        if (aux->id > node->id)
            break;

        aux = aux->p_seg;
    }

    if (aux == NULL)
        return (fila_insert_last(L, node));

    if (aux->p_ant == NULL)
        return (fila_insert_first(L, node));

    if (aux->p_seg == NULL)
    {
        node->p_seg = aux;
        node->p_ant = aux->p_ant;
        (aux->p_ant)->p_seg = node;
        aux->p_ant = node;
    }

    return L;
}

Fila *fila_find_node(Fila *L, int id)
{
    Fila *aux = L;
    while (aux != NULL)
    {
        if (id == aux->id)
            return aux;

        aux = aux->p_seg;
    }

    return NULL;
}

int fila_max_id(Fila *L)
{
    Fila *aux = L;
    int id = 0;

    while (aux != NULL)
    {
        if (id < aux->id)
            id = aux->id;

        aux = aux->p_seg;
    }

    return id;
}

Fila *fila_free(Fila *L)
{
    Fila *current = L;

    while (current != NULL)
    {
        Fila *next = current->p_seg;
        if (current->mensagens != NULL)
            msg_free(current->mensagens);

        free(current);
        current = next;
    }

    return NULL;
}