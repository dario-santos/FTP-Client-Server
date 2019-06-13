#ifndef CONNECTION_H
#define CONNECTION_H

typedef struct CONNECTION
{
    int fifosfd;
    int fifocfd;
    char fifos_path[20];
    char fifoc_path[20];

} Connection;

/*
 * Function: connection_can_connect
 * --------------------------------
 *   Returns the index of the free connection
 *
 *   returns: The index of a free connection, -1 if all of the connections are used.
 */
int connection_can_connect(int readfd, int writefd);

/*
 * Function: connection_open
 * -------------------------
 *   Opens the index channel of communication
 * 
 *   connection: The communication channel
 *   index: The index channel to open
 */
void connection_open(Connection *connection, int index);

/*
 * Function: connection_close
 * --------------------------
 *   Closes the communication channel
 * 
 *   connection: The communication channel
 */
void connection_close(Connection *connection);

#endif // CONNECTION_H