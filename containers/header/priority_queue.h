#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

#define PQ_OK    0
#define PQ_ERR  -1

typedef struct PriorityQueue PriorityQueue;

/**
 * comparison function used to order elements in the heap
 * must return:
 *   < 0 if a has higher priority than b
 *     0 if equal
 *   > 0 if b has higher priority than a
 *
 * @param a pointer to first element
 * @param b pointer to second element
 * @return result as described above
 */

typedef int (*pq_cmp_fn)(const void *a, const void *b);

/**
 * creates a new priority queue
 *
 * @param elem_size size of each element
 * @param cmp comparator function (min-heap or max-heap)
 * @return pointer to the queue or NULL on failure
 */
PriorityQueue *pq_create(size_t elem_size, pq_cmp_fn cmp);

/**
 * destroys the priority queue and releases memory
 */
void pq_destroy(PriorityQueue *pq);

/**
 * inserts a new element into the priority queue
 *
 * @param pq pointer to the queue
 * @param elem pointer to the element to insert
 * @return PQ_OK on success, PQ_ERR on failure
 */
int pq_push(PriorityQueue *pq, const void *elem);

/**
 * removes the element with highest priority
 *
 * @param pq pointer to the queue
 * @return PQ_OK on success, PQ_ERR if empty
 */
int pq_pop(PriorityQueue *pq);

/**
 * returns a pointer to the top (highest priority) element
 */
void *pq_top(const PriorityQueue *pq);

/**
 * returns the number of elements in the queue
 */
size_t pq_size(const PriorityQueue *pq);

/**
 * returns non-zero if the queue is empty or invalid
 */
int pq_is_empty(const PriorityQueue *pq);

#endif // PRIORITY_QUEUE_H
