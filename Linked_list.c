#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

typedef struct Node {
    int data;
    struct Node *next;
}  Linked_list;

Linked_list *first=NULL;
Linked_list *second=NULL;
Linked_list *third=NULL; // Used for merging


Linked_list *alloc(void);
void Display(Linked_list *p);
void create(const int A[], int n);
void create2(const int A[], int n);
void merge(Linked_list *p1, Linked_list *p2);
int linked_list_length(Linked_list *);
int sum(Linked_list *);
int recursive_sum(Linked_list *);
int find_max(Linked_list *);
int find_min(Linked_list *p);
int search(Linked_list *p, int key);
int recur_search(Linked_list *p, int key);
void swap_nodes(Linked_list *p1, Linked_list *p2, Linked_list *p3);
void insert(Linked_list *p, int idx, int x);
// Inserting always at last index, constant time | O(1) |
// we don't need to traverse the link list
void insert_last(int x);
void insert_sorted(Linked_list *p, int x);
void delete(Linked_list *p, int pos);
void free_node(Linked_list *p);
void check_sorted(Linked_list *p);
void delete_dup(Linked_list *p);
void reverse_elements(Linked_list *p);
void reverse_links(Linked_list *p);
void reverse(Linked_list *p);
void recursive_reverse(Linked_list *q, Linked_list *p);
void concat(Linked_list *p1, Linked_list *p2);
int check_loop(Linked_list *p);

void free_node(Linked_list *p)
{
    free((Linked_list *) p);
}

Linked_list *alloc(void)
{
    return (Linked_list *) malloc(sizeof(Linked_list));
}

int check_loop(Linked_list *p)
{
    Linked_list *q, *t;
    q=t=p;

    do {
        q=q->next;
        t=t->next;
        t = (t) ? t->next : NULL;
    } while (t && q && t != q);

    return (t==q) ? 1 : 0;
}

void merge(Linked_list *p1, Linked_list *p2)
{
    Linked_list *l;
    if (p1->data < p2->data) {
        third = l = p1;
        p1 = p1->next;
        third->next = NULL;
    } else {
        third = l = p2;
        p2 = p2->next;
        third->next = NULL;
    }

    while (p1 && p2) {
        if (p1->data < p2->data) {
            l->next = p1;
            l = p1;
            p1 = p1->next;
            l->next = NULL;
        } else {
            l->next = p2;
            l = p2;
            p2 = p2->next;
            l->next = NULL;
        }
    }
    if (p1)
        l->next = p1;
    if (p2)
        l->next = p2;
}

void create(const int A[], int n)
{
    int i;
    Linked_list *t, *last;
    first = alloc(); // allocate space for head pointer
    first->data = A[0];
    first->next = NULL;
    last = first; // last points at first

    for (i=1; i < n; i++) {
        t = alloc(); // allocating space for t
        t->data = A[i]; // storing A[i] as data
        t->next = NULL;
        last->next = t; // last->next points at t
        last = t; // last points at t
    }
}

void create2(const int A[], int n) {
    int i;
    Linked_list *t, *last;
    second = alloc(); // allocate space for head pointer
    second->data = A[0];
    second->next = NULL;
    last = second; // last points at first

    for (i = 1; i < n; i++) {
        t = alloc(); // allocating space for t
        t->data = A[i]; // storing A[i] as data
        t->next = NULL;
        last->next = t; // last->next points at t
        last = t; // last points at t
    }
}

void concat(Linked_list *p1, Linked_list *p2)
{
    while (p1->next != NULL)
        p1=p1->next;
    p1->next = p2->next;
}

void recursive_reverse(Linked_list *q, Linked_list *p)
{
    if (p) {
        recursive_reverse(p, p->next); // recursive traversal along the linked list, at the end q = last element & p = NULL
        p->next = q; // At returning time p->next = q
    } else
        first = q; // Last recursive iteration, p will be NULL, than first = q | last element before NULL
}

void insert_last(int x)
{
  
/*        ### IF first == NULL ###
 * -----------------------------------------
 * temp = x
 * temp->next = NULL
 * first allocate memory
 * first = temp = last -> move last to temp
 * -----------------------------------------
 *        ### ELSE ###
 * -----------------------------------------
 * last points to previous temp
 * last will need to point to new temp
 * -----------------------------------------
 * Complexity --> O(1)
 */

    Linked_list *temp=alloc();
    Linked_list *last;

    temp->data = x;
    temp->next = NULL;

    if (first == NULL) {
        first = alloc();
        first = temp;
        last = temp;
    } else {
        last->next = temp;
        last = temp;
    }
}

void reverse_elements(Linked_list *p)
{
    int i, len=linked_list_length(p);
    int A[len];

    i=0;
    while (p) {
        A[i++] = p->data;
        p = p->next;
    }

    p = first, i--;
    while (p) {
        p->data = A[i--];
        p=p->next;
    }
}

void reverse_links(Linked_list *p)
{
    Linked_list *r=NULL, *q=NULL;

    while (p) {
        r = q;
        q = p;
        p = p->next;
        q->next = r; // reverse link
    }
    first = q;
}

void reverse(Linked_list *p)
{
    int i, len=linked_list_length(p);
    Linked_list *A[len];

    for (i=0; p; p=p->next, i++)
        A[i] = p;

    p = first, i--;
    while (i >= 0) {
        p->next = A[i];
        p = p->next, i--;
    }
    first = A[len-1];
    p->next = NULL;
}

void delete(Linked_list *p, int pos)
{
    int i, len=linked_list_length(p);
    Linked_list *q;

    if (pos > (len-1) || pos < 0)
        fprintf(stdout, "%s < %d >\n", "[-] INVALID INDEX ", pos);
    else {
        if (pos == 0) {
            first = p->next;
            free_node(p);
        } else {
            for (i = 0; p && i < pos; i++, q = p, p = p->next); // Traversing to the specified position
            q->next = p->next;
            free_node(p);
        }
    }
}

void delete_dup(Linked_list *p)
{
    Linked_list *q;

    q = p;
    p = p->next;
    while (p) {
        if (p->data == q->data) {
            q->next = p->next;
            free_node(p);
            p = q->next;
        } else {
            q = p;
            p = p->next;
        }
    }
}

void check_sorted(Linked_list *p)
{
    Linked_list *q=NULL;
    int flag=0;

    for (q=p, p=p->next; p; q=p, p=p->next) {
        if (q->data < p->data)
            flag = 1;
        else {
            flag = 0;
            break;
        }
    }
    (flag == 1) ? printf("Sorted\n") : printf("Not sorted\n");
}

void insert_sorted(Linked_list *p, int x)
{
    Linked_list *insert=alloc(), *previous=NULL;
    insert->data = x;
    insert->next = NULL;

    if (first == NULL) // If list in not present, create it
        first = insert;
    else {
        while (p && (p->data < x)) {
            previous = p;
            p = p->next;
        }
        if (p == first) {
            insert->next = first;
            first = insert;
        } else {
            insert->next = previous->next;
            previous->next = insert;
        }
    }
}

void insert(Linked_list *p, int idx, int x)
{
    Linked_list *pf=NULL, *q=NULL, *pinsert=alloc(); // pointer to first node
    int flag=1, count=0;
    int len=linked_list_length(p);

    if (idx < 0 || idx > len) {
        printf("[-] The index must be greater >= 0 and <  %d | Your idx < %d >\n", len,idx);
    } else {
        pinsert->data = x;
        while (p) {
            // inserting at first node
            if (idx == 0) {
                pf = p; // pf = 1 (in this case)
                first = pinsert; // first node == node to insert
                first->next = pf; // first points at next element
                break;
            }
            // inserting at  first_idx < node < last_idx
            if (idx > 0 && count == idx) {
                q->next = pinsert;
                pinsert->next = p;
                flag = 0;
                break;
            }
            q = p;
            p = p->next;
            count++;
        }
        if (p == NULL && flag) {
            pinsert->next = q->next; // q next is NULL, pinsert will also be NULL
            q->next = pinsert; // q->next points to the new node to insert
        }
    }
}

int linked_list_length(Linked_list *p)
{
    int cnt=0;
    while (p) {
        cnt++;
        p=p->next;
    }
    return cnt;
}

int sum(Linked_list *p)
{
    int total=0;
    while (p) {
        total += p->data;
        p = p->next;
    }
    return total;
}

int recursive_sum(Linked_list *p)
{
    if (!p)
        return 0;
    return recursive_sum(p->next) + p->data;
}

int find_max(Linked_list *p)
{
    int x=0;

    if (p==NULL)
        return INT_MIN;
    x = find_max(p->next); // At returning time, x will be assigned with p->next
    if (x > p->data)
        return x;
    else
        return p->data; // if  | x < p->data | ==> x will be equal to p->data
}

int find_min(Linked_list *p)
{
    int x;
    if (p==NULL)
        return INT_MAX;
    x = find_min(p->next);
    return (x < p->data) ? x : p->data;
}

void Display(Linked_list *p)
{
    if (p) {
        printf("%d -> ", p->data);
        Display(p->next);
    } else
        printf("NULL\n");
}

// will be used to improve linear search | the searched item will drawn toward the start of the linked list |
// Original -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> NULL
// After swapping -> 1 -> 2 -> 3 -> 5 -> 4 -> 6 -> 7 -> 8 -> 9 -> 10 -> NULL
void swap_nodes(Linked_list *p1, Linked_list *p2, Linked_list *p3)
{
    p3->next = p1; // 3 -> 5
    p2->next = p1->next; // 4 -> 6
    p1->next = p2; // 5 -> 4
}

int search(Linked_list *p, int key)
{
    Linked_list *previous=NULL, *pp=NULL;
    int count=0;

    while (p) {
        if (p->data == key) {
            if (count == 1) {
                /* Improving linear search */
                previous->next = p->next;
                p->next = first;
                first = p;
            }
            else if (count > 1)
                swap_nodes(p, previous, pp);
            return 1;
        }
        else {
            pp = previous;
            previous = p;
            p = p->next;
            count++;
        }
    }
    return 0;
}

int recur_search(Linked_list *p, int key)
{
    if (!p)
        return 0;
    if (p->data == key)
        return p->data;
    recur_search(p->next, key);
}
