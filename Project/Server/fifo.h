#ifndef FIFO_H
#define FIFO_H

#include <pthread.h>

// Comunicação Servidor - Cliente
#define FIFO_COM_S "/tmp/FIFO_COM_S.X"
// Comunicação Cliente - Servidor
#define FIFO_COM_C "/tmp/FIFO_COM_C.X"

#define FIFOS "/tmp/FIFOS.%d"
#define FIFOC "/tmp/FIFOC.%d"

#define PATH_CURRENT "./"
#define PATH_SECRET "./secret/"
#define PASSWORD 1234

#define true 1
#define false 0
#define ERROR -1

typedef struct
{
    int writefd;
    int readfd;
    pthread_t thread_id;
} MainConnection;

#endif // FIFO_H
