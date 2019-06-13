#ifndef FTP_H
#define FTP_H

#include "connection.h"

/*
 * Function: ftp_handle
 * --------------------
 *   Handles the File Transfer interface
 *
 *   connection: The communication channel
 *
 *   returns: 1 if everything runs okay, 0 if not
 */
int ftp_handle(Connection *connection);

/*
 * Function: ftp_valid_filepath
 * ----------------------------
 *   Evaluates the filepath
 *
 *   connection: The communication channel
 *   file_path: The file path
 *   request_filefd: The requested file fd
 *
 *   returns: 1 if everything runs okay, 0 if not
 */
int ftp_valid_filepath(Connection *connection, char *file_path, int *request_filefd);

/*
 * Function: ftp_send
 * ------------------
 *   Sends the file to the client
 *
 *   connection: The communication channel
 *   request_filefd: The requested file fd
 */
void ftp_send(Connection connection, int request_filefd);

#endif  // FTP_H
