/* Queue using Linked List */

#include "stdio.h"
#include "stdlib.h"

struct node {
    int data;
    struct node *next;
} *front=NULL,*rear=NULL;


struct node *init(void);
void enqueue(int x);
int dequeue(void);
void Display(struct node*);

struct node *init(void)
{
    struct node *p=(struct node *)malloc(sizeof(struct node));
    return p;
}

void enqueue(int x)
{
    struct node *q = init();
    q->data = x;

    if (q == NULL)
        puts("The queue is full !");
    else {
        q->data = x;
        q->next = NULL;
        if (front == NULL)
            front = rear = q;
        else {
            rear->next = q;
            rear = q;
        }
    }
}

int dequeue(void)
{
    struct node *q;
    int x = -1;

    if (front == NULL)
        puts("The queue is empty !");
    else {
        x = front->data;
        // q is temporary pointer so we will use it to release the memory when performing dequeue
        q = front;
        front = front->next;
        free((struct node *) q);
    }
    return x;
}


void Display(struct node *p)
{
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
}


int main(void)
{
    int i;

    for (i=0; i < 10; i++)
        enqueue((i+1)*10);

    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    Display(front);

    return 0;
}
