#include "dynamic_array.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));

    const size_t N = 500000;
    DynamicArray *arr = da_create(4, sizeof(int));
    assert(arr != NULL);

    // fill with sequential values
    for (size_t i = 0; i < N; ++i) {
        int val = (int)i;
        da_push_back(arr, &val);
    }

    assert(da_size(arr) == N);

    // verify values at random positions
    for (size_t i = 0; i < 1000; ++i) {
        size_t index = rand() % N;
        int *value = (int *)da_get(arr, index);
        assert(value != NULL);
        assert(*value == (int)index);
    }

    // overwrite random elements and verify
    for (size_t i = 0; i < 1000; ++i) {
        size_t index = rand() % N;
        int newVal = -1 * (int)index;
        da_set(arr, index, &newVal);
        int *value = (int *)da_get(arr, index);
        assert(value != NULL);
        assert(*value == newVal);
    }

    // insert at beginning, middle, and end
    int head = 1111, mid = 2222, tail = 3333;

    da_insert_at(arr, 0, &head);
    size_t midIndex = da_size(arr) / 2;
    da_insert_at(arr, midIndex, &mid);
    da_insert_at(arr, da_size(arr), &tail); // append to the end

    // verify insertions
    assert(*(int *)da_get(arr, 0) == head);
    assert(*(int *)da_get(arr, midIndex) == mid);
    assert(*(int *)da_get(arr, da_size(arr) - 1) == tail);

    // remove 5000 random positions
    for (size_t i = 0; i < 5000; ++i) {
        size_t index = rand() % da_size(arr);
        da_remove_at(arr, index);
    }

    printf("✅ full stress test passed. final size = %zu\n", da_size(arr));

    da_destroy(arr);
    return (0);
}

