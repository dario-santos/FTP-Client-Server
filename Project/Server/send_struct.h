#ifndef SEND_STRUCT_H
#define SEND_STRUCT_H

#include "connection.h"
#include "fila.h"
#include "msg.h"

void send_handle(Connection *connection, Fila **L);

int send_fila(Connection connection, Fila *L);

int send_fila_add(Connection connection, Fila **L);

int send_fila_msg(Connection connection, Fila *L);

int send_msg_content(Connection connection, Fila *L);

int send_msg_add(Connection connection, Fila **L);

int send_msg_remove(Connection connection, Fila **L);

#endif