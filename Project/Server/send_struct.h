#ifndef SEND_STRUCT_H
#define SEND_STRUCT_H

#include "connection.h"
#include "fila.h"

/*
 * Function: send_handle
 * ---------------------
 *   Handles the send_struct interface
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 *   
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_handle(Connection *connection, Fila **L);

/*
 * Function: send_fila
 * -------------------
 *   Sends the node ids in L
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 * 
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_fila(Connection connection, Fila *L);

/*
 * Function: send_fila_add
 * -----------------------
 *   Adds a new node to L
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 * 
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_fila_add(Connection connection, Fila **L);

/*
 * Function: send_fila_msg
 * -----------------------
 *   Sends the msg node ids from a L node
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 * 
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_fila_msg(Connection connection, Fila *L);

/*
 * Function: send_msg_content
 * --------------------------
 *   Sends the content of the msg
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 * 
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_msg_content(Connection connection, Fila *L);

/*
 * Function: send_msg_add
 * ----------------------
 *   Adds a new node to the msg list
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 * 
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_msg_add(Connection connection, Fila **L);

/*
 * Function: send_msg_remove
 * -------------------------
 *   Removes a node from msg
 *
 *   connection: The communication channel
 *   Fila: The Fila list head
 * 
 *   returns: 1 if everything runs okay, 0 if not
 */
int send_msg_remove(Connection connection, Fila **L);

#endif // SEND_STRUCT_H