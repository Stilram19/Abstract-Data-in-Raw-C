#include "sort.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// inline merge of the two subarrays [start1, end1], [start2, end2]
// temp is used as auxilary temporary space to copy merged subarrays
static void _merge(void *base, uint8_t *temp, size_t elem_size, size_t start1, size_t end1, size_t start2, size_t end2, Comparator cmp) {
    uint8_t *arr = base;

    // copy first subarray into temp
    memcpy(temp, arr + start1 * elem_size, (end1 - start1 + 1) * elem_size);

    // merge subarrays into `arr`
    size_t i = 0, j = start2, k = start1;
    while (start1 + i <= end1 && j <= end2) {
        void *elem1 = temp + i * elem_size;
        void *elem2 = arr + j * elem_size;

        // guarantee stability (<=)
        if (cmp(elem1, elem2) <= 0) {
            memcpy(arr + k * elem_size, elem1, elem_size);
            i += 1;
        } else {
            memcpy(arr + k * elem_size, elem2, elem_size);
            j += 1;
        }

        k += 1;
    }

    while (start1 + i <= end1) {
        void *elem1 = temp + i * elem_size;
        memcpy(arr + k * elem_size, elem1, elem_size);
        i += 1;
        k += 1;
    }
}

static int _merge_sort(void *base, void *temp, size_t size, size_t elem_size, size_t start, size_t end, Comparator cmp) {
    if (start >= end) {
        return (SORT_OK);
    }

    // divide
    size_t mid = (start + end) / 2;

    if (_merge_sort(base, temp, size, elem_size, start, mid, cmp) == SORT_ERR) {
        return (SORT_ERR);
    }
    if (_merge_sort(base, temp, size, elem_size, mid + 1, end, cmp) == SORT_ERR) {
        return (SORT_ERR);
    }

    // merge
    _merge(base, temp, elem_size, start, mid, mid + 1, end, cmp);
    return (SORT_OK);
}

int merge_sort(void *base, size_t size, size_t elem_size, Comparator cmp) {
    if (base == NULL || cmp == NULL || elem_size == 0) {
        return (SORT_ERR);
    }

    if (size < 2) {
        return (SORT_OK);
    }

    // temp will be used for merging sorted subarrays
    void *temp = malloc(((size / 2) + 1) * elem_size);

    if (temp == NULL) {
        return (SORT_ERR);
    }

    if (_merge_sort(base, temp, size, elem_size, 0, size - 1, cmp) == SORT_ERR) {
        free(temp);
        return (SORT_ERR);
    }

    free(temp);
    return (SORT_OK);
}
