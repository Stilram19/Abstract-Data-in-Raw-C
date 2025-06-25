#include "priority_queue.h"
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

    PriorityQueue *pq = pq_create(sizeof(int), int_min_cmp);
    assert(pq != NULL);

    // insert N random integers
    for (size_t i = 0; i < N; ++i) {
        int val = rand();
        assert(pq_push(pq, &val) == PQ_OK);
    }

    // verify they come out in ascending order
    int last = -1;
    for (size_t i = 0; i < N; ++i) {
        int *top = pq_top(pq);
        assert(top != NULL);
        assert(*top >= last);
        last = *top;
        assert(pq_pop(pq) == PQ_OK);
    }

    assert(pq_is_empty(pq));
    pq_destroy(pq);

    puts("✓ stress test passed: inserted and removed 1 million elements in sorted order");

    return EXIT_SUCCESS;
}

