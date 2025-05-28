// implemented interface
# include "dynamic_array.h"

// implementation dependencies
# include <stdlib.h>
# include <assert.h>

DynamicArray *da_create(size_t initial_capacity) {
    assert(initial_capacity > 0);
    DynamicArray *da = malloc(sizeof(DynamicArray));

    if (da == NULL) {
        return (NULL);
    }

    da->data = malloc(initial_capacity * sizeof(int));

    if (da->data == NULL) {
        free(da);
        return (NULL);
    }

    da->size = 0;
    da->capacity = initial_capacity;

    return (da);
}
