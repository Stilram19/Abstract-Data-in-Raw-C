#include "sort.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int insertion_sort(void *base, size_t size, size_t elem_size, Comparator cmp) {
    if (base == NULL || cmp == NULL || elem_size == 0) {
        return (SORT_ERR);
    }

    if (size < 2) {
        return (SORT_OK);
    }

    void *elem = malloc(elem_size);

    if (elem == NULL) {
        return (SORT_ERR);
    }

    uint8_t *arr = base;

    for (size_t i = 1; i < size; i++) {
        size_t j = i;
        memcpy(elem, arr + i * elem_size, elem_size);

        for (; j > 0; j--) {
            void *prev = arr + (j - 1) * elem_size;

            if (cmp(elem, prev) >= 0) {
                break;
            }

            memcpy(arr + j * elem_size, arr + (j - 1) * elem_size, elem_size); // shift element
        }

        memcpy(arr + j * elem_size, elem, elem_size); // insert element
    }

    free(elem);
    return (SORT_OK);
}
