#include <semaphore.h>
#include <stdlib.h>
#include "lock.h"

sem_t sem_lock;
sem_t sem_unlock;

void lock_sem_init(void)
{
    sem_init(&sem_lock, 0, 1);
    sem_init(&sem_unlock, 0, 1);
}

int lock(int *L, int size, int index)
{
    if (index >= size || index < 0)
        return 0;

    //sem_wait(&sem_lock);

    if (L[index] == 0)
        L[index] = 1;
    else
        return 0;

    //sem_post(&sem_unlock);
    return 1;
}

int unlock(int *L, int size, int index)
{
    if (index >= size || index < 0)
        return 0;

    //sem_wait(&sem_lock);

    if (L[index] == 1)
        L[index] = 0;
    else
        return 0;

    //sem_post(&sem_unlock);
    return 1;
}

int *locks_insert_node(int *L, int *size)
{
    (*size)++;

    if (*size == 1)
        L = (int *)malloc(sizeof(int));
    else
        L = (int *)realloc(L, (*size) * sizeof(int));

    L[*size - 1] = 0;

    return L;
}
