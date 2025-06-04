#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

/* status codes */
#define DA_OK 0
#define DA_ERR -1

/* opaque dynamic array type */
typedef struct DynamicArray DynamicArray;

/* create a new dynamic array that can store elements of size `elem_size`. 
   returns NULL if memory allocation fails. */
DynamicArray* da_create(size_t initial_capacity, size_t elem_size);

/* free all memory associated with the array.
 * if elements are heap pointers they are not freed using this function, they are the responsibility of the user
*/
void da_destroy(DynamicArray *arr);

/* get a pointer to the element at `index`. 
   returns NULL if out of bounds. the returned pointer is valid until next mutation. */
void* da_get(const DynamicArray *arr, size_t index);

/* set the element at `index` by copying `elem_size` bytes from `src`. */
int da_set(DynamicArray* arr, size_t index, const void *src);

/* append an element to the end of the array. */
int da_push_back(DynamicArray *arr, const void *src);

/* insert an element at `index`, shifting elements as needed. */
int da_insert_at(DynamicArray* arr, size_t index, const void *src);

/* remove the element at `index`, shifting elements left. */
int da_remove_at(DynamicArray *arr, size_t index);

/* get current number of elements in the array. */
size_t da_size(const DynamicArray *arr);

/* get total allocated capacity (in number of elements). */
size_t da_capacity(const DynamicArray *arr);

/* clears the array (size becomes 0) */
void da_clear(DynamicArray *arr);

#endif /* DYNAMIC_ARRAY_H */

