#ifndef REQUEST_STRUCT_H
#define REQUEST_STRUCT_H

#include "connection.h"

/*
 * Function: request_fila
 * ----------------------
 *   Requests the Fila Ids
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int request_fila(Connection connection);

/*
 * Function: request_fila_add
 * --------------------------
 *   Add Fila node
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int request_fila_add(Connection connection);

/*
 * Function: request_fila_msg
 * --------------------------
 *   Requests Msg Ids of a Fila
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int request_fila_msg(Connection connection);

/*
 * Function: request_msg_content
 * -----------------------------
 *   Requests the content of a msg
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int request_msg_content(Connection connection);

/*
 * Function: request_msg_add
 * -------------------------
 *   Adds Msg node
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int request_msg_add(Connection connection);

/*
 * Function: request_msg_remove
 * ----------------------------
 *   Requests the Remove of a msg
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int request_msg_remove(Connection connection);

#endif // REQUEST_STRUCT_H