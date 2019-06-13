#ifndef FILA_H
#define FILA_H

#include "msg.h"

typedef struct FILA
{
    int id;
    Msg *mensagens;
    struct FILA *p_seg;
    struct FILA *p_ant;
} Fila;

/*
 * Function: fila_make_node
 * ------------------------
 *   Makes a Fila node
 *
 *   id: node id
 *   mensagens: Msg list of this node
 *
 *   returns: Pointer to the node
 */
Fila *fila_make_node(int id, Msg *mensagens);

/*
 * Function: fila_insert_node
 * --------------------------
 *   Inserts the node in the list
 *
 *   L: List to insert the node
 *   node: The node to insert
 *
 *   returns: Pointer to the new head of the list
 */
Fila *fila_insert_node(Fila *L, Fila *node);

/*
 * Function: fila_find_node
 * ------------------------
 *   Returns the node with the givin id.
 * 
 *   L: List to search the node
 *   id: The id to search
 *
 *   returns: Pointer to the node
 */
Fila *fila_find_node(Fila *L, int id);

/*
 * Function: fila_max_id
 * ---------------------
 *   Returns highest id
 * 
 *   L: List to search
 *
 *   returns: The highest id
 */
int fila_max_id(Fila *L);

/*
 * Function: fila_free
 * ------------------------
 *   Frees the allocated memory of the list
 * 
 *   L: The list to free
 *
 *   returns: NULL
 */
Fila *fila_free(Fila *L);

#endif // FILA_H