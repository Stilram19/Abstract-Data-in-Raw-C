#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define UTIL_OK 0
#define UTIL_ERR -1

/**
* @brief generic swap function to swap any two memory regions of the same size
* @param temp should point to an allocated memory region of at least elem_size bytes
* @return UTIL_ERR to indicate error, and UTIL_OK otherwise
*/
int swap(void *a, void *b, void *temp, size_t elem_size);

#endif
