#include <stdio.h>
#include "lock.h"

int teste_locks_insert_node(void);
int teste_lock(void);

int main(void)
{
    printf("teste_locks_insert_node : %d\n", teste_locks_insert_node());

    printf("teste_lock : %d\n", teste_lock());

    return 0;
}

int teste_locks_insert_node(void)
{
    int size = 0;
    int *locks = locks_insert_node(NULL, &size);

    //printf("locks[0] = %d\n", locks[0]);

    locks = locks_insert_node(locks, &size);

    locks[size - 1] = 1;

    //printf("locks[size - 1] = %d\n", locks[size - 1]);

    return 1;
}

int teste_lock(void)
{
    int size = 0;
    int *locks = locks_insert_node(NULL, &size);
    locks_insert_node(NULL, &size);
    locks_insert_node(NULL, &size);
    locks_insert_node(NULL, &size);

    lock(locks, size, 0);
    printf("locks[0] = %d\n", locks[0]);

    unlock(locks, size, 0);

    printf("locks[0] = %d\n", locks[0]);

    return 1;
}