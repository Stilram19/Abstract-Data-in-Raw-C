#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const size_t N = 1000000;
    Queue *q = queue_create(sizeof(int));
    assert(q != NULL);

    // enqueue N elements
    for (int i = 0; i < (int)N; ++i) {
        assert(queue_enqueue(q, &i) == QUEUE_OK);
    }

    // dequeue and check values
    for (int i = 0; i < (int)N; ++i) {
        int *front = queue_front(q);
        assert(front != NULL);
        assert(*front == i);
        assert(queue_dequeue(q) == QUEUE_OK);
    }

    assert(queue_is_empty(q));
    assert(queue_size(q) == 0);
    queue_destroy(q);

    puts("✓ stress test passed (1M ops)");
    return EXIT_SUCCESS;
}

