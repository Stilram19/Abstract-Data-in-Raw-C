#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sort.h"

/* comparator for integers */
int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return (0);
}

/* utility to print array (for debugging) */
void print_array(const int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* simple assertion macro */
#define ASSERT_EQUAL_ARRAY(arr, expected, n) do {          \
    for (size_t i = 0; i < n; i++) {                     \
        if (arr[i] != expected[i]) {                     \
            printf("Test failed at index %zu: got %d, expected %d\n", i, arr[i], expected[i]); \
            return (0);                                     \
        }                                                \
    }                                                    \
} while(0)

int test_selection_sort() {
    /* test cases */
    int single[] = {42};
    int sorted[] = {1, 2, 3, 4, 5};
    int reversed[] = {5, 4, 3, 2, 1};
    int random[] = {3, 1, 4, 5, 2};
    int duplicates[] = {3, 1, 3, 2, 1};

    /* expected results */
    int expected_sorted[] = {1, 2, 3, 4, 5};
    int expected_reversed[] = {1, 2, 3, 4, 5};
    int expected_random[] = {1, 2, 3, 4, 5};
    int expected_duplicates[] = {1, 1, 2, 3, 3};

    /* empty array (we can use any other array with size 0)*/
    if (insertion_sort(single, 0, sizeof(int), cmp_int) != SORT_OK) {
        printf("Empty array failed\n"); return (0);
    }

    /* single element array */
    if (insertion_sort(single, 1, sizeof(int), cmp_int) != SORT_OK) {
        printf("Single element failed\n"); return (0);
    }

    /* already sorted */
    if (insertion_sort(sorted, 5, sizeof(int), cmp_int) != SORT_OK) {
        printf("Sorted array failed\n"); return (0);
    }
    ASSERT_EQUAL_ARRAY(sorted, expected_sorted, 5);

    /* reversed array */
    if (insertion_sort(reversed, 5, sizeof(int), cmp_int) != SORT_OK) {
        printf("Reversed array failed\n"); return (0);
    }
    ASSERT_EQUAL_ARRAY(reversed, expected_reversed, 5);

    /* random array */
    if (insertion_sort(random, 5, sizeof(int), cmp_int) != SORT_OK) {
        printf("Random array failed\n"); return (0);
    }
    ASSERT_EQUAL_ARRAY(random, expected_random, 5);

    /* duplicates */
    if (insertion_sort(duplicates, 5, sizeof(int), cmp_int) != SORT_OK) {
        printf("Duplicates array failed\n"); return (0);
    }
    ASSERT_EQUAL_ARRAY(duplicates, expected_duplicates, 5);

    printf("All insertion_sort tests passed!\n");
    return (1);
}

int main() {
    if (!test_selection_sort()) {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
