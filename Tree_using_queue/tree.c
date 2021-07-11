#include "stdio.h"
#include "queue.h"
#include "color.h"
#include "Stack.h"


#if defined(_WIN32)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

Node *root=NULL;

void create(void);
void DisplayInOrder(Node *);
void FreeTree(Node *);
void DisplayPreOrder(Node *);

void create(void)
{
    Node *p, *t;
    int x, space=10, i=0, cnt_nodes=2;

#ifdef WIN32
    printf("ENTER -1 TO EXIT\n");
    printf("Enter root value\n");
#else
    red("ENTER -1 TO EXIT", True);
    blue("Enter root value", True);
#endif
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
#ifndef WIN32
            green("[!] Tree is balanced", True);
#else
            printf("[!] Tree is balanced\n");
#endif
            cnt_nodes *= 2;
            i = 0;
            space += 5;
        }
        if ((p->lchild && !p->rchild) || (p->rchild && !p->lchild))
            space += 5;
        Q->cnt_nodes++;
    }
    system(CLEAR);
    puts("");
}

void DisplayPreOrder(Node *r)
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

void IterativeInOrder(Node *r)
{
    while (r) {
        printf("%d ", r->data);
        if (r->lchild && r->rchild) {
            push(r);
            r = r->lchild;
        } else if (!IsEmpty(s->top)) {
            r = pop();
            r = r->rchild;
        } else
            break;
    }
}

int main(void) {

    char format[20];
    int Mode;

    create();
    system(CLEAR);

    puts("Enter traversal mode:\n1)Iterative Traversal\n2)Recursive Traversal");
    scanf("%d", &Mode);

    switch (Mode) {
        case 1:
            puts("Iterative Pre Order Traversal:");
            IterativeInOrder(root);
            break;
        case 2:
            sprintf(format, "[+] %d Nodes", Q->cnt_nodes - 1);
            green("[+] Printing Tree ...", True);
            green(format, True);
            DisplayInOrder(root);
            FreeTree(root);
            red("[*] Freeing Tree ...", True);
            break;
        default:
            puts("Invalid traversal mode !");
    }

    return 0;
}
