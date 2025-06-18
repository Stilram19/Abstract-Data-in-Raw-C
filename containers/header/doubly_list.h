#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stddef.h>

/* status codes */
#define DL_OK   0   // operation successful
#define DL_ERR -1   // operation failed

/* opaque doubly linked list type */
typedef struct DoublyList DoublyList;

/* constructor / destructor */

/**
 * creates a new doubly linked list with elements of size `elem_size`
 *
 * @param elem_size size of each element in bytes
 * @return pointer to the newly created list, or NULL on failure
 */
DoublyList *dl_create(size_t elem_size);

/**
 * frees all memory used by the list
 *
 * @param list pointer to the doubly list to destroy
 */
void dl_destroy(DoublyList *list);


/* insertion */

/**
 * inserts an element at the front of the list
 *
 * @param list pointer to the doubly list
 * @param src pointer to the element to insert
 * @return DL_OK on success, DL_ERR on failure
 */
int dl_push_front(DoublyList *list, const void *src);

/**
 * inserts an element at the back of the list
 *
 * @param list pointer to the doubly list
 * @param src pointer to the element to insert
 * @return DL_OK on success, DL_ERR on failure
 */
int dl_push_back(DoublyList *list, const void *src);

/**
 * inserts an element at the given index (0-indexed)
 *
 * @param list pointer to the doubly list
 * @param index position at which to insert
 * @param src pointer to the element to insert
 * @return DL_OK on success, DL_ERR on failure
 */
int dl_insert_at(DoublyList *list, size_t index, const void *src);


/* deletion */

/**
 * removes the front element from the list (constant time)
 *
 * @param list pointer to the doubly list
 * @return DL_OK on success, DL_ERR on failure
 */
int dl_pop_front(DoublyList *list);

/**
 * removes the last element from the list (constant time)
 *
 * @param list pointer to the doubly list
 * @return DL_OK on success, DL_ERR on failure
 */
int dl_pop_back(DoublyList *list);

/**
 * removes the element at the given index (0-indexed)
 *
 * @param list pointer to the doubly list
 * @param index position of the element to remove
 * @return DL_OK on success, DL_ERR on failure
 */
int dl_remove_at(DoublyList *list, size_t index);


/* access */

/**
 * returns a pointer to the front element
 *
 * @param list pointer to the doubly list
 * @return pointer to the front element, or NULL if list is empty
 */
void *dl_front(const DoublyList *list);

/**
 * returns a pointer to the last element
 *
 * @param list pointer to the doubly list
 * @return pointer to the last element, or NULL if list is empty
 */
void *dl_back(const DoublyList *list);

/**
 * returns a pointer to the element at the given index (0-indexed)
 *
 * @param list pointer to the doubly list
 * @param index position of the element to retrieve
 * @return pointer to the element, or NULL if out of bounds
 */
void *dl_get(const DoublyList *list, size_t index);


/* utilities */

/**
 * returns the number of elements in the list
 *
 * @param list pointer to the doubly list
 * @return number of elements
 */
size_t dl_size(const DoublyList *list);

/**
 * checks if the list is empty
 *
 * @param list pointer to the doubly list
 * @return non-zero if empty, 0 otherwise
 */
int dl_is_empty(const DoublyList *list);

/**
 * clears the list contents (size becomes 0)
 *
 * @param list pointer to the doubly list
 */
void dl_clear(DoublyList *list);

#endif // DOUBLY_LIST_H
