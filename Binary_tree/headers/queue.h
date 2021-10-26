#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"


typedef struct l_node {
    t_node *node;
    struct l_node *next;
} list_node;

typedef struct queue {
    list_node *front;
    list_node *rear;
} Queue;

#define IsEmpty(q) ((q)->rear == NULL && (q)->front == NULL) ? 1 : 0

Queue *InitQueue();
void EnQueue(Queue **queue, t_node *node);
t_node *DeQueue(Queue **queue);

#endif
