#ifndef SORT_H
#define SORT_H

#include <stddef.h>

#define SORT_OK 0
#define SORT_ERR -1

/**
* @brief Comparator function used to define the ordering of the elements
* @param a points to the first element
* @param b points to the second element
* @return
* * negative value if *a < *b
* * zero if *a == *b
* * positive if *a > *b
* @note
* * comparator must be deterministic (always produces the same output for the same input)
*/
typedef int (*Comparator)(const void *a, const void *b);

// @brief using bubble sort algorithm under the hood to sort the array at `void *base`
// @param base: pointer to the array
// @param size: array size
// @param elem_size: the size of each element in the array
// @param cmp: comparator function used to define the order of the array elements
int bubble_sort(void *base, size_t size, size_t elem_size, Comparator cmp);

#endif
