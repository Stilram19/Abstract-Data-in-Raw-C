#include "sort.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

static size_t _partition(void *base, void *elem_size_temp, size_t elem_size, size_t start, size_t end, size_t pivot_index, Comparator cmp) {
    uint8_t *arr = base;

    void *pivot = arr + pivot_index * elem_size;

    // swap elements at pivot index and end (if they are not the same)
    if (pivot_index != end) {
        swap(pivot, arr + end * elem_size, elem_size_temp, elem_size);
    }

    size_t i = start, j = end - 1;

    while (i < j) {
        if (cmp(pivot, arr + i * elem_size) <= 0) {
            i += 1;
            continue;
        }
        if (cmp(pivot, arr + j * elem_size) >= 0) {
            j -= 1;
            continue;
        }
        swap(arr + i * elem_size, arr + j * elem_size, elem_size_temp, elem_size);
    }

    // i == j at loop end 
    swap(pivot, arr + i * elem_size, elem_size_temp, elem_size); // the pivot is sorted (in its place in the final sorted array)

    return i;
}

static void _quick_sort(void *base, void *elem_size_temp, size_t elem_size, size_t start, size_t end, Comparator cmp) {
    if (start >= end) {
        return;
    }

    size_t pivot_index = (end + start) / 2;
    size_t pivot_fixed_index = _partition(base, elem_size_temp, elem_size, start, end, pivot_index, cmp);

    size_t start1 = start;
    size_t end1 = pivot_fixed_index > 0 ? pivot_fixed_index - 1 : 0;
    size_t start2 = pivot_fixed_index + 1;
    size_t end2 = end;

    _quick_sort(base, elem_size_temp, elem_size, start1, end1, cmp);
    _quick_sort(base, elem_size_temp, elem_size, start2, end2, cmp);
}

int quick_sort(void *base, size_t size, size_t elem_size, Comparator cmp) {
    if (base == NULL || elem_size == 0 || cmp == NULL) {
        return (SORT_ERR);
    }

    if (size < 2) {
        return (SORT_OK);
    }

    void *temp = malloc(elem_size);

    if (temp == NULL) {
        return (SORT_ERR);
    }

    return (SORT_OK);
}
