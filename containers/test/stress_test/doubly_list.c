#include "doubly_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));

    const size_t N = 500000;
    DoublyList *list = dl_create(sizeof(int));
    assert(list != NULL);

    // fill with sequential values
    for (size_t i = 0; i < N; ++i) {
        int val = (int)i;
        assert(dl_push_back(list, &val) == DL_OK);
    }

    assert(dl_size(list) == N);

    // verify values at random positions
    for (size_t i = 0; i < 1000; ++i) {
        size_t index = rand() % N;
        int *value = (int *)dl_get(list, index);
        assert(value != NULL);
        assert(*value == (int)index);
    }

    // insert at beginning, middle, and end
    int head = 1111, mid = 2222, tail = 3333;

    assert(dl_insert_at(list, 0, &head) == DL_OK);
    size_t midIndex = dl_size(list) / 2;
    assert(dl_insert_at(list, midIndex, &mid) == DL_OK);
    assert(dl_insert_at(list, dl_size(list), &tail) == DL_OK);

    // verify insertions
    assert(*(int *)dl_get(list, 0) == head);
    assert(*(int *)dl_get(list, midIndex) == mid);
    assert(*(int *)dl_get(list, dl_size(list) - 1) == tail);

    // remove 5000 random positions
    for (size_t i = 0; i < 5000; ++i) {
        size_t index = rand() % dl_size(list);
        assert(dl_remove_at(list, index) == DL_OK);
    }

    printf("✅ doublyList stress test passed. Final size = %zu\n", dl_size(list));

    dl_destroy(list);
    return 0;
}

