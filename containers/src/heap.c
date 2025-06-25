// implemented interface
# include "heap.h"

// implementation dependencies
# include "dynamic_array.h"
# include <stdlib.h>

# define INITIAL_CAPACITY 1024

typedef struct Heap {
    DynamicArray *arr;
    heap_cmp_fn cmp;
} Heap;

Heap *heap_create(size_t elem_size, heap_cmp_fn cmp) {
    if (elem_size == 0 || cmp == NULL) {
        return (NULL);
    }

    Heap *h = malloc(sizeof(Heap));

    if (h == NULL) {
        return (NULL);
    }

    h->arr = da_create(INITIAL_CAPACITY, elem_size);

    if (h->arr == NULL) {
        free(h);
        return (NULL);
    }

    h->cmp = cmp;

    return (h);
}

void heap_destroy(Heap *h) {
    if (h != NULL) {
        da_destroy(h->arr);
        free(h);
    }
}

int heap_insert(Heap *h, const void *elem) {
    if (h == NULL || h->arr == NULL || h->cmp == NULL || elem == NULL) {
        return (HEAP_ERR);
    }

    if (da_push_back(h->arr, elem) == DA_ERR) {
        return (HEAP_ERR);
    }

    size_t curr_i = da_size(h->arr) - 1;

    while (curr_i > 0) {
        size_t parent_i = (curr_i - 1) / 2;
        void *curr = da_get(h->arr, curr_i);
        void *parent = da_get(h->arr, parent_i);

        if (curr == NULL || parent == NULL) {
            return (HEAP_ERR);
        }

        if (h->cmp(curr, parent) >= 0) {
            break ;
        }

        if (da_swap(h->arr, curr_i, parent_i) == DA_ERR) {
            return (HEAP_ERR);
        }

        curr_i = parent_i;
    }

    return (HEAP_OK);
}

int heap_remove_top(Heap *h) {
    if (h == NULL || h->cmp == NULL || h->arr == NULL) {
        return (HEAP_ERR);
    }

    if (da_swap(h->arr, 0, da_size(h->arr) - 1) == DA_ERR) {
        return (HEAP_ERR);
    }

    if (da_pop(h->arr) == DA_ERR) {
        return (HEAP_ERR);
    }

    size_t curr_i = 0;
    size_t size = da_size(h->arr);
    size_t last_i = da_size(h->arr);

    while (curr_i < last_i) {
        size_t left_i = 2 * curr_i + 1;
        size_t right_i = 2 * curr_i + 2;
        size_t highest_priority_i = curr_i;

        if (left_i < size &&
            h->cmp(da_get(h->arr, left_i), da_get(h->arr, highest_priority_i)) < 0) {
            highest_priority_i = left_i;
        }

        if (right_i < size &&
            h->cmp(da_get(h->arr, right_i), da_get(h->arr, highest_priority_i)) < 0) {
            highest_priority_i = right_i;
        }

        if (highest_priority_i == curr_i) {
            break ;
        }

        da_swap(h->arr, curr_i, highest_priority_i);
        curr_i = highest_priority_i;
    }

    return (HEAP_OK);
}

void *heap_peek(const Heap *h) {
    if (h == NULL || h->arr == NULL) {
        return (NULL);
    }

    return (da_get(h->arr, 0));
}

size_t heap_size(const Heap *h) {
    if (h == NULL) {
        return (0);
    }

    return (da_size(h->arr));
}

int heap_is_empty(const Heap *h) {
    return (h == NULL || heap_size(h) == 0);
}
