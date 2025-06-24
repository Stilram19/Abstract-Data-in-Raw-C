#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void test_basic_queue_behavior(void) {
    Queue *q = queue_create(sizeof(int));
    assert(q != NULL);
    assert(queue_is_empty(q));
    assert(queue_size(q) == 0);

    int val = 42;
    assert(queue_enqueue(q, &val) == QUEUE_OK);
    assert(!queue_is_empty(q));
    assert(queue_size(q) == 1);

    int *front = queue_front(q);
    assert(front != NULL);
    assert(*front == 42);

    assert(queue_dequeue(q) == QUEUE_OK);
    assert(queue_is_empty(q));
    assert(queue_size(q) == 0);

    queue_destroy(q);
    puts("✓ test_basic_queue_behavior passed");
}

static void test_multiple_enqueue_dequeue(void) {
    Queue *q = queue_create(sizeof(char));
    assert(q != NULL);

    char values[] = { 'a', 'b', 'c', 'd' };
    for (int i = 0; i < 4; ++i) {
        assert(queue_enqueue(q, &values[i]) == QUEUE_OK);
    }

    assert(queue_size(q) == 4);

    for (int i = 0; i < 4; ++i) {
        char *front = queue_front(q);
        assert(front != NULL);
        assert(*front == values[i]);
        assert(queue_dequeue(q) == QUEUE_OK);
    }

    assert(queue_is_empty(q));
    queue_destroy(q);
    puts("✓ test_multiple_enqueue_dequeue passed");
}

static void test_null_operations(void) {
    assert(queue_enqueue(NULL, NULL) == QUEUE_ERR);
    assert(queue_dequeue(NULL) == QUEUE_ERR);
    assert(queue_size(NULL) == 0);
    assert(queue_front(NULL) == NULL);
    assert(queue_is_empty(NULL));
    puts("✓ test_null_operations passed");
}

int main(void) {
    test_basic_queue_behavior();
    test_multiple_enqueue_dequeue();
    test_null_operations();
    puts("🎉 all queue unit tests passed");
    return EXIT_SUCCESS;
}

