#include "stdio.h"
#include "queue.h"
#include "colors.h"

#if defined(_WIN64)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

Node *root=NULL;

void create(void);
void DisplayInOrder(Node *);
void FreeTree(Node *);

void create(void)
{
    Node *p, *t;
    int x, space=10, i=0, cnt_nodes=2;

    red("### TO EXIT ENTER -1 ###", True);
    blue("Enter root value ", True);
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
        if (i == cnt_nodes && (p->rchild && p->lchild)) {
            green("[!] Tree is balanced", True);
            cnt_nodes *= 2;
            i = 0;
            Q->level++;
            space += 5;
        }
        if ((p->lchild && !p->rchild) || (p->rchild && !p->lchild))
            space += 5;
        Q->cnt_nodes++;
    }
    system(CLEAR);
    puts("");
}

void DisplayInOrder(Node *r)
{
    int i;
    if (r) {
        DisplayInOrder(r->lchild);
        for (i=0; i < r->space; i++)
            printf(" ");
        if (r->space == 0) {
            red("{ROOT} ", False);
            printf("[%d]\n", r->data);
        } else {
            green(" ---[", False);
            printf("%d\n", r->data);
        }
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

    char format[20];

    create();
    sprintf(format, "[+] %d Nodes", Q->cnt_nodes-1);

    green("[+] Printing Tree ...", True);
    green(format, True);
    DisplayInOrder(root);
    FreeTree(root);
    red("[*] Freeing Tree ...", True);
    return 0;
}
