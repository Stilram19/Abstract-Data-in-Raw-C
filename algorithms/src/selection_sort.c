#include "sort.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

int selection_sort(void *base, size_t size, size_t elem_size, Comparator cmp) {
    if (base == NULL || elem_size == 0 || cmp == NULL) {
        return (SORT_ERR);
    }

    if (size < 2) {
        return (SORT_OK);
    }

    uint8_t *arr = base;
    void *temp = malloc(elem_size);

    if (temp == NULL) {
        return (SORT_ERR);
    }

    for (size_t i = 0; i + 1 < size; i++) {
        void *base_i = arr + i * elem_size;
        void *min_elem = base_i;

        for (size_t j = i + 1; j < size; j++) {
            void *base_j = arr + j * elem_size;

            if (cmp(min_elem, base_j) > 0) {
                min_elem = base_j;
            }
        }
 
        if (base_i != min_elem) {
            if (swap(base_i, min_elem, temp, elem_size) == UTIL_ERR) {
                free(temp);
                return (SORT_ERR);
            }
        }
    }

    free(temp);
    return (SORT_OK);
}
