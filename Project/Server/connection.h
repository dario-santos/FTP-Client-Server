#ifndef CONNECTION_H
#define CONNECTION_H

#include <pthread.h>

typedef struct CONNECTION
{
    int index;
    int fifosfd;
    int fifocfd;
    char fifos_path[20];
    char fifoc_path[20];
    pthread_t thread_id;

} Connection;

/*
 * Function: connection_can_connect
 * --------------------------------
 *   Returns the index of the free connection
 *
 *   returns: The index of a free connection, -1 if all of the connections are used.
 */
int connection_can_connect(void);

/*
 * Function: connection_init
 * -------------------------
 *   Initializes the required lists with MAX_CONNECTIONS elements
 */
void connection_init(void);

/*
 * Function: get_connection_info
 * -----------------------------
 *   Returns the connections_info in de index position
 * 
 *   index: The position of the node 
 * 
 *   returns: A pointer to the node
 */
Connection *get_connection_info(int index);

/*
 * Function: connection_open
 * -------------------------
 *   Opens the index channel of communication
 * 
 *   writefd: The file that the client is reading the information
 *   index: The index channel to open
 */
void connection_open(int writefd, int index);

/*
 * Function: connection_close
 * --------------------------
 *   Closes the index channel of communication
 * 
 *   index: The index channel to close
 */
void connection_close(int index);

/*
 * Function: connection_free
 * -------------------------
 *   Frees the lists
 */
void connection_free(void);

#endif // CONNECTION_H