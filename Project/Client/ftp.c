#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "ftp.h"

void ftp_request(Connection connection)
{
    char str[BUFSIZ];
    int request = -1;
    int answer = -1;
    int fd = -1;
    int n = -1;

    printf("File Transfer Menu\n");
    printf("Insert the file path: ");
    scanf("%s", str);

    // Sends the file path
    write(connection.fifocfd, str, sizeof(str));

    // Receives the confirmation
    read(connection.fifosfd, &answer, sizeof(int));

    if (answer == -1)
    {
        printf("Client: Error you can only request files in the server directory.\n");
        printf("Client: Please use ./\n");
        return;
    }
    if (answer == 0)
    {
        printf("Client: You are trying to transfer a secreft file.\n");
        printf("Client: Please insert the password: ");
        printf("Password: ");
        scanf("%d", &request);

        // Sends password
        write(connection.fifocfd, &request, sizeof(int));

        // Receives the confirmation
        read(connection.fifosfd, &answer, sizeof(int));

        if (answer == -1)
        {
            printf("Client: Wrong password\n");
            return;
        }
    }

    if (answer == -2)
    {
        printf("Client: The file don't exist.\n");
        return;
    }

    // Creates the file
    fd = creat("received.txt", 0666);

    while ((n = read(connection.fifosfd, str, BUFSIZ)) > 0)
    {
        str[n] = '\0';
        write(fd, str, strlen(str));
    }
    if (n < 0)
        perror("Error receiving file.");

    printf("Client: File Received.\n");
    close(fd);
}