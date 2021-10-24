#include "tree.h"
#include "queue.h"

t_node *init_node(int data)
{
    t_node *new = malloc(sizeof(t_node));
    new->data = data;
    new->lchild = new->rchild = NULL;

    return new;
}

void InOrder(Tree *root)
{
    if (root) {
        InOrder(root->lchild);
        printf("%d ", root->data);
        InOrder(root->rchild);
    }
}

int max(int n1, int n2)
{
    if (n1 > n2)
        return n1;
    return n2;
}

int FindHeight(Tree *root)
{
    if (root == NULL)
        return 0;
    return max(FindHeight(root->lchild)+1, FindHeight(root->rchild)+1);
}

void PrintKLevel(Tree *root, int k)
{
    if (root == NULL)
        return;

    if (k == 0)
        printf("%d ", root->data);
    else {
        PrintKLevel(root->lchild, k-1);
        PrintKLevel(root->rchild, k-1);
    }
}

t_node *CreateTree(Tree *root, int *arr, int idx, int size)
{
    if (idx < size) {
        root = init_node(arr[idx]);

        root->lchild = CreateTree(root->lchild, arr, idx * 2 + 1, size);
        root->rchild = CreateTree(root->rchild, arr, idx * 2 + 2, size);
    }

    return root;
}

int SizeOfTree(Tree *root)
{
    if (root == NULL)
        return 0;
    return SizeOfTree(root->lchild) + 1 + SizeOfTree(root->rchild);
}

int FindMax(Tree *root)
{
    if (root == NULL)
        return INT_MIN;

    int max_left, max_right, current = root->data;

    max_left = FindMax(root->lchild);
    max_right = FindMax(root->rchild);

    if (max_left > current)
        current = max_left;
    if (max_right > current)
        current = max_right;

    return current;
}

void PrintKLevelIterative(Tree *root)
{
    Queue *queue = NULL;

    EnQueue(&queue, root);
    EnQueue(&queue, NULL);
    t_node *temp = NULL;

    if (queue != NULL) {
        while (queue->front && !IsEmpty(queue)) {
            temp = DeQueue(&queue);

            if (temp != NULL) {
                if (temp->lchild)
                    EnQueue(&queue, temp->lchild);

                if (temp->rchild != NULL)
                    EnQueue(&queue, temp->rchild);
                printf("%d ", temp->data);
            }
        }
        puts("");
        free(queue);
        queue = NULL;
    }
}

int FindMin(Tree *root)
{
    if (root == NULL)
        return INT_MAX;

    int min_left, min_right, current = root->data;

    min_left = FindMin(root->lchild);
    min_right = FindMin(root->rchild);

    if (min_left < current)
        current = min_left;
    if (min_right < current)
        current = min_right;

    return current;
}
