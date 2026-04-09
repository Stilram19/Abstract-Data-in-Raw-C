#include "utils.h"
#include <stdint.h>
#include <string.h>

# if defined(__GNUC__) || defined(__clang__)
    # define USE_ALLOCA
    # include <alloca.h>
#endif

int swap(void *a, void *b, size_t elem_size) {
    if (a == NULL || b == NULL || elem_size == 0) {
        return (UTIL_ERR);
    }

    void *temp = NULL;

    #ifdef USE_ALLOCA
        temp = alloca(elem_size);
    #else
        temp = malloc(elem_size);

        if (temp == NULL) {
            return (UTIL_ERR);
        }
    #endif

    memcpy(temp, a, elem_size);
    memcpy(a, b, elem_size);
    memcpy(b, temp, elem_size);

    #ifndef USE_ALLOCA
        free(temp);
    #endif

    return (UTIL_OK);
}
