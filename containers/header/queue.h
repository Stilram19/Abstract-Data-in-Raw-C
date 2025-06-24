#ifndef QUEUE_H
# define QUEUE_H

# include <stddef.h>

# define QUEUE_OK    0   // indicates a successful queue operation
# define QUEUE_ERR  -1   // indicates a failed queue operation

/**
 * opaque structure representing a queue
 * stores elements of fixed size in first-in, first-out order
 */
typedef struct Queue Queue;

/**
 * creates a new queue that holds elements of a given size
 *
 * @param elem_size size in bytes of each element
 * @return pointer to the created queue, or NULL on failure
 */
Queue *queue_create(size_t elem_size);

/**
 * destroys the queue and frees all associated memory
 *
 * @param q pointer to the queue to destroy
 */
void queue_destroy(Queue *q);

/**
 * adds an element to the back of the queue in constant time O(1)
 *
 * @param q pointer to the queue
 * @param elem pointer to the element to enqueue
 * @return QUEUE_OK on success, QUEUE_ERR on failure
 */
int queue_enqueue(Queue *q, const void *elem);

/**
 * removes an element from the front of the queue in constant time O(1)
 *
 * @param q pointer to the queue
 * @return QUEUE_OK on success, QUEUE_ERR if the queue is empty or invalid
 */
int queue_dequeue(Queue *q);

/**
 * returns a pointer to the front element of the queue
 *
 * @param q pointer to the queue
 * @return pointer to the front element, or NULL if the queue is empty or invalid
 */
void *queue_front(const Queue *q);

/**
 * returns the number of elements in the queue
 *
 * @param q pointer to the queue
 * @return number of elements, or 0 if the queue is invalid
 */
size_t queue_size(const Queue *q);

/**
 * checks whether the queue is empty
 *
 * @param q pointer to the queue
 * @return non-zero if empty or invalid, 0 otherwise
 */
int queue_is_empty(const Queue *q);

/**
 * clears the queue content (size becomes 0)
 *
 * @param q pointer to the queue 
 */
void queue_clear(Queue *q);

#endif // QUEUE_H
