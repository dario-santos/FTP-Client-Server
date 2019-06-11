#ifndef REQUEST_STRUCT_H
#define REQUEST_STRUCT_H

#include "connection.h"

int request_fila(Connection connection);

int request_fila_add(Connection connection);

int request_fila_msg(Connection connection);

int request_msg_content(Connection connection);

int request_msg_add(Connection connection);

int request_msg_remove(Connection connection);

#endif // REQUEST_STRUCT_H