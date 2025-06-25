// implemented interface
# include "priority_queue.h"

/* implementation dependencies */
# include "heap.h"
# include <stdlib.h> 

typedef struct PriorityQueue {
    Heap *h;
} PriorityQueue;

/**
 * creates a new priority queue
 *
 * @param elem_size size of each element
 * @param cmp comparator function (min-heap or max-heap)
 * @return pointer to the queue or NULL on failure
 */
PriorityQueue *pq_create(size_t elem_size, pq_cmp_fn cmp) {
    if (elem_size == 0 || cmp == NULL) {
        return (NULL);
    }

    PriorityQueue *pq = malloc(sizeof(PriorityQueue));

    if (pq == NULL) {
        return (NULL);
    }

    pq->h = heap_create(elem_size, cmp);

    if (pq->h == NULL) {
        free(pq);
        return (NULL);
    }

    return (pq);
}

/**
 * destroys the priority queue and releases memory
 */
void pq_destroy(PriorityQueue *pq) {
    if (pq != NULL) {
        heap_destroy(pq->h);
        free(pq);
    }
}

/**
 * inserts a new element into the priority queue
 *
 * @param pq pointer to the queue
 * @param elem pointer to the element to insert
 * @return PQ_OK on success, PQ_ERR on failure
 */
int pq_push(PriorityQueue *pq, const void *elem) {
    if (pq == NULL || elem == NULL) {
        return (PQ_ERR);
    }

    if (heap_insert(pq->h, elem) == HEAP_ERR) {
        return (PQ_ERR);
    }

    return (PQ_OK);
}

/**
 * removes the element with highest priority
 *
 * @param pq pointer to the queue
 * @return PQ_OK on success, PQ_ERR if empty
 */
int pq_pop(PriorityQueue *pq) {
    if (pq == NULL) {
        return (PQ_ERR);
    }

    if (heap_remove_top(pq->h) == HEAP_ERR) {
        return (PQ_ERR);
    }

    return (PQ_OK);
}

/**
 * returns a pointer to the top (highest priority) element
 */
void *pq_top(const PriorityQueue *pq) {
    if (pq == NULL) {
        return (NULL);
    }

    return (heap_peek(pq->h));
}

/**
 * returns the number of elements in the queue
 */
size_t pq_size(const PriorityQueue *pq) {
    if (pq == NULL) {
        return (0);
    }

    return (heap_size(pq->h));
}

/**
 * returns non-zero if the queue is empty or invalid
 */
int pq_is_empty(const PriorityQueue *pq) {
    return (pq == NULL || heap_is_empty(pq->h));
}
