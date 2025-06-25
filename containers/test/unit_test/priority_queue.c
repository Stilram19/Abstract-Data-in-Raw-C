#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int int_min_cmp(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

static int int_max_cmp(const void *a, const void *b) {
    return (*(const int *)b - *(const int *)a);
}

static void test_min_priority_queue() {
    PriorityQueue *pq = pq_create(sizeof(int), int_min_cmp);
    assert(pq != NULL);
    assert(pq_is_empty(pq));
    assert(pq_size(pq) == 0);
    assert(pq_top(pq) == NULL);

    int vals[] = { 6, 3, 9, 1, 5 };
    for (int i = 0; i < 5; ++i) {
        assert(pq_push(pq, &vals[i]) == PQ_OK);
    }

    int last = -1;
    while (!pq_is_empty(pq)) {
        int *top = pq_top(pq);
        assert(top != NULL);
        assert(*top >= last);
        last = *top;
        assert(pq_pop(pq) == PQ_OK);
    }

    pq_destroy(pq);
    puts("✓ test_min_priority_queue passed");
}

static void test_max_priority_queue() {
    PriorityQueue *pq = pq_create(sizeof(int), int_max_cmp);
    assert(pq != NULL);

    int vals[] = { 4, 2, 10, 7 };
    for (int i = 0; i < 4; ++i) {
        assert(pq_push(pq, &vals[i]) == PQ_OK);
    }

    int last = 1e9;
    while (!pq_is_empty(pq)) {
        int *top = pq_top(pq);
        assert(top != NULL);
        assert(*top <= last);
        last = *top;
        assert(pq_pop(pq) == PQ_OK);
    }

    pq_destroy(pq);
    puts("✓ test_max_priority_queue passed");
}

static void test_empty_and_null_behavior() {
    assert(pq_push(NULL, NULL) == PQ_ERR);
    assert(pq_pop(NULL) == PQ_ERR);
    assert(pq_top(NULL) == NULL);
    assert(pq_size(NULL) == 0);
    assert(pq_is_empty(NULL));
    pq_destroy(NULL);
    puts("✓ test_empty_and_null_behavior passed");
}

int main(void) {
    test_min_priority_queue();
    test_max_priority_queue();
    test_empty_and_null_behavior();
    puts("🎉 all priority_queue tests passed");
    return EXIT_SUCCESS;
}

