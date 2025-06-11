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
    SLNode *tail; // the last node in the list
} SinglyList;


/* helpers */

/* return NULL to indicate failure */
/* in case of failure, the function cleans everything up */
static SLNode *helper_new_node(SinglyList *list, SLNode *next, const void *src) {
    if (list == NULL || src == NULL) {
        return (NULL);
    }

    SLNode *new_node = malloc(sizeof(SLNode));

    if (new_node == NULL) {
        return (NULL);
    }

    new_node->next = next;
    new_node->data = malloc(list->elem_size);

    if (new_node->data == NULL) {
        free(new_node);
        return (NULL);
    }

    memcpy(new_node->data, src, list->elem_size);

    return (new_node);
}

/* returns a pointer to the node at the index `index` */
static SLNode *helper_get_node(const SinglyList *list, size_t index) {
    if (list == NULL) {
        return (NULL);
    }

    if (index > list->size - 1) {
        return (NULL);
    }

    SLNode *curr = list->head;

    while (index--) {
        curr = curr->next;
    }

    return (curr);
}

/* releases memory acquired previously by both node->data and node */
/* returns the next node (pointed to by `node->next`) */
static SLNode *helper_destroy_node(SLNode *node) {
    if (node == NULL) {
        return (NULL);
    }

    void *data = node->data;
    SLNode *next = node->next;

    free(node);

    if (data != NULL) {
        free(data);
    }

    return (next);
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
    sl->tail = NULL;

    return (sl);
}

/* destructor */
void sl_destroy(SinglyList *list) {
    if (list == NULL) {
        return ;
    }

    /* clear list */
    sl_clear(list);

    /* reclaim object memory block */
    free(list);
}


/* insertion */

/* pushes `src` into the front of the list */
int sl_push_front(SinglyList *list, const void *src) {
    if (list == NULL) {
        return (SL_ERR);
    }

    SLNode *new_node = helper_new_node(list, list->head, src);

    if (new_node == NULL) {
        return (SL_ERR);
    }

    /* new_node is last node only if it's the first pushed node to the list */
    if (list->tail == NULL) {
        list->tail = new_node;
    }
    list->head = new_node;
    list->size++;
    return (SL_OK);
}

/* pushes `src` into the back of the list */
int sl_push_back(SinglyList *list, const void *src) {
    if (list == NULL) {
        return (SL_ERR);
    }

    /* if list is empty, logic is same as push_front */
    if (list->tail == NULL) {
        return (sl_push_front(list, src));
    }

    SLNode *new_node = helper_new_node(list, NULL, src);

    if (new_node == NULL) {
        return (SL_ERR);
    }

    list->tail->next = new_node;
    list->tail = new_node;
    list->size++;
    return (SL_OK);
}

/* list is 0-indexed */
/* index must be within the range [0, size] */
int sl_insert_at(SinglyList *list, size_t index, const void *src) {
    if (list == NULL) {
        return (SL_ERR);
    }

    if (index > list->size) {
        return (SL_ERR);
    }

    if (index == 0) {
        return (sl_push_front(list, src));
    }

    if (index == list->size) {
        return (sl_push_back(list, src));
    }

    // helper_get_element_by_index
    // use it with index - 1
    SLNode *prev_node = helper_get_node(list, index - 1);

    if (prev_node == NULL) {
        return (SL_ERR);
    }

    SLNode *next_node = prev_node->next;

    if (next_node == NULL) {
        return (SL_ERR);
    }

    SLNode *new_node = helper_new_node(list, next_node, src);
    prev_node->next = new_node;

    list->size++;

    return (SL_OK);
}


/* deletion */

int sl_pop_front(SinglyList *list) {
    if (list == NULL) {
        return (SL_ERR);
    }

    SLNode *next = helper_destroy_node(list->head); 
    list->head = next;

    /* handling the case where list->size is 1 */
    if (next == NULL) {
        list->tail = NULL;
    }

    list->size--;
    return (SL_OK);
}

/* index must be in the range [0, size - 1] */
int sl_remove_at(SinglyList *list, size_t index) {
    if (list == NULL) {
        return (SL_ERR);
    }

    if (index > list->size - 1) {
        return (SL_ERR);
    }

    if (index == 0) {
        return (sl_pop_front(list));
    }

    SLNode *prev = helper_get_node(list, index - 1);

    if (prev == NULL) {
        return (SL_ERR);
    }

    SLNode *next = helper_destroy_node(prev->next);

    if (index == list->size - 1) {
        list->tail = prev;
    }

    prev->next = next;
    list->size--;
    return (SL_OK);
}



/* access */
void *sl_front(const SinglyList *list) {
    if (list == NULL || list->head == NULL) {
        return (NULL);
    }

    return (list->head->data);
}

void *sl_back(const SinglyList *list) {
    if (list == NULL || list->tail == NULL) {
        return (NULL);
    }

    return (list->tail->data);
}

void *sl_get(const SinglyList *list, size_t index) {
    SLNode *node = helper_get_node(list, index);

    if (node == NULL) {
        return (NULL);
    }

    return (node->data);
}



/* utilities */

size_t sl_size(const SinglyList *list) {
    if (list == NULL) {
        return (0);
    }

    return (list->size);
}

int sl_is_empty(const SinglyList *list) {
    return (list == NULL || list->size == 0);
}

/* clears the list, after this call, the list->size is 0 */
void sl_clear(SinglyList *list) {
    if (list == NULL) {
        return ;
    }

    SLNode *curr = list->head;

    /* reclaim all SLNode memory blocks */
    while (curr != NULL) {
        curr = helper_destroy_node(curr); // returns the next node
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

