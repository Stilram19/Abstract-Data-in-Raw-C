#include "utils.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int swap(void *a, void *b, void *temp, size_t elem_size) {
    if (a == NULL || b == NULL || temp == NULL || elem_size == 0) {
        return (UTIL_ERR);
    }

    if (a == b) {
        return (UTIL_OK);
    }

    memcpy(temp, a, elem_size);
    memcpy(a, b, elem_size);
    memcpy(b, temp, elem_size);

    return (UTIL_OK);
}
