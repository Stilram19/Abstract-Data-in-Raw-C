#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stddef.h>

/* status codes */
#define SL_OK 0
#define SL_ERR -1

/* opaque singly list type */
typedef struct SinglyList SinglyList;

/* constructor / destructor */
SinglyList *sl_create(size_t elem_size);
void sl_destroy(SinglyList *list);

/* insertion */
int sl_push_front(SinglyList *list, const void *src);
int sl_push_back(SinglyList *list, const void *src);
int sl_insert_at(SinglyList *list, size_t index, const void *src); /* list is 0-indexed */

/* deletion */
int sl_pop_front(SinglyList *list);
int sl_remove_at(SinglyList *list, size_t index);

/* access */
void *sl_front(const SinglyList *list);
void *sl_back(const SinglyList *list);
void *sl_get(const SinglyList *list, size_t index);

/* utilities */
size_t sl_size(const SinglyList *list);
int sl_is_empty(const SinglyList *list);
void sl_clear(SinglyList *list);

#endif // SINGLY_LIST_H
