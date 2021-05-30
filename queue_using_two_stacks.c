#include "stdio.h"
#include "stdlib.h"

typedef struct stack
{
    int size;
    int *A;
    int top;
} STACK;

typedef struct queue
{
    STACK **s;
} QUEUE;

STACK *stack_init(int n);
QUEUE *queue_init(int n);
void push(STACK *, int);
int pop(STACK *);
void enqueue(QUEUE *, int);
int dequeue(QUEUE *);


STACK *stack_init(int n)
{
    STACK *s = (STACK *) malloc(sizeof(STACK));
    s->size = n;
    s->A = (int *) malloc(sizeof(int)*n);
    s->top = -1;
    return s;
}

QUEUE *queue_init(int n)
{
    int i;
    QUEUE *q = (QUEUE *) malloc(sizeof(QUEUE));
    q->s = (STACK **) malloc(sizeof(STACK) * 2);

    for (i = 0; i < 2; i++)
        q->s[i] = (stack_init(n));
    return q;
}

void push(STACK *s, int n)
{
    if (s->top == s->size-1)
        puts("Stack overflow !");
    else
        s->A[s->top++] = n;
}

int pop(STACK *s)
{
    int x = -1;
    if (s->top == -1)
        puts("The stack is empty");
    else
        x = s->A[--s->top];
    return x;
}

void enqueue(QUEUE *q, int n)
{
    if (q->s[0]->top == q->s[0]->size-1 || q->s[1]->top == q->s[1]->size-1)
        puts("The queue is full !");
    else {
        if (q->s[0]->top < q->s[0]->size)
            push(q->s[0], n);
        else if (q->s[1]->top < q->s[1]->size && q->s[0]->top == -1)
            push(q->s[1], n);
    }
}

int dequeue(QUEUE *q)
{
    int x = -1;

    if (q->s[0]->top == -1 && q->s[1]->top == -1)
        puts("The queue is empty !");
    else {
        if (q->s[0]->top == q->s[0]->size-1) {
            while (q->s[0]->top > 0) {
                x = pop(q->s[0]);
                push(q->s[1], x);
            }
            x = pop(q->s[0]);
        } else if (q->s[0]->top == -1 && q->s[1]->top < q->s[1]->size)
            if (q->s[1]->top > -1)
                x = pop(q->s[1]);
    }
    return x;
}


int main(void)
{
    int i, n;

    puts("Enter the size of the stack:");
    scanf("%d", &n);

    STACK *s = stack_init(n);
    QUEUE *q = queue_init(n);

    for (i=0; i < s->size; i++)
        enqueue(q, i);

    for (i=s->size; i > 0; i--) {
        printf("%d ", dequeue(q));
        printf("Top: %d || %d\n", q->s[0]->top, q->s[1]->top);
    }

    return 0;
}
