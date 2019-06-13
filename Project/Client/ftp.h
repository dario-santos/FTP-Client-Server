#ifndef FTP_H
#define FTP_H

#include "connection.h"

/*
 * Function: ftp_request
 * ---------------------
 *   Requests and receives a file from the server
 * 
 *   connection: The communication channel
 */
void ftp_request(Connection connection);

#endif // FTP_H