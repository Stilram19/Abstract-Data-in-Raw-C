#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stddef.h>

/* status codes */
#define DL_OK 0
#define DL_ERR -1

/* opaque doubly list type */
typedef struct DoublyList DoublyList;

/* constructor / destructor */
DoublyList *dl_create(size_t elem_size);
void dl_destroy(DoublyList *list);

/* insertion */
int dl_push_front(DoublyList *list, const void *src);
int dl_push_back(DoublyList *list, const void *src);
int dl_insert_at(DoublyList *list, size_t index, const void *src); // doubly list is 0-indexed

/* deletion */
int dl_pop_front(DoublyList *list); // constant time complexity
int dl_pop_back(DoublyList *list); // constant time complexity
int dl_remove_at(DoublyList *list, size_t index); // doubly list is 0-indexed

/* access */
void *dl_front(const DoublyList *list);
void *dl_back(const DoublyList *list);
void *dl_get(const DoublyList *list, size_t index); // doubly list is 0-indexed

/* utilities */
size_t dl_size(const DoublyList *list);
int dl_is_empty(const DoublyList *list);
void dl_clear(DoublyList *list);

#endif // DOUBLY_LIST_H
