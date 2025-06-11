#include "singly_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_create_destroy() {
    SinglyList *list = sl_create(sizeof(int));
    assert(list != NULL);
    assert(sl_size(list) == 0);
    sl_destroy(list);
}

void test_push_front_back() {
    SinglyList *list = sl_create(sizeof(int));
    int a = 42, b = 7;

    sl_push_front(list, &a); // [42]
    sl_push_back(list, &b);  // [42, 7]

    assert(sl_size(list) == 2);
    assert(*(int*)sl_front(list) == 42);
    assert(*(int*)sl_back(list) == 7);

    sl_destroy(list);
}

void test_insert_at() {
    SinglyList *list = sl_create(sizeof(int));
    int x = 1, y = 2, z = 3;

    sl_push_back(list, &x);         // [1]
    sl_insert_at(list, 1, &z);      // [1, 3]
    sl_insert_at(list, 1, &y);      // [1, 2, 3]

    assert(sl_size(list) == 3);
    assert(*(int*)sl_get(list, 0) == 1);
    assert(*(int*)sl_get(list, 1) == 2);
    assert(*(int*)sl_get(list, 2) == 3);

    sl_destroy(list);
}

void test_remove_at() {
    SinglyList *list = sl_create(sizeof(int));
    int x = 1, y = 2, z = 3;

    sl_push_back(list, &x); // [1]
    sl_push_back(list, &y); // [1, 2]
    sl_push_back(list, &z); // [1, 2, 3]

    sl_remove_at(list, 1);  // [1, 3]
    assert(sl_size(list) == 2);
    assert(*(int*)sl_get(list, 1) == 3);

    sl_remove_at(list, 0);  // [3]
    assert(*(int*)sl_front(list) == 3);
    assert(*(int*)sl_back(list) == 3);
    assert(sl_size(list) == 1);

    sl_remove_at(list, 0);  // []
    assert(sl_is_empty(list));

    sl_destroy(list);
}

void test_clear() {
    SinglyList *list = sl_create(sizeof(int));
    int x = 100;

    for (int i = 0; i < 5; ++i) {
        sl_push_back(list, &x);
    }

    assert(sl_size(list) == 5);
    sl_clear(list);
    assert(sl_size(list) == 0);
    assert(sl_is_empty(list));

    sl_destroy(list);
}

int main(void) {
    test_create_destroy();
    test_push_front_back();
    test_insert_at();
    test_remove_at();
    test_clear();
    printf("✅ all singly list unit tests passed!\n");
    return (0);
}

