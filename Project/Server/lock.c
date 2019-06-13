#include <semaphore.h>
#include <stdlib.h>
#include "lock.h"

#define LOCKED 1
#define UNLOCKED 0

#define TRUE 1
#define FALSE 0

static sem_t sem_lock;
static sem_t sem_unlock;

static int *locks = NULL;
static int size = 0;

void locks_sem_init(void)
{
    sem_init(&sem_lock, 0, 1);
    sem_init(&sem_unlock, 0, 1);
}

int locks_lock_node(int index)
{
    if (index <= -1 || index >= size)
        return FALSE;

    sem_wait(&sem_lock);

    if (locks[index] == LOCKED)
    {
        sem_post(&sem_lock);
        return FALSE;
    }

    locks[index] = LOCKED;
    sem_post(&sem_lock);
    return TRUE;
}

int locks_unlock_node(int index)
{
    if (index <= -1 || index >= size)
        return FALSE;

    sem_wait(&sem_unlock);

    if (locks[index] == UNLOCKED)
    {
        sem_post(&sem_unlock);
        return FALSE;
    }

    locks[index] = UNLOCKED;
    sem_post(&sem_unlock);
    return TRUE;
}

void locks_insert_node(void)
{
    size++;

    locks = size == 1 ? (int *)malloc(sizeof(int)) : (int *)realloc(locks, size * sizeof(int));

    locks[size - 1] = UNLOCKED;
}

void locks_free(void)
{
    free(locks);
    size = 0;
}
