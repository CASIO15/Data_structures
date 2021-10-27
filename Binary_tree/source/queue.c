#include "queue.h"

Queue *InitQueue()
{
    Queue *new;

    if ((new = malloc(sizeof(Queue))) == NULL) {
        return NULL;
    }
    new->front = new->rear = NULL;

    return new;
}

void EnQueue(Queue **queue, t_node *node)
{
    list_node *new_node;

    if ((new_node = malloc(sizeof(list_node))) == NULL) {
        return;
    }

    new_node->node = node;
    new_node->next = NULL;

    if (*queue == NULL) {
        if ((*queue = InitQueue()) == NULL)
            return;
        (*queue)->front = (*queue)->rear = new_node;
        (*queue)->rear->next = NULL;
        return;
    }

    (*queue)->rear->next = new_node;
    (*queue)->rear = new_node;
}

t_node *DeQueue(Queue **queue)
{
    if (IsEmpty(*queue) == 1)
        return NULL;

    list_node *current = (*queue)->front;
    t_node *return_val = current->node;

    (*queue)->front = (*queue)->front->next;
    free(current);

    if ((*queue)->front == NULL)
        (*queue)->rear = NULL;

    return return_val;
}
