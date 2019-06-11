#ifndef MENU_H
#define MENU_H

#include "connection.h"

#define MAX_CONNECTIONS 10

int menu_handle_main(Connection connection);

int menu_show_main(void);

int menu_request_main(Connection connection, int request);

int menu_handle_msg(Connection connection);

int menu_show_msg(void);

int menu_request_msg(Connection connection, int request);

#endif // MENU_H
