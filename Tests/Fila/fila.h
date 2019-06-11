#ifndef FILA_H
#define FILA_H

#include "msg.h"

/* msg_make_node: Makes a Msg node
* 
*  args:
*    id: Msg id
*    content: Msg content
*
*  return: Node with the given information
*/
typedef struct FILA
{
    int id;
    Msg *mensagens;
    struct FILA *p_seg;
    struct FILA *p_ant;
} Fila;

/* fila_make_node: Makes a Fila node
* 
*  args:
*    id: Fila id
*    mensagens: Msg list
*
*  return: Node with the given information
*/
Fila *fila_make_node(int id, Msg *mensagens);

/* fila_insert_node: Inserts a node in the given list
* 
*  args:
*    L: Fila list
*    node: Fila node to insert
*
*  return: Fila list with the node
*/
Fila *fila_insert_node(Fila *L, Fila *node);

/* fila_find_node: finds the node in the list with the given id
* 
*  args:
*    L: Fila list
*    id: id to find
*
*  return: Fila list
*/
Fila *fila_find_node(Fila *L, int id);

/* fila_max_id: searches the id in the given list
* 
*  args:
*    L: Fila list 
*
*  return: Fila max int id
*/
int fila_max_id(Fila *L);


/* fila_free: frees the list
* 
*  args:
*    L: Fila list
*
*  return: NULL
*/
Fila *fila_free(Fila *L);

#endif // FILA_H