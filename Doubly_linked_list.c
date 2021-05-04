#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *prev;
    int data;
    struct Node *next;
}  Doubly_Linked_list;

Doubly_Linked_list *head=NULL;

void create_dobuly(const int A[], int n);
void Rdisplay_doubly(Doubly_Linked_list *p);
Doubly_Linked_list *alloc(void);
int len(Doubly_Linked_list *p);
void insert(Doubly_Linked_list *p, int idx, int x);
void delete(Doubly_Linked_list *p, int idx);
void reverse(Doubly_Linked_list *p);


Doubly_Linked_list *alloc(void)
{
    return (Doubly_Linked_list *) malloc(sizeof(Doubly_Linked_list));
}

void create_dobuly(const int A[], int n)
{
    int i;
    Doubly_Linked_list *q, *t;

    head = alloc();
    head->prev = NULL;
    head->data = A[0];
    q = head;

    for (i=1; i<n; i++) {
        t = alloc();
        t->prev = q;
        t->data = A[i];
        t->next = NULL;
        q->next = t;
        q = t;
    }
}

void reverse(Doubly_Linked_list *p)
{
    Doubly_Linked_list *temp;
    while (p) {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        p=p->prev;
        if (p)
            head = p;
    }
}

void insert(Doubly_Linked_list *p, int idx, int x)
{
    int i=0, length=len(p);
    Doubly_Linked_list *q=alloc(), *t=NULL;
    q->data = x;

    if (idx < 0 || idx > length)
        printf("Invalid index !\n");
    else {
        if (idx == 0) {
            p->prev = q;
            q->next = p;
            q->prev = NULL;
            head = q;
        } else {
            while (p && i < idx)
                t=p, p=p->next, i++;
            if (idx == length) {
                t->next = q;
                q->prev = t;
                q->next = NULL;
            } else {
                q->prev = t;
                q->next = p;
                p->prev = q;
                t->next = q;
            }
        }
    }
}

void delete(Doubly_Linked_list *p, int idx)
{
    Doubly_Linked_list *q;
    int i, length=len(p);

    if (idx > length || idx < 0)
        printf("Error: Invalid index !\n");
    else {
        if (idx == 0) {
            head = p->next;
            if (head)
                head->prev = NULL;
            free(p);
        } else {
            for (q=p, i=0; i<idx; i++, q=p, p=p->next);
            q->next = p->next;
            p->next = p->prev;
            free(p);
        }
    }
}

int len(Doubly_Linked_list *p)
{
    int i;
    for (i=0; p; p=p->next, i++);
    return i;
}

void Rdisplay_doubly(Doubly_Linked_list *p)
{
    if (p) {
        (p->prev != NULL) ? printf(" <-(%d)->", p->data) : printf("NULL <-(%d)-> ", p->data);
        Rdisplay_doubly(p->next);
    } else
        printf("NULL\n");
}
