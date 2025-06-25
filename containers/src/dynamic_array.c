/* implemented interface */
# include "dynamic_array.h"

/* implementation dependencies */
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include <stdint.h>


/* private attributes */
typedef struct DynamicArray {
    void *data;           // raw byte buffer
    size_t size;          // number of elements
    size_t capacity;      // number of slots
    size_t elem_size;     // size of each element
} DynamicArray;

/* private helpers */

/* reallocates the memory of the underlying data to new_capacity 
** if reallocation went successful, both arr->data and arr->capacity are changed
** otherwise nothing is changed
** returns a pointer to the new allocated memory if reallocation went successful,
** returns NULL otherwise to indicate failure
*/
static void *helper_reallocate(DynamicArray *arr) {
    if (arr == NULL) {
        return (NULL);
    }

    /* prevent capacity overflow */
    if (arr->capacity > SIZE_MAX / 2) {
        return (NULL);
    }

    size_t new_capacity = arr->capacity * 2;

    if (new_capacity == 0) {
        return (NULL);
    }

    void *newData = realloc(arr->data, new_capacity * arr->elem_size); 
    if (newData == NULL) {
        return (NULL);
    }
    arr->data = newData;
    arr->capacity = new_capacity;

    return (newData);
}

/*
 ** this helper right shifts the array by one, starting from startIndex
 ** arr and arr->data mustn't be NULL
 ** size must be less than capacity
 ** startIndex needs to be less than the size
 ** if call is successful arr->size is incremented
*/
static int helper_right_shift(DynamicArray *arr, size_t startIndex) {
    if (arr == NULL || arr->data == NULL || arr->size >= arr->capacity || startIndex >= arr->size) {
        return (DA_ERR);
    }

    size_t srcOffset = startIndex * arr->elem_size;
    size_t destOffset = (startIndex + 1) * arr->elem_size;
    size_t length = (arr->size - startIndex) * arr->elem_size;
    void *srcPtr = (char*)arr->data + srcOffset; 
    void *destPtr = (char*)arr->data + destOffset; 

    memmove(destPtr, srcPtr, length);
    arr->size++;

    return (DA_OK);
}

/*
 ** this helper left shits elements one time, starting from startIndex
 ** arr and arr->data mustn't be NULL
 ** startIndex must be less than or equals arr->size and greater than 0
 ** if call is successful arr->size is decremented
*/
static inline int helper_left_shift(DynamicArray *arr, size_t startIndex) {
    if (arr == NULL || arr->data == NULL || startIndex > arr->size || startIndex == 0) {
        return (DA_ERR);
    }

    if (startIndex == arr->size) {
        arr->size--;
        return (DA_OK);
    }

    size_t srcOffset = startIndex * arr->elem_size;
    size_t destOffset = (startIndex - 1) * arr->elem_size;
    size_t length = (arr->size - startIndex) * arr->elem_size;
    void *srcPtr = (char*)arr->data + srcOffset;
    void *destPtr = (char*)arr->data + destOffset;

    memcpy(destPtr, srcPtr, length);
    arr->size--;

    return (DA_OK);
}
 
/*
** the constructor function
** initial_capacity must be greater than 0
** elem_size must be greater than 0
** returns NULL to indicate failure
*/
DynamicArray *da_create(size_t initial_capacity, size_t elem_size) {
    if (initial_capacity == 0 || elem_size == 0) {
        return (NULL);
    }

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
void *da_get(const DynamicArray *arr, size_t index) {
    if (arr == NULL || arr->data == NULL  || index >= arr->size) {
        return (NULL);
    }

    size_t indexOffset = index * arr->elem_size;/* index in bytes */

    return (((char*)arr->data + indexOffset));
}


/* return a pointer to the last element in `arr` */
void *da_back(const DynamicArray *arr) {
    if (arr == NULL || arr->size == 0) {
        return (NULL);
    }

    return (da_get(arr, arr->size - 1));
}


/* adds the value at the end of the dynamic array 
** if array is full we reallocate twice the current capacity (amortized cost)
** the size is incremented, if the push_back call succeeds
*/
int da_push_back(DynamicArray *arr, const void *src) {
    if (arr == NULL || arr->data == NULL || src == NULL || arr->size > arr->capacity) {
        return (DA_ERR);
    }

    if (arr->size == arr->capacity) {
        void *newData = helper_reallocate(arr);

        if (newData == NULL) {
            return (DA_ERR);
        }
    }

    size_t indexOffset = arr->size * arr->elem_size;/* index in bytes */

    /* copy elem_size bytes from the memory block pointed to by 'src', to the back of the array */
    memcpy((char*)arr->data + indexOffset, src, arr->elem_size);

    arr->size++;
    return (DA_OK);
}

/*
** sets the given value in the given index
** the index must be less than the array size
** arr, arr->data and src must be non-null pointers
** return -1 to indicate an error, and 0 to indicate success
*/
int da_set(DynamicArray *arr, size_t index, const void *src) {
    if (arr == NULL || arr->data == NULL || src == NULL || index >= arr->size) {
        return (DA_ERR);
    }

    size_t indexOffset = index * arr->elem_size;/* index in bytes */

    /* copy elem_size bytes from the memory block pointed to by 'src', to the index*/
    memcpy((char*)arr->data + indexOffset, src, arr->elem_size);

    return (DA_OK);
}

/*
 ** inserts the element pointed to by src at the right index
** the index must be less than or equals the array size
** arr, arr->data and src must be non-null pointers
** return -1 to indicate an error, and 0 to indicate success
*/
int da_insert_at(DynamicArray *arr, size_t index, const void *src) {
    if (arr == NULL || arr->data == NULL || src == NULL || index > arr->size) {
        return (DA_ERR);
    }

    /* if index is size, it means we need to insert at the back of the array */
    if (index == arr->size) {
        return (da_push_back(arr, src));
    }

    /* size must not be greater than capacity (at any given time) */
    if (arr->size > arr->capacity) {
        return (DA_ERR);
    }

    if (arr->size == arr->capacity) {
        void *newData = helper_reallocate(arr);
        if (newData == NULL) {
            return (DA_ERR);
        }
    }

    /* right shift all the elements starting from index */
    if (helper_right_shift(arr, index) == DA_ERR) {
        return (DA_ERR);
    }

    size_t indexOffset = index * arr->elem_size;/* index in bytes */

    /* copy elem_size bytes from the memory block pointed to by 'src', to the index */
    memcpy((char*)arr->data + indexOffset, src, arr->elem_size);

    return (DA_OK);
}

int da_swap(DynamicArray *arr, size_t i, size_t j) {
    if (arr == NULL || i >= arr->size || j >= arr->size) {
        return (DA_ERR);
    }

    // we need a temporary memory for swap operation
    void *temp = malloc(arr->elem_size);

    if (temp == NULL) {
        return (DA_ERR);
    }

    memcpy(temp, (char*)arr->data + i * arr->elem_size, arr->elem_size); // temp <- a[i]
    memcpy((char*)arr->data + i * arr->elem_size, (char*)arr->data + j * arr->elem_size, arr->elem_size); // a[i] <- a[j]
    memcpy((char*)arr->data + j * arr->elem_size, temp, arr->elem_size); // a[j] <- temp

    free(temp);

    return (DA_OK);
}

/*
** removes the element at the index
** arr and arr->data mustn't be NULL
** index must be less than the array size
** return -1 to indicate an error, and 0 to indicate success
*/
int da_remove_at(DynamicArray *arr, size_t index) {
    if (arr == NULL || arr->data == NULL || index >= arr->size) {
        return (DA_ERR);
    }

    /* shift elements left starting from element after index */
    if (helper_left_shift(arr, index + 1) == DA_ERR) {
        return (DA_ERR);
    }

    return (DA_OK);
}

/* removes the last element in the array */
int da_pop(DynamicArray *arr) {
    if (arr == NULL) {
        return (DA_ERR);
    }

    if (arr->size == 0) {
        return (DA_ERR);
    }

    return (da_remove_at(arr, arr->size - 1));
}

/*
** returns the size of the given dynamic array
*/
size_t da_size(const DynamicArray *arr) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    return (arr->size);
}

/*
** returns the capacity of the given dynamic array
*/
size_t da_capacity(const DynamicArray* arr) {
    if (arr == NULL || arr->data == NULL) {
        return (0);
    }

    return (arr->capacity);
}

/* clears the array (size becomes zero) */
void da_clear(DynamicArray *arr) {
    if (arr) arr->size = 0;
}
