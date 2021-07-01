#include "stdio.h"
#include "queue.h"

Node *root=NULL;

void create(void);
void DisplayInOrder(Node *);

void create(void)
{
    Node *p, *t;
    int x, cnt=0;

    puts("### TO EXIT ENTER -1 ###");
    puts("Enter root value ");
    scanf("%d", &x);
    root = Init_node();
    root->data = x;
    root->prec = 0;
    enqueue(root);

    while (!IsEmptyQ(Q)) {
        p = dequeue();
        printf("Enter left child of %d ", p->data);
        scanf("%d", &x);
        if (x != -1) {
            t = Init_node();
            t->data = x;
            t->prec = cnt+1;
            p->lchild = t;
            enqueue(t);
        }
        printf("Enter right child of %d ", p->data);
        scanf("%d.4", &x);
        if (x != -1) {
            t = Init_node();
            t->data = x;
            t->prec = cnt+1;
            p->rchild = t;
            enqueue(t);
        }
        cnt++;
    }
}

void DisplayInOrder(Node *r)
{
    if (r) {
        printf("%d\n", r->data);
        DisplayInOrder(r->lchild);
        DisplayInOrder(r->rchild);
    }
}


int main(void) {

    create();
    DisplayInOrder(root);
    return 0;
}
