/* Double ended DEQueue using Linked List */

#include "stdio.h"
#include "stdlib.h"


typedef struct queue {
    int *Q; // Pointer for a dynamic array
    int size; // Size of the queue
    int front; // Front pointer
    int rear;  // Rear pointer
} QUEUE;


QUEUE *init(void);
void front_enqueue(QUEUE *q, int x);
void rear_enqueue(QUEUE *q, int x);
int front_dequeue(QUEUE *q);
int rear_dequeue(QUEUE *q);
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

void rear_enqueue(QUEUE *q, int x)
{
    if (q->rear == q->size-1 && q->front == -1)
        puts("Queue overflow !");
    else
        q->Q[++q->rear] = x;
}

int rear_dequeue(QUEUE *q)
{
    int x;
    if (q->rear == -1 && q->front == -1) {
        puts("Queue underflow");
        return -1;
    }
    x = q->Q[--q->rear];
    return x;
}

void front_enqueue(QUEUE *q, int x)
{
    if (q->rear == q->size-1 && q->front == -1)
        puts("Queue overflow");
    else {
        q->Q[q->front--] = x;
    }
}

int front_dequeue(QUEUE *q)
{
    int x;
    if (q->rear == -1 && q->front == -1) {
        puts("Queue underflow");
        return -1;
    }
    x = q->Q[++q->front];
    return x;
}

void Display(QUEUE *q)
{
    int i;

    for (i=q->front+1; i <= q->front || i <= q->rear; i++)
        printf("%d ", q->Q[i]);
}


int main(void)
{
    QUEUE *q = init();
    int i;

    for (i=0; i < q->size; i++)
        rear_enqueue(q, (i+1)*10);

    for (i=0; i < (q->size/2); i++)
        front_dequeue(q);

   for (; i > 0; i--)
       front_enqueue(q, i);

   rear_dequeue(q);
   rear_dequeue(q);
   front_dequeue(q);
   front_dequeue(q);

    Display(q); // 3 4 5 6 7 8 9 10 110 120 130 140 150 160 170 180

    return 0;
}
