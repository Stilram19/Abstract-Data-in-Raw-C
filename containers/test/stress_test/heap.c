#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000  // 1 million elements

static int int_min_cmp(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int main(void) {
    srand((unsigned int)time(NULL));

    Heap *h = heap_create(sizeof(int), int_min_cmp);
    assert(h != NULL);

    // insert N random elements
    for (size_t i = 0; i < N; ++i) {
        int val = rand();
        assert(heap_insert(h, &val) == HEAP_OK);
    }

    // remove and ensure ordering
    int last = -1;
    for (size_t i = 0; i < N; ++i) {
        int *top = heap_peek(h);
        assert(top != NULL);
        assert(*top >= last);  // min-heap property
        last = *top;
        assert(heap_remove_top(h) == HEAP_OK);
    }

    assert(heap_is_empty(h));
    heap_destroy(h);

    puts("✓ stress test passed: inserted & removed 1 million random elements");

    return EXIT_SUCCESS;
}
