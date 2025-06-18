/* implemented interface */
# include "stack.h"

/* implementation dependencies */
# include "dynamic_array.h"
# include <stdlib.h>

# define INITIAL_CAPACITY 1024

typedef struct Stack {
    DynamicArray *arr;
} Stack;

Stack *stack_create(size_t elem_size) {
    Stack *s = malloc(sizeof(Stack));

    if (s == NULL) {
        return (NULL);
    }

    s->arr = da_create(INITIAL_CAPACITY, elem_size);

    if (s->arr == NULL) {
        free(s);
        s = NULL;
    }

    return (s);
}

void   stack_destroy(Stack *s) {
    if (s != NULL) {
        da_destroy(s->arr);
        free(s);
    }
}

int    stack_push(Stack *s, const void *src) {
    if (s == NULL || src == NULL) {
        return (STACK_ERR);
    }

    if (da_push_back(s->arr, src) == DA_ERR) {
        return (STACK_ERR);
    }

    return (STACK_OK);
}

int    stack_pop(Stack *s) {
    if (s == NULL) {
        return (STACK_ERR);
    }

    if (da_pop(s->arr) == DA_ERR) {
        return (STACK_ERR);
    }

    return (STACK_OK);
}

void  *stack_top(const Stack *s) {
    if (s == NULL) {
        return (NULL);
    }

    return (da_back(s->arr));
}

size_t stack_size(const Stack *s) {
    if (s == NULL) {
        return (0);
    }

    return (da_size(s->arr));
}

int    stack_is_empty(const Stack *s) {
    return (stack_size(s) == 0);
}

