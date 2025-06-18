#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));
    const size_t N = 10000000; // 10 million

    Stack *s = stack_create(sizeof(int));
    assert(s != NULL);

    // push 10 million elements
    for (size_t i = 0; i < N; ++i) {
        int val = (int)i;
        assert(stack_push(s, &val) == STACK_OK);
    }
    assert(stack_size(s) == N);

    // verify top value is last pushed
    int *top = (int *)stack_top(s);
    assert(top != NULL && *top == (int)(N - 1));

    // pop all values
    for (size_t i = 0; i < N; ++i) {
        assert(stack_pop(s) == STACK_OK);
    }
    assert(stack_is_empty(s));

    printf("✅ stress test passed with %zu operations\n", N);
    stack_destroy(s);
    return 0;
}

