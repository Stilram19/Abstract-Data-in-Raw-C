#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

/* status codes */
#define DA_OK  0   ///< operation successful
#define DA_ERR -1  ///< operation failed

/* opaque dynamic array type */
typedef struct DynamicArray DynamicArray;

/**
 * creates a new dynamic array with given initial capacity and element size
 *
 * @param initial_capacity number of elements to initially allocate
 * @param elem_size size in bytes of each element
 * @return pointer to the created array, or NULL on failure
 */
DynamicArray *da_create(size_t initial_capacity, size_t elem_size);

/**
 * destroys the array and frees all associated memory
 * 
 * @param arr pointer to the dynamic array
 * @note user is responsible for freeing element contents if they are heap pointers
 */
void da_destroy(DynamicArray *arr);

/**
 * returns a pointer to the element at the given index
 *
 * @param arr pointer to the dynamic array
 * @param index index of the element to retrieve
 * @return pointer to the element, or NULL if out of bounds
 * @note returned pointer is valid until next mutation
 */
void *da_get(const DynamicArray *arr, size_t index);

/**
 * returns a pointer to the last element in the array
 *
 * @param arr pointer to the dynamic array
 * @return pointer to the last element, or NULL if array is empty or invalid
 */
void *da_back(const DynamicArray *arr);

/**
 * sets the element at the given index by copying from src
 *
 * @param arr pointer to the dynamic array
 * @param index index to modify
 * @param src pointer to source data to copy
 * @return DA_OK on success, DA_ERR on failure
 */
int da_set(DynamicArray *arr, size_t index, const void *src);

/**
 * appends a new element to the end of the array
 *
 * @param arr pointer to the dynamic array
 * @param src pointer to the element to append
 * @return DA_OK on success, DA_ERR on failure
 */
int da_push_back(DynamicArray *arr, const void *src);

/**
 * inserts an element at a specific index, shifting elements as needed
 *
 * @param arr pointer to the dynamic array
 * @param index position to insert at (0 <= index <= size)
 * @param src pointer to the element to insert
 * @return DA_OK on success, DA_ERR on failure
 */
int da_insert_at(DynamicArray *arr, size_t index, const void *src);

/**
 * removes the element at a specific index, shifting elements left
 *
 * @param arr pointer to the dynamic array
 * @param index index of the element to remove
 * @return DA_OK on success, DA_ERR on failure
 */
int da_remove_at(DynamicArray *arr, size_t index);

/**
 * removes the last element from the array
 *
 * @param arr pointer to the dynamic array
 * @return DA_OK on success, DA_ERR on failure
 */
int da_pop(DynamicArray *arr);

/**
 * returns the number of elements currently in the array
 *
 * @param arr pointer to the dynamic array
 * @return number of elements in the array
 */
size_t da_size(const DynamicArray *arr);

/**
 * returns the total allocated capacity of the array (in number of elements)
 *
 * @param arr pointer to the dynamic array
 * @return allocated capacity
 */
size_t da_capacity(const DynamicArray *arr);

/**
 * clears the array contents (size becomes zero)
 *
 * @param arr pointer to the dynamic array
 */
void da_clear(DynamicArray *arr);

#endif /* DYNAMIC_ARRAY_H */
