#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "ftp.h"

#define PATH_CURRENT "./"
#define PATH_SECRET "./secret/"
#define PASSWORD 1234

#define TRUE 1
#define FALSE 0
#define ERROR -1

static int is_in_directory(char *file_path);

static int is_file(char *file_path);

int ftp_handle(Connection *connection)
{
    char buf[BUFSIZ];
    int request_filefd = ERROR;
    int n = ERROR;

    n = read(connection->fifocfd, buf, BUFSIZ);
    if (n == ERROR)
        return FALSE;

    buf[n] = '\0';

    if (ftp_valid_filepath(connection, buf, &request_filefd))
        ftp_send(*connection, request_filefd);
    else
        return FALSE;

    return TRUE;
}

int is_in_directory(char *file_path)
{
    if (strncmp(PATH_CURRENT, file_path, strlen(PATH_CURRENT)) != 0)
        return FALSE;

    if (strncmp("./.", file_path, strlen("./.")) == 0)
        return FALSE;
    
    return TRUE;
}

int is_file(char *file_path)
{
    struct stat st_buf;
    stat(file_path, &st_buf);

    return !S_ISDIR(st_buf.st_mode) ? TRUE : FALSE;
}

int ftp_valid_filepath(Connection *connection, char *file_path, int *request_filefd)
{
    int answer = ERROR;
    int password = ERROR;

    // Is the file in the server directory?
    if (!is_in_directory(file_path))
    {
        answer = ERROR;
        write(connection->fifosfd, &answer, sizeof(int));
        return FALSE;
    }

    // The file is secret?
    if (strncmp(PATH_SECRET, file_path, strlen(PATH_SECRET)) == 0)
    {
        answer = 0;
        // Request the pass
        if (write(connection->fifosfd, &answer, sizeof(int)) == ERROR)
            return FALSE;

        // Reads the pass from the client
        if (read(connection->fifocfd, &password, sizeof(int)) == ERROR)
            return FALSE;

        if (PASSWORD != password)
        {
            answer = ERROR;
            write(connection->fifosfd, &answer, sizeof(int));
            return FALSE;
        }
    }

    // Is a directory?
    if (!is_file(file_path))
    {
        answer = -2;
        write(connection->fifosfd, &answer, sizeof(int));
        return FALSE;
    }

    // The file exists?
    *request_filefd = open(file_path, O_RDONLY);
    if (*request_filefd == ERROR)
    {
        answer = -2;
        write(connection->fifosfd, &answer, sizeof(int));
        return FALSE;
    }

    // Everithing is okay
    answer = 1;
    if (write(connection->fifosfd, &answer, sizeof(int)) == ERROR)
        return FALSE;

    return TRUE;
}

void ftp_send(Connection connection, int request_filefd)
{
    char buf[BUFSIZ];
    int n = 0;

    while ((n = read(request_filefd, buf, BUFSIZ)) > 0)
        if (write(connection.fifosfd, buf, n) != n)
            break;

    close(request_filefd);
}
