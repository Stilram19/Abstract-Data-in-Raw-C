/* implemented interface */
# include "dynamic_array.h"

/* implementation dependencies */
# include <stdlib.h>
# include <assert.h>
# include <string.h>


/* private attributes */
typedef struct DynamicArray {
    void* data;           // raw byte buffer
    size_t size;          // number of elements
    size_t capacity;      // number of slots
    size_t elem_size;     // size of each element
} DynamicArray;

/* private helpers */

/* reallocates the memory of the underlying data to new_capacity 
** if reallocation went successful, both arr->data and arr->capacity are changed
** otherwise nothing is changed
** returns a pointer to the new allocated memory if reallocation went successful,
** returns NULL otherwise to indicate that the reallocation failed
*/
static void *helper_reallocate(DynamicArray *arr, size_t new_capacity) {
    if (arr == NULL) {
        return (NULL);
    }

    assert(new_capacity > 0);

    void *newData = realloc(arr->data, new_capacity * arr->elem_size); 
    if (newData == NULL) {
        return (NULL);
    }
    arr->data = newData;
    arr->capacity = new_capacity;

    return (newData);
}

/* returns the offset in bytes (in terms of the element size) */
static size_t helper_get_offset_in_bytes(DynamicArray *arr, size_t offset) {
    if (arr == NULL) {
        return (offset);
    }

    return (offset * arr->elem_size);
}

/*
 ** this helper right shifts the array by one, starting from startIndex
 ** if arr is NULL or arr->data is NULL, nothing happens
 ** size must be less than capacity
 ** startIndex needs to be less than the size
 ** if call is successful arr->size is incremented
*/
static void helper_right_shift(DynamicArray *arr, size_t startIndex) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    assert(arr->size < arr->capacity);
    assert(startIndex < arr->size);

    size_t srcOffset = helper_get_offset_in_bytes(arr, startIndex);
    size_t destOffset = helper_get_offset_in_bytes(arr, startIndex + 1);
    size_t length = helper_get_offset_in_bytes(arr, arr->size - startIndex);
    void *srcPtr = (char*)arr->data + srcOffset; 
    void *destPtr = (char*)arr->data + destOffset; 

    memmove(destPtr, srcPtr, length);
    arr->size++;
}

/*
 ** this helper left shits elements one time, starting from startIndex
 ** if arr is NULL or arr->data is NULL, nothing happens
 ** startIndex must be less than or equals arr->size and greater than 0
 ** if call is successful arr->size is decremented
*/
static inline void helper_left_shift(DynamicArray *arr, size_t startIndex) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    assert(startIndex <= arr->size);
    assert(startIndex > 0);

    arr->size--;

    if (startIndex == arr->size) {
        return ;
    }

    size_t srcOffset = helper_get_offset_in_bytes(arr, startIndex);
    size_t destOffset = helper_get_offset_in_bytes(arr, startIndex - 1);
    size_t length = helper_get_offset_in_bytes(arr, arr->size - startIndex);
    void *srcPtr = (char*)arr->data + srcOffset;
    void *destPtr = (char*)arr->data + destOffset;

    memcpy(destPtr, srcPtr, length);
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
** if arr is NULL or arr->data is NULL or index is greater than arr->size, NULL is returned 
*/
void *da_get(DynamicArray *arr, size_t index) {
    if (arr == NULL || arr->data == NULL  || index >= arr->size) {
        return (NULL);
    }

    size_t indexOffset = helper_get_offset_in_bytes(arr, index); /* index in bytes */

    return (((char*)arr->data + indexOffset));
}

/* adds the value at the end of the dynamic array 
** if array is full we reallocate twice the current capacity (amortized cost)
** the size is incremented, if the push_back call succeeds
*/
void da_push_back(DynamicArray *arr, void *ptr_to_value) {
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

    size_t indexOffset = helper_get_offset_in_bytes(arr, arr->size); /* index in bytes */

    /* copy elem_size bytes from the memory block pointed to by 'ptr_to_value', to the back of the array */
    memcpy((char*)arr->data + indexOffset, ptr_to_value, arr->elem_size);

    arr->size++;
}

/*
** sets the given value in the given index
** if arr is NULL, arr->data is NULL, then nothing is changed 
** the index must be less than the array size
*/
void da_set(DynamicArray *arr, size_t index, void *ptr_to_value) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    /* index must be less than the array size */
    assert(index < arr->size);

    size_t indexOffset = helper_get_offset_in_bytes(arr, index); /* index in bytes */

    /* copy elem_size bytes from the memory block pointed to by 'ptr_to_value', to the index*/
    memcpy((char*)arr->data + indexOffset, ptr_to_value, arr->elem_size);
}

/*
 ** inserts the element pointed to by ptr_to_value at the right index
 ** if arr is NULL or arr->data is NULL, nothing will happen
 ** index must be less than or equals the array's size
*/
void da_insert_at(DynamicArray *arr, size_t index, void *ptr_to_value) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    /* index cannot be greater than size */
    assert(index <= arr->size);

    /* if index is size, it means we need to insert at the back of the array */
    if (index == arr->size) {
        da_push_back(arr, ptr_to_value);
        return ;
    }

    /* size must not be greater than capacity (at any given time) */
    assert(arr->size <= arr->capacity);

    if (arr->size == arr->capacity) {
        void *newData = helper_reallocate(arr, arr->capacity * 2);
        if (newData == NULL) {
            return ;
        }
    }

    /* right shift all the elements */
    helper_right_shift(arr, index); /* it also increments the array size */

    size_t indexOffset = helper_get_offset_in_bytes(arr, index); /* index in bytes */

    /* copy elem_size bytes from the memory block pointed to by 'ptr_to_value', to the index */
    memcpy((char*)arr->data + indexOffset, ptr_to_value, arr->elem_size);
}


/*
** removes the element at the index
** if arr is NULL or arr->data is NULL, nothing happens
** index must be less than the array size
*/
void da_remove_at(DynamicArray *arr, size_t index) {
    if (arr == NULL || arr->data == NULL) {
        return ;
    }

    /* index must be less than arr->size (valid index) */
    assert(index < arr->size);

    /* left shift */
    helper_left_shift(arr, index + 1); /* it also decrements the array size */
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

