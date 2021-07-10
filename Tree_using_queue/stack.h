#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H

#include "stdio.h"
#include "queue.h"

typedef struct stack
{
    Linked_list *top;
} Stack;

#define IsStackFull(s) ((s) == NULL) ? True : False

extern void push(Node *);
extern Node *pop(void);

Stack *InitStack(void);

Stack *InitStack(void)
{
    Stack *new = (Stack *) malloc(sizeof(Stack));
    new->top=NULL;
    return new;
}

Stack *s=NULL;

void push(Node *n)
{
    Linked_list *t=Init_list();

    if (IsEmpty(s))
        s = InitStack();
    if (IsEmpty(s->top)) {
        s->top = Init_list();
        s->top->node = n;
        t->next = s->top->next = NULL;
    } else if (!IsStackFull(s)) {
        t->next = s->top;
        t->node = n;
        s->top = t;
    }
}

Node *pop(void)
{
    Node *n = NULL;
    Linked_list *t=NULL;

    if (!IsEmpty(s->top)) {
        n = s->top->node;
        t = s->top->next;
        free((Linked_list *) s->top);
        s->top = t;
    }
    return n;
}

#endif
