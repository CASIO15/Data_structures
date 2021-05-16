/* Basic Circular Queue Implementation */

#include "stdio.h"
#include "stdlib.h"

#define EMPTY(a) ((a)->front == (a)->rear) ? 1 : 0
#define FULL(a) ((((a)->rear+1)%(a)->size) == (a)->front) ? 1 : 0


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
    q->front = q->rear = 0;

    return q;
}

void enqueue(QUEUE *q, int x)
{
    if (FULL(q))
        puts("Queue overflow");
    else {
        q->rear = (q->rear+1)%q->size;
        q->Q[q->rear] = x;
    }
}

int dequeue(QUEUE *q)
{
    int x = -1;
    if (EMPTY(q))
        puts("Queue underflow");
    else {
        q->front = (q->front+1);
        x = q->Q[q->front];
    }
    return x;
}

void Display(QUEUE *q)
{
    int i = q->front+1;

    do {
        printf("%d ", q->Q[i]);
        i = (i+1)%q->size;
    } while (i != (q->rear+1)%q->size);
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
    dequeue(q);


    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    Display(q);

    return 0;
}
