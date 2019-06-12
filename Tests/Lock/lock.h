#ifndef LOCK_H
#define LOCK_H

void lock_sem_init(void);

int lock(int *L, int size, int index);

int unlock(int *L, int size, int index);

int* locks_insert_node(int *L, int *size);

#endif // LOCK_H