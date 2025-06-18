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
        assert(da_push_back(arr, &i) == DA_OK);
    }
    assert(da_size(arr) == 5);

    for (int i = 0; i < 5; ++i) {
        int *value = da_get(arr, i);
        assert(value != NULL);
        assert(*value == i);
    }

    da_destroy(arr);
}

void test_back_and_pop() {
    DynamicArray *arr = da_create(3, sizeof(int));
    int vals[] = {10, 20, 30};
    for (int i = 0; i < 3; ++i) da_push_back(arr, &vals[i]);

    assert(*(int *)da_back(arr) == 30);
    assert(da_pop(arr) == DA_OK);
    assert(da_size(arr) == 2);
    assert(*(int *)da_back(arr) == 20);
    da_destroy(arr);
}

void test_insert_at_boundaries() {
    DynamicArray *arr = da_create(2, sizeof(int));
    int a = 10, b = 20, c = 30;
    da_insert_at(arr, 0, &b); // front insert
    da_insert_at(arr, 1, &c); // back insert
    da_insert_at(arr, 0, &a); // insert at front again
    assert(da_size(arr) == 3);
    assert(*((int *)da_get(arr, 0)) == 10);
    assert(*((int *)da_get(arr, 1)) == 20);
    assert(*((int *)da_get(arr, 2)) == 30);
    da_destroy(arr);
}

void test_remove_at_boundaries() {
    DynamicArray *arr = da_create(4, sizeof(int));
    int vals[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i) da_push_back(arr, &vals[i]);

    da_remove_at(arr, 0);           // remove first
    da_remove_at(arr, da_size(arr)-1); // remove last
    assert(da_size(arr) == 2);
    assert(*((int *)da_get(arr, 0)) == 2);
    assert(*((int *)da_get(arr, 1)) == 3);
    da_destroy(arr);
}

void test_set_and_get() {
    DynamicArray *arr = da_create(3, sizeof(int));
    int val = 42;
    da_push_back(arr, &val);
    int new_val = 99;
    da_set(arr, 0, &new_val);
    int *res = da_get(arr, 0);
    assert(res != NULL && *res == 99);
    da_destroy(arr);
}

void test_reallocation() {
    DynamicArray *arr = da_create(1, sizeof(int));
    for (int i = 0; i < 100; ++i) {
        assert(da_push_back(arr, &i) == DA_OK);
    }
    for (int i = 0; i < 100; ++i) {
        assert(*(int *)da_get(arr, i) == i);
    }
    assert(da_size(arr) == 100);
    da_destroy(arr);
}

void test_clear() {
    DynamicArray *arr = da_create(4, sizeof(int));
    for (int i = 0; i < 4; ++i) da_push_back(arr, &i);
    da_clear(arr);
    assert(da_size(arr) == 0);
    assert(da_get(arr, 0) == NULL);
    da_destroy(arr);
}

void test_invalid_operations() {
    DynamicArray *arr = da_create(2, sizeof(int));
    int a = 5;
    assert(da_get(arr, 0) == NULL);
    assert(da_set(arr, 0, &a) == DA_ERR);
    assert(da_insert_at(arr, 3, &a) == DA_ERR);
    assert(da_remove_at(arr, 0) == DA_ERR);
    assert(da_pop(arr) == DA_ERR);
    da_destroy(arr);
}

int main() {
    test_create_and_destroy();
    test_push_and_get();
    test_back_and_pop();
    test_insert_at_boundaries();
    test_remove_at_boundaries();
    test_set_and_get();
    test_reallocation();
    test_clear();
    test_invalid_operations();
    printf("✅ All dynamic array unit tests passed!\n");
    return 0;
}

