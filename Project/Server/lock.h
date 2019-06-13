#ifndef LOCK_H
#define LOCK_H

/*
 * Function: lock_sem_init
 * -----------------------
 *   Initializes the locking system semaphores
 */
void locks_sem_init(void);

/*
 * Function: lock
 * --------------
 *   Locks the index node of L
 *
 *   index: the index of L to lock
 *
 *   returns: true or false
 */
int locks_lock_node(int index);

/*
 * Function: unlock
 * ----------------
 *   Unlocks the index node of L
 *
 *   index: the index of L to unlock
 *
 *   returns: true or false
 */
int locks_unlock_node(int index);

/*
 * Function: lock_insert_node
 * --------------------------
 *   Inserts a new node in the locks list
 *
 *
 *   returns: The head of the list with the new node
 */
void locks_insert_node(void);

/*
 * Function: locks_free
 * --------------------
 *   Frees the list
 */
void locks_free(void);


#endif // LOCK_H