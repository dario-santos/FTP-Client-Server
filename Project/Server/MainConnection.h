#ifndef MAINCONNECTION_H
#define MAINCONNECTION_H

#include <pthread.h>

typedef struct
{
    int writefd;
    int readfd;
    pthread_t thread_id;
} MainConnection;

#endif // MAINCONNECTION_H
