#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stddef.h>

/* status codes */
#define SL_OK   0   // operation successful
#define SL_ERR -1   // operation failed

/* opaque singly linked list type */
typedef struct SinglyList SinglyList;

/* constructor / destructor */

/**
 * creates a new singly linked list with elements of size `elem_size`
 *
 * @param elem_size size of each element in bytes
 * @return pointer to the newly created list, or NULL on failure
 */
SinglyList *sl_create(size_t elem_size);

/**
 * frees all memory used by the list
 *
 * @param list pointer to the singly list to destroy
 */
void sl_destroy(SinglyList *list);


/* insertion */

/**
 * inserts an element at the front of the list
 *
 * @param list pointer to the singly list
 * @param src pointer to the element to insert
 * @return SL_OK on success, SL_ERR on failure
 */
int sl_push_front(SinglyList *list, const void *src);

/**
 * inserts an element at the back of the list in constant time O(1)
 *
 * @param list pointer to the singly list
 * @param src pointer to the element to insert
 * @return SL_OK on success, SL_ERR on failure
 */
int sl_push_back(SinglyList *list, const void *src);

/**
 * inserts an element at the given index
 *
 * @param list pointer to the singly list
 * @param index position at which to insert (0-indexed)
 * @param src pointer to the element to insert
 * @return SL_OK on success, SL_ERR on failure
 */
int sl_insert_at(SinglyList *list, size_t index, const void *src);


/* deletion */

/**
 * removes the front element from the list in constant time O(1)
 *
 * @param list pointer to the singly list
 * @return SL_OK on success, SL_ERR on failure
 */
int sl_pop_front(SinglyList *list);

/**
 * removes the element at the given index
 *
 * @param list pointer to the singly list
 * @param index position of the element to remove (0-indexed)
 * @return SL_OK on success, SL_ERR on failure
 */
int sl_remove_at(SinglyList *list, size_t index);


/* access */

/**
 * returns a pointer to the front element
 *
 * @param list pointer to the singly list
 * @return pointer to the front element, or NULL if list is empty
 */
void *sl_front(const SinglyList *list);

/**
 * returns a pointer to the last element
 *
 * @param list pointer to the singly list
 * @return pointer to the last element, or NULL if list is empty
 */
void *sl_back(const SinglyList *list);

/**
 * returns a pointer to the element at the given index
 *
 * @param list pointer to the singly list
 * @param index position of the element to retrieve (0-indexed)
 * @return pointer to the element, or NULL if out of bounds
 */
void *sl_get(const SinglyList *list, size_t index);


/* utilities */

/**
 * returns the number of elements in the list
 *
 * @param list pointer to the singly list
 * @return number of elements
 */
size_t sl_size(const SinglyList *list);

/**
 * checks if the list is empty
 *
 * @param list pointer to the singly list
 * @return non-zero if empty, 0 otherwise
 */
int sl_is_empty(const SinglyList *list);

/**
 * clears the list contents (size becomes 0)
 *
 * @param list pointer to the singly list
 */
void sl_clear(SinglyList *list);

#endif // SINGLY_LIST_H
