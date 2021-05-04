/* Stack using linked list */

#include "stdio.h"
#include "stdlib.h"


typedef struct Node {
    int data;
    struct Node *next;
} Stack;

enum BOOL {FALSE, TRUE};

Stack *top=NULL;

Stack *alloc(void );
void push(int n);
int empty(void);
int full(void);
void Display(Stack *s);
int pop(void);
int peek(int idx);
int stackTop(void);

Stack *alloc(void)
{
    return (Stack *)malloc(sizeof(Stack));
}

void push(int n)
{
    Stack *q=alloc();

    if (!full()) {
        if (top == NULL) {
            top = q;
            q->data = n;
            q->next = NULL;
        } else {
            q->next = top;
            top = q;
            top->data = n;
        }
    } else
        printf("Stack overflow !\n");
}

int empty(void)
{
    return (top == NULL) ? TRUE : FALSE;
}

int full(void)
{
    int state;
    Stack *t=alloc();
    (state=(t == NULL)) ? TRUE : FALSE;
    free((Stack *) t);
    return state;
}

void Display(Stack *s)
{
    if (s) {
        printf("%d\n", s->data);
        Display(s->next);
    }
}

int pop(void)
{
    Stack *new_top;
    int x=-1;

    if (empty())
        return x;
    x = top->data;
    new_top = top->next;
    free((Stack *) top);
    top = new_top;
    return x;
}

int peek(int idx)
{
    Stack *p=top;
    if (empty())
        return -1;
    else {
        while (p && (--idx) > 0)
            p=p->next;
        return p->data;
    }
}

int stackTop(void)
{
    if (top)
        return top->data;
    else
        return -1;
}
