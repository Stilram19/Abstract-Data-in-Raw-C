#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

#define HEAP_OK    0
#define HEAP_ERR  -1

/**
 * opaque heap structure
 */
typedef struct Heap Heap;

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
typedef int (*heap_cmp_fn)(const void *a, const void *b);

/**
 * creates a new heap
 *
 * @param elem_size size of each element in bytes
 * @param cmp comparison function for heap ordering
 * @return pointer to created heap, or NULL on failure
 */
Heap *heap_create(size_t elem_size, heap_cmp_fn cmp);

/**
 * destroys the heap and frees associated memory
 */
void heap_destroy(Heap *h);

/**
 * inserts a new element into the heap
 *
 * @param h pointer to the heap
 * @param elem pointer to the element to insert
 * @return HEAP_OK on success, HEAP_ERR on failure
 */
int heap_insert(Heap *h, const void *elem);

/**
 * removes the top-priority element from the heap
 *
 * @param h pointer to the heap
 * @return HEAP_OK on success, HEAP_ERR on failure or empty heap
 */
int heap_remove_top(Heap *h);

/**
 * gets a pointer to the top-priority element
 *
 * @param h pointer to the heap
 * @return pointer to element, or NULL if empty or invalid
 */
void *heap_peek(const Heap *h);

/**
 * returns the number of elements currently in the heap
 */
size_t heap_size(const Heap *h);

/**
 * returns non-zero if the heap is empty or invalid
 */
int heap_is_empty(const Heap *h);

#endif // HEAP_H
