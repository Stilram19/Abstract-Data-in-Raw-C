#include "singly_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));

    const size_t N = 500000;
    SinglyList *list = sl_create(sizeof(int));
    assert(list != NULL);

    // push N sequential values to the back
    for (size_t i = 0; i < N; ++i) {
        int val = (int)i;
        assert(sl_push_back(list, &val) == SL_OK);
    }

    assert(sl_size(list) == N);

    // verify random access to 1000 values
    for (size_t i = 0; i < 1000; ++i) {
        size_t index = rand() % N;
        int *value = (int *)sl_get(list, index);
        assert(value != NULL);
        assert(*value == (int)index);
    }

    // insert at head, middle, and tail
    int head = 1111, mid = 2222, tail = 3333;

    assert(sl_insert_at(list, 0, &head) == SL_OK);
    size_t mid_index = sl_size(list) / 2;
    assert(sl_insert_at(list, mid_index, &mid) == SL_OK);
    assert(sl_insert_at(list, sl_size(list), &tail) == SL_OK);

    assert(*(int *)sl_get(list, 0) == head);
    assert(*(int *)sl_get(list, mid_index) == mid);
    assert(*(int *)sl_back(list) == tail);

    // remove 5000 random elements
    for (size_t i = 0; i < 5000; ++i) {
        size_t index = rand() % sl_size(list);
        assert(sl_remove_at(list, index) == SL_OK);
    }

    printf("✅ full stress test passed. final size = %zu\n", sl_size(list));

    sl_destroy(list);
    return 0;
}

