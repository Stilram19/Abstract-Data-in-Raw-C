#include <assert.h>
#include <stdio.h>
#include "dynamic_array.h"

void test_create_and_destroy() {
    DynamicArray *arr = da_create(4, sizeof(int));
    assert(arr != NULL);
    assert(da_size(arr) == 0);
    assert(da_capacity(arr) == 4);
    da_destroy(arr);
}

void test_push_and_get() {
    DynamicArray *arr = da_create(2, sizeof(int));
    for (int i = 0; i < 5; ++i) {
        da_push_back(arr, &i);
    }
    assert(da_size(arr) == 5);

    for (int i = 0; i < 5; ++i) {
        int *value = da_get(arr, i);
        assert(value != NULL);
        assert(*value == i);
    }

    da_destroy(arr);
}

void test_set() {
    DynamicArray *arr = da_create(3, sizeof(int));
    int a = 42, b = 99;
    da_push_back(arr, &a);
    da_set(arr, 0, &b);
    int *val = da_get(arr, 0);
    assert(*val == 99);
    da_destroy(arr);
}

void test_insert_at() {
    DynamicArray *arr = da_create(2, sizeof(int));
    int a = 1, b = 2, c = 3;
    da_push_back(arr, &a);
    da_push_back(arr, &c);
    da_insert_at(arr, 1, &b); // should now be 1,2,3
    assert(da_size(arr) == 3);
    assert(*((int *)da_get(arr, 0)) == 1);
    assert(*((int *)da_get(arr, 1)) == 2);
    assert(*((int *)da_get(arr, 2)) == 3);
    da_destroy(arr);
}

void test_remove_at() {
    DynamicArray *arr = da_create(4, sizeof(int));
    int vals[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; ++i) {
        da_push_back(arr, &vals[i]);
    }
    da_remove_at(arr, 1); // remove 20
    assert(da_size(arr) == 3);
    assert(*((int *)da_get(arr, 0)) == 10);
    assert(*((int *)da_get(arr, 1)) == 30);
    assert(*((int *)da_get(arr, 2)) == 40);
    da_destroy(arr);
}

int main() {
    test_create_and_destroy();
    test_push_and_get();
    test_set();
    test_insert_at();
    test_remove_at();
    printf("✅ all tests passed!\n");
    return 0;
}

