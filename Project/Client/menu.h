#ifndef MENU_H
#define MENU_H

#include "connection.h"

/*
 * Function: menu_handle_main
 * --------------------------
 *   Handles the Main Menu
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int menu_handle_main(Connection connection);

/*
 * Function: menu_show_main
 * ------------------------
 *   Shows the Main Menu to the user
 * 
 *   returns: The choosen option
 */
int menu_show_main(void);

/*
 * Function: menu_request_main
 * ---------------------------
 *   Handles the Main Menu Options
 * 
 *   connection: The communication channel
 *   request: The request to send to the server
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int menu_request_main(Connection connection, int request);

/*
 * Function: menu_handle_msg
 * -------------------------
 *   Handles the Data Structure 
 * 
 *   connection: The communication channel
 *   
 *   returns: 1 if everything is okay, 0 if not
 */
int menu_handle_msg(Connection connection);

/*
 * Function: menu_show_msg
 * -----------------------
 *   Shows the Data Structure Menu to the user 
 * 
 *   returns: The choosen option
 */
int menu_show_msg(void);

/*
 * Function: menu_request_msg
 * --------------------------
 *   Handles the Data Structure Options
 *   connection: The communication channel
 *   request: The request to send to the server
 * 
 *   returns: 1 if everything is okay, 0 if not
 */
int menu_request_msg(Connection connection, int request);

#endif // MENU_H
