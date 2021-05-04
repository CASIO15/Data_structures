/* Stack using array */

#include "stdio.h"
#include "stdlib.h"

typedef struct stack {
    int size;
    int *s;
    int top;
} Stack;

Stack *alloc(int size);
void push(Stack *s, int el);
int pop(Stack *s);
int peek(Stack *s, int idx);
int stackTop(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);

Stack *alloc(int size)
{
    Stack *p;
    p=(Stack *)malloc(sizeof(Stack));
    p->size = size;
    p->top = -1; // Points outside the stack
    p->s = (int *)malloc(sizeof(int)*p->size);

    return p;
}

void push(Stack *s, int el)
{

    if (s->top == s->size-1)
        puts("Stack overflow !");
    else
        s->s[++(s->top)] = el; // We need to use the prefix inc (++x), because the stack pointer is initially -1
}

int pop(Stack *s)
{
    if (s->top == -1) {
        puts("Stack underflow !");
        return -1;
    }
    else
        return s->s[(s->top)--];
}

int peek(Stack *s, int idx)
{
    if (s->top < idx || idx < -1)
        puts("Invalid index !");
    else
        return s->s[s->top-idx];
}

int stackTop(Stack *s)
{
    if (s->top == -1)
        puts("The stack is empty !");
    else
        return s->s[s->top];
}

int isEmpty(Stack *s)
{
    return (s->top == -1) ? 1 : 0;
}

int isFull(Stack *s)
{
    return (s->top == s->size-1) ? 0 : 1;
}
