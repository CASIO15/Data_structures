/* Priority Queue */

#include "stdio.h"
#include "stdlib.h"


typedef struct linkedList {
    int data;
    struct linkedList* next;
    struct linkedList* front;
    struct linkedList* rear;
} LinkedList;


typedef struct queue {
    int size;
    LinkedList **Q;
} QUEUE;


QUEUE* Qinit(void);
LinkedList* Linit(void);
void enqueue(QUEUE*, int n, int prec);
int dequeue(QUEUE*);
void Display(QUEUE*);
void freeQ(QUEUE*);

QUEUE* Qinit(void)
{
    int i;
    QUEUE* new = (QUEUE*)malloc(sizeof(QUEUE));
    puts("Enter the number of priority queues:");
    scanf("%d", &new->size);
    new->Q = (LinkedList **) malloc(sizeof(LinkedList)*new->size);

    for (i = 0; i < new->size; i++) {
        new->Q[i] = Linit();
        new->Q[i]->front = NULL;
        new->Q[i]->rear = NULL;
    }
    return new;
}

LinkedList* Linit(void)
{
    LinkedList* new = (LinkedList*)malloc(sizeof(LinkedList));
    return new;
}

void enqueue(QUEUE* q, int n, int prec)
{
    LinkedList* p = Linit();
    p->data = n;
    p->next = NULL;

    if (q == NULL)
        puts("The queue is full !");
    else {
        if (q->Q[prec]->front == NULL) {
            q->Q[prec]->front = Linit();
            q->Q[prec]->rear = Linit();
            q->Q[prec]->front = q->Q[prec]->rear = q->Q[prec]->next = p;
        }
        else {
            q->Q[prec]->rear->next = q->Q[prec]->next = p;
            q->Q[prec]->rear = p;
        }
    }
}

int dequeue(QUEUE* q)
{
    int x = -1;
    static unsigned int prec = 0;
    LinkedList* p;

    if (q->Q[prec]->front == NULL) {
        puts("The queue is empty !");
        prec++;
    }
    else {
        if (q->Q[prec]->front != NULL) {
            x = q->Q[prec]->front->data;
            p = q->Q[prec]->front;
            q->Q[prec]->front = q->Q[prec]->front->next;
            free((LinkedList*)p);
        }
    }
    return x;
}

void Display(QUEUE* q)
{
    int i;

    for (i = 0; i < q->size; i++) {
        if (q->Q[i]->front == NULL)
            continue;
        else {
            while (q->Q[i]->front) {
                printf("%d -> ", q->Q[i]->front->data);
                q->Q[i]->front = q->Q[i]->front->next;
            }
            printf(" |Priority = %d|\n", i);
        }
    }
}

void freeQ(QUEUE* q)
{
    int i;

    for (i = 0; i < q->size; i++) {
        while (q->Q[i]->front) {
            free((LinkedList*)q->Q[i]->front);
            q->Q[i]->front = q->Q[i]->front->next;
        }
        free((LinkedList*)q->Q[i]);
    }
}

int main(void)
{
    QUEUE* q = Qinit();
    int i, n;

    for (i = 0; i < q->size; i++)
        for (n = 0; n < q->size; n++)
            enqueue(q, ((n + 1) * (i + 1)), i);

   for (i=0; i<25; i++)
       dequeue(q);

    Display(q);
    freeQ(q);

    return 0;
}
