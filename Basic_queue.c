/* Basic Queue Implementation */

#include "stdio.h"
#include "stdlib.h"

#define EMPTY(a,b) ((a) == (b)) ? 1 : 0
#define FULL(a,b) ((a) == (b)) ? 1 : 0


typedef struct queue {
    int *Q; // Pointer for a dynamic array
    int size; // Size of the queue
    int front; // Front pointer
    int rear;  // Rear pointer
} QUEUE;


QUEUE *init(void);
void enqueue(QUEUE *q, int x);
int dequeue(QUEUE *q);
void Display(QUEUE *q);

QUEUE *init(void)
{
    QUEUE *q=(QUEUE *)malloc(sizeof(QUEUE));

    puts("Enter the size of the queue: ");
    scanf("%d", &q->size);

    q->Q = (int *)malloc(sizeof(int)*q->size);
    q->front = q->rear = -1;

    return q;
}

void enqueue(QUEUE *q, int x)
{
    if (FULL(q->front, q->size-1))
        puts("Queue overflow");
    else {
        ++q->rear;
        q->Q[q->rear] = x;
    }
}

int dequeue(QUEUE *q)
{
    int x;
    if (EMPTY(q->rear, q->front)) {
        puts("Queue underflow");
        return -1;
    }
    ++q->front;
    x = q->Q[q->front];
    return x;
}

void Display(QUEUE *q)
{
    static int f=0;
    if (q->Q[q->front] == q->rear || EMPTY(q->front, q->rear))
        ;
    else {
        printf("%d ", q->Q[++q->front]);
        Display(q);
    }
}


int main(void)
{
    QUEUE *q = init();
    int i;

    for (i=0; i < q->size; i++)
        enqueue(q, i+1);

    dequeue(q);
    dequeue(q);
    dequeue(q);
    Display(q);

    return 0;
}
