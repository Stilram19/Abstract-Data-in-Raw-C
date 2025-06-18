#include "stack.h"
#include <assert.h>
#include <stdio.h>

void test_stack_create_and_destroy() {
    Stack *s = stack_create(sizeof(int));
    assert(s != NULL);
    assert(stack_size(s) == 0);
    assert(stack_is_empty(s));
    stack_destroy(s);
}

void test_stack_push_and_top() {
    Stack *s = stack_create(sizeof(int));
    int vals[] = {10, 20, 30};

    for (int i = 0; i < 3; ++i) {
        assert(stack_push(s, &vals[i]) == STACK_OK);
        int *top = (int *)stack_top(s);
        assert(top != NULL);
        assert(*top == vals[i]);
    }

    assert(stack_size(s) == 3);
    stack_destroy(s);
}

void test_stack_pop() {
    Stack *s = stack_create(sizeof(int));
    int a = 42, b = 99;
    stack_push(s, &a);
    stack_push(s, &b);
    assert(stack_size(s) == 2);

    assert(stack_pop(s) == STACK_OK);
    assert(stack_size(s) == 1);
    int *top = (int *)stack_top(s);
    assert(*top == 42);

    assert(stack_pop(s) == STACK_OK);
    assert(stack_is_empty(s));

    // popping from empty stack should still be safe
    assert(stack_pop(s) == STACK_ERR);
    stack_destroy(s);
}

int main() {
    test_stack_create_and_destroy();
    test_stack_push_and_top();
    test_stack_pop();
    printf("✅ All stack unit tests passed!\n");
    return 0;
}

