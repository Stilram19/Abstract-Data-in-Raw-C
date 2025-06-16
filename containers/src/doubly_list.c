// implemented interface
# include "doubly_list.h"

// implementation dependencies
# include <stdlib.h>
# include <string.h>
  
typedef struct DLNode {
    void            *data;
    struct DLNode   *prev;
    struct DLNode   *next;
}DLNode;

/* opaque doubly list type */
typedef struct DoublyList {
    size_t size;
    size_t elem_size;
    DLNode *head; // dummy node (first node is pointed to by head->next)
    DLNode *tail; // dummy node (last node is pointed to by tail->prev)
}DoublyList;


/* helpers */

/* return NULL to indicate failure */
/* in case of failure, the function cleans everything up */
static DLNode *helper_new_node(DoublyList *list, DLNode *prev, DLNode *next, const void *src) {
    /* prev and next shouldn't be NULL, since we have head and tail dummy nodes */
    if (list == NULL || src == NULL || prev == NULL || next == NULL) {
        return (NULL);
    }

    DLNode *new_node = malloc(sizeof(DLNode));

    if (new_node == NULL) {
        return (NULL);
    }
 
    new_node->prev = prev;
    new_node->next = next;
    new_node->data = malloc(list->elem_size);

    if (new_node->data == NULL) {
        free(new_node);
        return (NULL);
    }

    memcpy(new_node->data, src, list->elem_size);

    return (new_node);
}

static DLNode *helper_delete_node(DoublyList *list, DLNode *node) {
    if (node == NULL || node == list->head || node == list->tail) {
        return (NULL); 
    }

    void *data = node->data;
    DLNode *next = node->next;
    DLNode *prev = node->prev;

    // prev and next can't be NULL in a correct implementation (head and tail are dummy nodes)
    if (prev == NULL || next == NULL) {
        return (NULL);
    }

    // adjusting links
    prev->next = next;
    next->prev = prev;

    // releasing acquired memory
    free(node);

    if (data != NULL) {
        free(data);
    }

    return (next);
}

/* returns a pointer to the node at the index `index` */
static DLNode *helper_get_node(const DoublyList *list, size_t index) {
    if (list == NULL) {
        return (NULL);
    }

    if (index > list->size - 1) {
        return (NULL);
    }

    DLNode *curr = list->head->next;

    while (index--) {
        curr = curr->next;
    }

    return (curr);
}


/* constructor / destructor */
DoublyList *dl_create(size_t elem_size) {
    // mem allocation
    DoublyList *dl = malloc(sizeof(DoublyList));

    if (dl == NULL) {
        return (NULL);
    }

    dl->head = malloc(sizeof(DLNode));
    if (dl->head == NULL) {
        free(dl);
        return (NULL);
    }

    dl->tail = malloc(sizeof(DLNode));
    if (dl->tail == NULL) {
        free(dl);
        return (NULL);
    }

    // links initialization
    dl->head->prev = NULL;
    dl->tail->next = NULL;
    dl->head->next = dl->tail;
    dl->tail->prev = dl->head;

    // init size
    dl->elem_size = elem_size;
    dl->size = 0;

    return (dl);
}

void dl_destroy(DoublyList *list) {
    /* clear list */
    dl_clear(list);

    free(list->head);
    free(list->tail);
    free(list);
}



/* insertion */

int dl_push_front(DoublyList *list, const void *src) {
    if (list == NULL || list->head == NULL || src ==  NULL) {
        return (DL_ERR);
    }

    DLNode *old_head_next = list->head->next;

    if (old_head_next == NULL) {
        return (DL_ERR);
    }

    DLNode *new_node = helper_new_node(list, list->head, old_head_next, src);

    if (new_node == NULL) {
        return (DL_ERR);
    }

    old_head_next->prev = new_node;
    list->head->next = new_node;
    list->size++;
    return (DL_OK);
}

int dl_push_back(DoublyList *list, const void *src) {
    if (list == NULL || src == NULL || list->tail == NULL) {
        return (DL_ERR);
    }

    DLNode *old_tail_prev = list->tail->prev;
    if (old_tail_prev == NULL) {
        return (DL_ERR);
    }

    DLNode *new_node = helper_new_node(list, old_tail_prev, list->tail, src);
    if (new_node == NULL) {
        return (DL_ERR);
    }

    old_tail_prev->next = new_node;
    list->tail->prev = new_node;
    list->size++;
    return (DL_OK);
}

int dl_insert_at(DoublyList *list, size_t index, const void *src) {
    if (list == NULL || src == NULL || index > list->size) {
        return (DL_ERR);
    }

    if (index == 0) {
        return (dl_push_front(list, src));
    }

    if (index == list->size) {
        return (dl_push_back(list, src));
    }

    DLNode *old_node = helper_get_node(list, index);

    if (old_node == NULL || old_node->prev == NULL) {
        return (DL_ERR);
    }

    DLNode *new_node = helper_new_node(list, old_node->prev, old_node, src);

    if (new_node == NULL) {
        return (DL_ERR);
    }

    old_node->prev->next = new_node;
    old_node->prev = new_node;
    
    list->size++;
    return (DL_OK);
}



/* utilities */

/* clears the list, after this call, the list->size is 0 */
void dl_clear(DoublyList *list) {
    if (list == NULL || list->head == NULL) {
        return ;
    }

    DLNode *curr = list->head->next;

    /* deletes all DLNode blocks (freeing memory & deleting) */
    while (curr != list->tail) {
        curr = helper_delete_node(list, curr); // returns the next node
    }

    list->size = 0;
}

