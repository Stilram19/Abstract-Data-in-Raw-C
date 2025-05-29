// implemented interface
# include "dynamic_array.h"

// implementation dependencies
# include <stdlib.h>
# include <assert.h>

/*
 * the constructor function
 * initial_capacity must be greater than 0
 * */
DynamicArray *da_create(size_t initial_capacity) {
    assert(initial_capacity > 0);
    DynamicArray *da = malloc(sizeof(DynamicArray));

    if (da == NULL) {
        return (NULL);
    }

    da->data = malloc(initial_capacity * sizeof(int));

    if (da->data == NULL) {
        free(da);
        return (NULL);
    }

    da->size = 0;
    da->capacity = initial_capacity;

    return (da);
}

/*
 * the destructor function: releases all allocated memory related to the arr struct, if any
 * */
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
 * returns the value at the index
 * index cannot be greater than or equals the array size
*/
int da_get(DynamicArray *arr, size_t index) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    /* index must be less than arr->size */
    assert(index < arr->size);

    return (arr->data[index]);
}

/* adds the value at the end of the dynamic array 
 * if array is full we reallocate twice the current capacity (amortized cost)
*/
void da_push_back(DynamicArray *arr, size_t value) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    /* size must never be greater than capacity */
    assert(arr->size <= arr->capacity);

    if (arr->size == arr->capacity) {
        assert(arr->capacity > 0);
        size_t newCapacity = arr->capacity * 2;
        int *newData = realloc(arr->data, newCapacity * sizeof(int)); /* amortized cost */
        if (newData == NULL) {
            return ;
        }
        arr->data = newData;
        arr->capacity = newCapacity;
    }

    arr->data[arr->size] = value;
    arr->size++;
}

/*
 * returns the size of the given dynamic array
 * */
size_t da_size(DynamicArray *arr) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    return (arr->size);
}

/*
 * returns the capacity of the given dynamic array
 * */
size_t da_capacity(DynamicArray* arr) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    return (arr->capacity);
}
