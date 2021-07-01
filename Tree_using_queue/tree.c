#include "stdio.h"
#include "queue.h"
#include "stdlib.h"

Node *root=NULL;

void create(void);
void DisplayInOrder(Node *);
void FreeTree(Node *);

void create(void)
{
    Node *p, *t;
    int x, space=10, i=0, cnt_nodes=2;

    puts("### TO EXIT ENTER -1 ###");
    printf("Enter root value \n");
    scanf("%d", &x);
    root = Init_node();
    root->data = x;
    root->space = 0;
    enqueue(root);
    Q->cnt_nodes = 1;

    while (!IsEmptyQ(Q)) {
        p = dequeue();
        printf("Enter left child of %d \n", p->data);
        scanf("%d", &x);
        if (x != -1) {
            t = Init_node();
            t->data = x;
            t->space = space;
            p->lchild = t;
            enqueue(t);
            i++;
        }
        printf("Enter right child of %d \n", p->data);
        scanf("%d", &x);
        if (x != -1) {
            t = Init_node();
            t->data = x;
            t->space = space;
            p->rchild = t;
            enqueue(t);
            i++;
        }
        if (i == cnt_nodes) {
            printf("[!] Tree is balanced\n");
            cnt_nodes *= 2;
            i = 0;
            space += 5;
        }
        Q->cnt_nodes++;
    }
    system("cls");
    printf("\n\n");
}

void DisplayInOrder(Node *r)
{
    int i;
    if (r) {
        DisplayInOrder(r->lchild);
        for (i=0; i < r->space; i++)
            printf(" ");
        if (r->space == 0)
            printf("{ROOT} [%d]\n", r->data);
        else
            printf(" ----[%d\n", r->data);
        DisplayInOrder(r->rchild);
    }
}

void FreeTree(Node *r)
{
    if (r) {
        FreeTree(r->lchild);
        FreeTree(r->rchild);
        free((Node *) r);
    }
}


int main(void) {

    create();
    puts("[+] Printing Tree ...");
    printf("[+] %d Nodes\n", Q->cnt_nodes-1);
    DisplayInOrder(root);
    FreeTree(root);
    puts("[*] Freeing Tree ...");
    return 0;
}
