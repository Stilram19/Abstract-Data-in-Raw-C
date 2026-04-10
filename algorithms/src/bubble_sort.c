#include "sort.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

int bubble_sort(void *base, size_t size, size_t elem_size, Comparator cmp) {
    if (base == NULL || cmp == NULL || elem_size == 0) {
        return (SORT_ERR);
    }

    if (size < 2) {
        return (SORT_OK);
    }

    int swapped = 1; // flag keeping track of whether we swapped
    size_t n = size;
    uint8_t *arr = base;
    void *temp = malloc(elem_size);

    if (temp == NULL) {
        return (SORT_ERR);
    }

    while (swapped && n > 1) {
        swapped = 0;
        for (size_t i = 0; i + 1 < n; i++) {
            void *a = arr + i * elem_size;
            void *b = arr + (i + 1) * elem_size;
 
            if (cmp(a, b) > 0) {
                if (swap(a, b, temp, elem_size) == UTIL_ERR) {
                    free(temp);
                    return (SORT_ERR);
                }
                swapped = 1;
            }
        }

        n -= 1; // largest element in range [0, n - 1] sorted
    }

    free(temp);
    return (SORT_OK);
}
