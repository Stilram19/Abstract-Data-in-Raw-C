#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

/* this is the dynamic array's interface */

#include <stddef.h>

/* data structure declaration */ 
typedef struct DynamicArray DynamicArray;

/* constructor */
DynamicArray* da_create(size_t initial_capacity, size_t elem_size);

/* destructor */
void da_destroy(DynamicArray* arr);

/* public utilities to manipulate the structure */
void *da_get(DynamicArray *arr, size_t index);
void da_set(DynamicArray *arr, size_t index, void *value);
void da_push_back(DynamicArray *arr, void *value);
void da_insert_at(DynamicArray *arr, size_t index, void *value);
void da_remove_at(DynamicArray *arr, size_t index);
size_t da_capacity(DynamicArray *arr); /* returns the capacity of the given dynamic array */
size_t da_size(DynamicArray *arr); /* returns the size of the given dynamic array */

#endif
