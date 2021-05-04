#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
}  Linked_list;

Linked_list *head=NULL;

Linked_list *alloc(void);
void create(const int A[], int n);
void display_circular(Linked_list *p);
void insert(Linked_list *p, int x, int idx);
int length(Linked_list *p);
void delete(Linked_list *p, int idx);
void free_node(Linked_list *p);
void reverse(Linked_list *p);

void free_node(Linked_list *p)
{
    free((Linked_list *) p);
}

Linked_list *alloc(void)
{
    return (Linked_list *) malloc(sizeof(Linked_list));
}

int length(Linked_list *p)
{
    int i=0;
    do {
        p=p->next, i++;
    } while (p->next != head);
    return i;
}

void delete(Linked_list *p, int idx)
{
    Linked_list *t;
    int i=0;

    if (idx < 0 || idx > length(p))
        printf("Invalid index !\n");
    else {
        if (idx == 0) {
            t = p;
            // We need to traverse across all the list, so we point the last node to the new head.
            while (p->next != head)
                p = p->next;
            head = t->next;
            p->next = head;
            free_node(t);
        } else {
            while (p->next != head && i < idx)
                t = p, p = p->next, i++;
            t->next = p->next;
        }
    }
}

void reverse(Linked_list *p)
{
    Linked_list *q=NULL, *t=NULL, *first=p;

    while (p->next != head) {
        t = q;
        q = p;
        p = p->next;
        q->next = t;
    }
    head = p;
    p->next = q;
    q->next = t;
    first->next = head;
}

void create(const int A[], int n)
{
    Linked_list *t, *last;
    int i;

    head = alloc();
    head->data = A[0];
    head->next = head;
    last = head;

    for (i=1; i < n; i++)
    {
        t = alloc();
        t->data = A[i];
        t->next = last->next;
        last->next = t;
        last = t;
    }
}

void display_circular(Linked_list *p)
{
    static int flag = 1;
    if (p && flag) {
        printf("%d -> ", p->data);
        if (p->next == head)
            flag = 0;
        display_circular(p->next);
    } else
        printf("\b\b\b\b    ");
}

void insert(Linked_list *p, int x, int idx)
{
    int i;
    Linked_list *q=alloc(), *t=NULL;
    q->data = x;

    if (idx < 0 || idx > length(head)+1)
        printf("Invalid index !\n");
    else {
        if (idx == 0) {
            if (head == NULL) {
                head = q;
                q->next = head;
            } else {
                t = p;
                do {
                    p = p->next;
                } while (p->next != head);

                head = q;
                q->next = t;
                p->next = head;
            }
        } else {
            for (i = 0, t = p; i < idx; t = p, p = p->next, i++)
                ;
            t->next = q;
            q->next = p;
        }
    }
}
