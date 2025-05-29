#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

#include <stddef.h>


// this is the dynamic array's interface

// data (attributes)
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} DynamicArray;

// constructor
DynamicArray* da_create(size_t initial_capacity);

// destructor
void da_destroy(DynamicArray* arr);

// public utilities to manipulate the structure
int da_get(DynamicArray* arr, size_t index);
void da_set(DynamicArray* arr, size_t index, size_t value);
void da_push_back(DynamicArray* arr, size_t value);
void da_insert_at(DynamicArray* arr, size_t index, size_t value);
void da_remove_at(DynamicArray* arr, size_t index);
size_t da_capacity(DynamicArray* arr);
size_t da_size(DynamicArray* arr);

#endif
