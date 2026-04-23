#include "sort.h"

// inline merge of the two subarrays [start1, end1], [start2, end2]
static int _merge(void *base, size_t start1, size_t end1, size_t start2, size_t end2, Comparator cmp) {
    return (SORT_OK);
}

// 3, 4, 1, 2
static int _merge_sort(void *base, size_t size, size_t elem_size, size_t start, size_t end, Comparator cmp) {
    if (start >= end) {
        return (SORT_OK);
    }

    // divide
    size_t mid = (start + end) / 2;

    if (_merge_sort(base, size, elem_size, start, mid, cmp) == SORT_ERR) {
        return (SORT_ERR);
    }
    if (_merge_sort(base, size, elem_size, mid + 1, end, cmp) == SORT_ERR) {
        return (SORT_ERR);
    }

    // merge
    if (_merge(base, start, mid, mid + 1, end, cmp) == SORT_ERR) {
        return (SORT_ERR);
    }
    return (SORT_OK);
}

int merge_sort(void *base, size_t size, size_t elem_size, Comparator cmp) {
    if (base == NULL || cmp == NULL || elem_size == 0) {
        return (SORT_ERR);
    }

    if (size < 2) {
        return (SORT_OK);
    }

    return (_merge_sort(base, size, elem_size, 0, size - 1, cmp));
}
