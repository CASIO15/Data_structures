#ifndef QUEUE_H
#define QUEUE_H

#include "stdio.h"
#include "stdlib.h"


typedef struct node
{
    struct node *rchild;
    int data;
    int space;
    struct node *lchild;
} Node;

typedef struct linked_list
{
    struct linked_list *next;
    Node *node;
} Linked_list;

typedef struct queue
{
    int cnt_nodes;
    Linked_list *rear;
    Linked_list *front;
} Queue;

extern Node *Init_node(void);
Linked_list *Init_list(void);
Queue *Init_queue(void);

enum {False, True};
#define IsEmptyQ(b) ((b)->front == (b)->rear) ? True : False
#define IsEmpty(a) ((a) == NULL) ? True : False

Queue *Q=NULL;
Linked_list *first=NULL;

extern void enqueue(Node *);
extern Node *dequeue(void);

Node *Init_node(void)
{
    Node *n = (Node *) malloc(sizeof(Node));
    n->rchild = n->lchild = NULL;
    return n;
}

Linked_list *Init_list(void)
{
    Linked_list *l = (Linked_list *) malloc(sizeof(Linked_list));
    l->node = Init_node();
    l->next = NULL;
    return l;
}

Queue *Init_queue(void)
{
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Node *n)
{
    Linked_list *t=NULL;

    if (IsEmpty(first))
        first = Init_list();
    if (IsEmpty(Q))
        Q = Init_queue();
    if (IsEmptyQ(Q)) {
        first->node = n;
        Q->rear = first;
        Q->rear->next = NULL;
        Q->rear = first;
    } else {
        t = Init_list();
        t->node = n;
        Q->rear->next = t;
        t->next = NULL;
        Q->rear = t;
    }
}

Node *dequeue(void)
{
    Node *n=NULL;

    if (!IsEmptyQ(Q)) {
        n = first->node;
        Q->front = first;
        first = first->next;
    }
    return n;
}

#endif
