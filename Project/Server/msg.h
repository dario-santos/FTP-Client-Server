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

/*
 * Function: msg_make_node
 * -----------------------
 *   Makes a Msg node
 *
 *   id: node id
 *   content: Msg content
 *
 *   returns: Pointer to the node
 */
Msg *msg_make_node(int id, char *content);

/*
 * Function: msg_insert_node
 * -------------------------
 *   Inserts the node in the list
 *
 *   L: List to insert the node
 *   node: The node to insert
 *
 *   returns: Pointer to the new head of the list
 */
Msg *msg_insert_node(Msg *L, Msg *node);

/*
 * Function: msg_find_node
 * -----------------------
 *   Returns the node with the givin id.
 * 
 *   L: List to search the node
 *   id: The id to search
 *
 *   returns: Pointer to the node
 */
Msg *msg_find_node(Msg *L, int id);

/*
 * Function: msg_remove_node
 * -------------------------
 *   Removes the node from the list
 * 
 *   L: List to search
 *   del: The element to remove from the list
 *
 *   returns: The head to the list
 */
Msg *msg_remove_node(Msg *L, Msg *del);

/*
 * Function: msg_max_id
 * --------------------
 *   Returns highest id
 * 
 *   L: List to search
 *
 *   returns: The highest id
 */
int msg_max_id(Msg *L);

/*
 * Function: msg_free
 * ------------------
 *   Frees the allocated memory of the list
 * 
 *   L: The list to free
 *
 *   returns: NULL
 */
Msg *msg_free(Msg *L);

#endif //MSG_H
