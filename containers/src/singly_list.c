/* implemented interface */
# include "singly_list.h"

/* singly linked list's node */
typedef struct SLNode {
    void *data;
    struct SLNode *next;
} SLNode;

/* implementation dependencies */
# include <stdlib.h>
# include <string.h>

/* private data */
typedef struct SinglyList {
    size_t size; // number of nodes in the list
    size_t elem_size; // size of element in bytes
    SLNode *head; // the first node in the list
} SinglyList;


/* helpers */

/* return NULL to indicate failure */
/* in case of failure, the function cleans everything up */
static SLNode *helper_new_node(SinglyList *list, const void *src) {
    if (list == NULL || src == NULL) {
        return (NULL);
    }

    SLNode *new_node = malloc(sizeof(SLNode));

    if (new_node == NULL) {
        return (NULL);
    }

    new_node->next = NULL;
    new_node->data = malloc(list->elem_size);

    if (new_node->data == NULL) {
        free(new_node);
        return (NULL);
    }

    memcpy(new_node->data, src, list->elem_size);

    return (new_node);
}


/* constructor */
/* elem_size must be greater than 0 */
/* return NULL to indicate construction failure */
SinglyList *sl_create(size_t elem_size) {
    if (elem_size == 0) {
        return (NULL);
    }

    SinglyList *sl = malloc(sizeof(SinglyList));

    if (sl == NULL) {
        return (NULL);
    }

    sl->size = 0;
    sl->elem_size = elem_size;
    sl->head = NULL;

    return (sl);
}

/* destructor */
void sl_destroy(SinglyList *list) {
    if (list == NULL) {
        return ;
    }

    SLNode *curr = list->head;
    SLNode *next = NULL;

    /* reclaim all SLNode memory blocks */
    while (curr != NULL) {
        next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    }

    /* reclaim object memory block */
    free(list);
}


/* insertion */

int sl_push_front(SinglyList *list, const void *src) {
    // to be implemented
    return (SL_OK);
}

int sl_push_back(SinglyList *list, const void *src) {
    // to be implemented
    return (SL_OK);
}

int sl_insert_at(SinglyList *list, size_t index, const void *src) {
    // to be implemented
    return (SL_OK);
}
