#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

void *server(void *args);

int shutdown_main_thread(pthread_t);

#endif // SERVER_H
