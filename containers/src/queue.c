# include "queue.h"

// implementation dependencies
# include "singly_list.h"
#include <stdlib.h>

typedef struct Queue {
    SinglyList *list; 
} Queue;

Queue *queue_create(size_t elem_size) {
    if (elem_size == 0) {
        return (NULL);
    }

    Queue *q = malloc(sizeof(Queue));

    if (q == NULL) {
        return (NULL);
    }

    SinglyList *list = sl_create(elem_size);

    if (list == NULL) {
        free(q);
        return (NULL);
    }

    q->list = list;

    return (q);
}

void queue_destroy(Queue *q) {
    if (q == NULL) {
        return ;
    }

    if (q->list != NULL) {
        sl_destroy(q->list);
    }

    free(q);
}

int queue_enqueue(Queue *q, const void *elem) {
    if (q == NULL || elem == NULL) {
        return (QUEUE_ERR);
    }

    if (sl_push_back(q->list, elem) == SL_ERR) {
        return (QUEUE_ERR);
    }

    return (QUEUE_OK);
}

int queue_dequeue(Queue *q) {
    if (q == NULL) {
        return (QUEUE_ERR);
    }

    if (sl_pop_front(q->list) == SL_ERR) {
        return (QUEUE_ERR);
    }

    return (QUEUE_OK);
}

void *queue_front(const Queue *q) {
    if (q == NULL) {
        return (NULL);
    }

    return (sl_get(q->list, 0));
}

size_t queue_size(const Queue *q) {
    if (q == NULL || q->list == NULL) {
        return (0);
    }

    return (sl_size(q->list));
}

int queue_is_empty(const Queue *q) {
    return (q == NULL || sl_is_empty(q->list));
}

void queue_clear(Queue *q) {
    if (q != NULL) {
        sl_clear(q->list);
    }
}
