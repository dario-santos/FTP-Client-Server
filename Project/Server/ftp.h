#ifndef FTP_H
#define FTP_H

#include "connection.h"

void ftp_handle(Connection *connection);

int ftp_valid_filepath(Connection *connection, char *filepath, int *request_filefd);

void ftp_send(Connection connection, int request_filefd);

#endif  // FTP_H