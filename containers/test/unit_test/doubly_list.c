#include "doubly_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_create_and_destroy() {
    DoublyList *list = dl_create(sizeof(int));
    assert(list != NULL);
    assert(dl_size(list) == 0);
    assert(dl_is_empty(list) == 1);
    dl_destroy(list);
    printf("✅ test_create_and_destroy passed\n");
}

void test_push_and_access() {
    DoublyList *list = dl_create(sizeof(int));
    int a = 10, b = 20, c = 30;

    assert(dl_push_front(list, &a) == DL_OK);
    assert(dl_push_back(list, &b) == DL_OK);
    assert(dl_insert_at(list, 1, &c) == DL_OK);

    assert(dl_size(list) == 3);

    assert(*(int *)dl_get(list, 0) == 10);
    assert(*(int *)dl_get(list, 1) == 30);
    assert(*(int *)dl_get(list, 2) == 20);

    assert(*(int *)dl_front(list) == 10);
    assert(*(int *)dl_back(list) == 20);

    dl_destroy(list);
    printf("✅ test_push_and_access passed\n");
}

void test_pop_and_remove() {
    DoublyList *list = dl_create(sizeof(int));
    int vals[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; ++i) {
        dl_push_back(list, &vals[i]);
    }

    assert(dl_size(list) == 5);

    assert(dl_pop_front(list) == DL_OK);
    assert(dl_size(list) == 4);
    assert(*(int *)dl_front(list) == 2);

    assert(dl_pop_back(list) == DL_OK);
    assert(dl_size(list) == 3);
    assert(*(int *)dl_back(list) == 4);

    assert(dl_remove_at(list, 1) == DL_OK);  // removes index 1 (value 3)
    assert(dl_size(list) == 2);
    assert(*(int *)dl_get(list, 1) == 4);

    dl_destroy(list);
    printf("✅ test_pop_and_remove passed\n");
}

void test_clear_and_empty() {
    DoublyList *list = dl_create(sizeof(int));
    int a = 99;

    for (int i = 0; i < 100; ++i) {
        dl_push_back(list, &a);
    }

    assert(dl_size(list) == 100);
    dl_clear(list);
    assert(dl_size(list) == 0);
    assert(dl_is_empty(list));

    dl_destroy(list);
    printf("✅ test_clear_and_empty passed\n");
}

int main(void) {
    test_create_and_destroy();
    test_push_and_access();
    test_pop_and_remove();
    test_clear_and_empty();
    printf("✅ All unit tests passed.\n");
    return 0;
}

