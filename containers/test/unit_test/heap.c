#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int int_min_cmp(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

static int int_max_cmp(const void *a, const void *b) {
    return (*(const int *)b - *(const int *)a);
}

static void test_min_heap_basic() {
    Heap *h = heap_create(sizeof(int), int_min_cmp);
    assert(h != NULL);
    assert(heap_is_empty(h));
    assert(heap_size(h) == 0);
    assert(heap_peek(h) == NULL);

    int vals[] = { 5, 3, 7, 1, 4 };
    for (int i = 0; i < 5; ++i) {
        assert(heap_insert(h, &vals[i]) == HEAP_OK);
    }

    assert(heap_size(h) == 5);
    int last = -1;
    while (!heap_is_empty(h)) {
        int *top = heap_peek(h);
        assert(top != NULL);
        assert(*top >= last);
        last = *top;
        assert(heap_remove_top(h) == HEAP_OK);
    }

    assert(heap_size(h) == 0);
    heap_destroy(h);
    puts("✓ test_min_heap_basic passed");
}

static void test_max_heap_order() {
    Heap *h = heap_create(sizeof(int), int_max_cmp);
    assert(h != NULL);

    int vals[] = { 2, 10, 1, 6, 7 };
    for (int i = 0; i < 5; ++i) {
        assert(heap_insert(h, &vals[i]) == HEAP_OK);
    }

    int last = 1e9;
    while (!heap_is_empty(h)) {
        int *top = heap_peek(h);
        assert(top != NULL);
        assert(*top <= last);
        last = *top;
        assert(heap_remove_top(h) == HEAP_OK);
    }

    heap_destroy(h);
    puts("✓ test_max_heap_order passed");
}

static void test_remove_from_empty() {
    Heap *h = heap_create(sizeof(int), int_min_cmp);
    assert(h != NULL);
    assert(heap_remove_top(h) == HEAP_ERR);
    assert(heap_peek(h) == NULL);
    heap_destroy(h);
    puts("✓ test_remove_from_empty passed");
}

static void test_null_inputs() {
    assert(heap_insert(NULL, NULL) == HEAP_ERR);
    assert(heap_remove_top(NULL) == HEAP_ERR);
    assert(heap_peek(NULL) == NULL);
    assert(heap_size(NULL) == 0);
    assert(heap_is_empty(NULL));
    heap_destroy(NULL);
    puts("✓ test_null_inputs passed");
}

int main(void) {
    test_min_heap_basic();
    test_max_heap_order();
    test_remove_from_empty();
    test_null_inputs();
    puts("🎉 all heap unit tests passed");
    return EXIT_SUCCESS;
}

