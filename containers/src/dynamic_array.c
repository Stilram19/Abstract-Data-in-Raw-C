/* implemented interface */
# include "dynamic_array.h"

/* implementation dependencies */
# include <stdlib.h>
# include <assert.h>
# include <string.h>


/* private attributes (encapsulation) */
typedef struct DynamicArray {
    void* data;           // raw byte buffer
    size_t size;          // number of elements
    size_t capacity;      // number of slots
    size_t elem_size;     // size of each element
} DynamicArray;

/* private helpers */

/* reallocates the memory of the underlying data to newCapacity 
** if reallocation went successful, both arr->data and arr->capacity are changed
** otherwise nothing is changed
** returns a pointer to the new allocated memory if reallocation went successful,
** returns NULL otherwise to indicate that the reallocation failed
*/
static void *helper_reallocate(DynamicArray *arr, size_t newCapacity) {
    if (arr == NULL) {
        return (NULL);
    }

    assert(newCapacity > 0);

    void *newData = realloc(arr->data, newCapacity * arr->elem_size); 
    if (newData == NULL) {
        return (NULL);
    }
    arr->data = newData;
    arr->capacity = newCapacity;

    return (newData);
}

/*
** the constructor function
** initial_capacity must be greater than 0
** elem_size must be greater than 0
*/
DynamicArray *da_create(size_t initial_capacity, size_t elem_size) {
    assert(initial_capacity > 0);
    assert(elem_size > 0);

    DynamicArray *da = malloc(sizeof(DynamicArray));

    if (da == NULL) {
        return (NULL);
    }

    da->data = malloc(initial_capacity * elem_size);

    if (da->data == NULL) {
        free(da);
        return (NULL);
    }

    da->size = 0;
    da->elem_size = elem_size;
    da->capacity = initial_capacity;

    return (da);
}

/*
** the destructor function: releases all allocated memory related to the arr struct, if any
*/
void da_destroy(DynamicArray *arr) {
    if (arr == NULL) {
        return ;
    }

    if (arr->data != NULL) {
        free(arr->data);
    }

    free(arr);
}

/*
** returns generic pointer to the value at the index
** index cannot be greater than or equals the array size
*/
void *da_get(DynamicArray *arr, size_t index) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    /* index must be less than arr->size */
    assert(index < arr->size);

    size_t indexOffset = index * arr->elem_size; /* the arithmetic step size */

    return (((char*)arr->data + indexOffset));
}

/* adds the value at the end of the dynamic array 
** if array is full we reallocate twice the current capacity (amortized cost)
*/
void da_push_back(DynamicArray *arr, void *ptrToValue) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    /* size must never be greater than capacity */
    assert(arr->size <= arr->capacity);

    if (arr->size == arr->capacity) {
        void *newData = helper_reallocate(arr, arr->capacity * 2);

        if (newData == NULL) {
            return ;
        }
    }

    size_t indexOffset = arr->size * arr->elem_size; /* arithmetic step size */

    /* copy elem_size bytes from the memory block pointed to by 'ptrToValue', to the back of the array */
    memcpy((char*)arr->data + indexOffset, ptrToValue, arr->elem_size);

    arr->size++;
}

/*
** sets the given value in the given index
** if arr is NULL, arr->data is NULL or index is out of range, then nothing is changed 
*/
void da_set(DynamicArray *arr, size_t index, void *ptrToValue) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    /* index must be less than the array size */
    assert(index < arr->size);

    size_t indexOffset = index * arr->elem_size; /* arithmetic step size */

    /* copy elem_size bytes from the memory block pointed to by 'ptrToValue', to the back of the array */
    memcpy((char*)arr->data + indexOffset, ptrToValue, arr->elem_size);
}

/*
** returns the size of the given dynamic array
*/
size_t da_size(DynamicArray *arr) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    return (arr->size);
}

/*
** returns the capacity of the given dynamic array
*/
size_t da_capacity(DynamicArray* arr) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    return (arr->capacity);
}

