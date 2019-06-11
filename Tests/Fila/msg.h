#ifndef MSG_H
#define MSG_H

#define CONTENT_SIZE 512

typedef struct MSG
{
    int id;
    char *content;
    struct MSG *p_seg;
    struct MSG *p_ant;
} Msg;

/* msg_make_node: Makes a Msg node
* 
*  args:
*    id: Msg id
*    content: Msg content
*
*  return: Node with the given information
*/
Msg *msg_make_node(int id, char *content);

/* msg_insert_node: inserts node in the given list
* 
*  args:
*    L: Msg list
*    node: Msg node to insert
*
*  return: Msg list
*/
Msg *msg_insert_node(Msg *L, Msg *node);


/* msg_find_node: finds the node in the list with the given id
* 
*  args:
*    L: Msg list
*    id: id to find
*
*  return: Msg list
*/
Msg *msg_find_node(Msg *L, int id);

/* msg_remove_node: removes node from the given list
* 
*  args:
*    L: Msg list
*    del: Msg node to remove
*
*  return: Head of Msg list
*/
Msg *msg_remove_node(Msg *L, Msg *del);

/* msg_max_id: searches the id in the given list
* 
*  args:
*    L: Msg list 
*
*  return: Msg max id
*/
int msg_max_id(Msg *L);

/* msg_free: frees the list
* 
*  args:
*    L: Msg list
*
*  return: NULL
*/
Msg *msg_free(Msg *L);

#endif //MSG_H
