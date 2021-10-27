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
        while (queue->front != NULL) {
            temp = DeQueue(&queue);

            if (temp != NULL) {
                printf("%d ", temp->data);
                EnQueue(&queue, temp->lchild);
                EnQueue(&queue, temp->rchild);
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

void insert(Tree *root, int key)
{
    if (root != NULL) {
        t_node *new = init_node(key);

        if (root->rchild == NULL && root->lchild == NULL)
            return;
        if (root->rchild == NULL)
            root->rchild = new;
        else if (root->lchild == NULL)
            root->lchild = new;

        insert(root->lchild, key);
        insert(root->rchild, key);
    }
}

t_node *FindDeepestNode(Tree *root)
{
    if (root) {
        int is_right_leaf = IS_R_LEAF(root), is_left_leaf = IS_L_LEAF(root);

        if (!is_left_leaf && is_right_leaf)
            return root->lchild;
        else if (is_left_leaf && !is_right_leaf)
            return root->rchild;
        else if (IS_LEAF(root->rchild) && IS_LEAF(root->lchild))
            return root->rchild;
        FindDeepestNode(root->rchild);
    } else
        return NULL;
}

t_node *delete(Tree *root, t_node *head_ref, t_node *deepest, int key)
{
    if (root) {
        int is_leaf = IS_LEAF(root);
        // Delete leaf node
        if (is_leaf && root->data == key) {
            free(root);
            return NULL;
        }
        // Deleting root node or any other node that is not a leaf node
        // Find the rightmost, deepest node, copy its data, delete it and update the root node to the deepest data
        if (root->data == key && !is_leaf) {
            int deepest_data = deepest->data;
            delete(head_ref, deepest, head_ref, deepest_data);
            root->data = deepest_data;
        }
        root->lchild = delete(root->lchild, head_ref, deepest, key);
        root->rchild = delete(root->rchild, head_ref, deepest, key);
    }
}

void LeftView(Tree *root, int level)
{
    if (root == NULL)
        return;

    // If the level is zero, it means that we are at root level, print it
    if (level == 0)
        printf("%d ", root->data);

    // If the left node of hte node is a leaf, and the node itself is not a leaf, print its left child
    if (!IS_L_LEAF(root) && !IS_LEAF(root))
        printf("%d ", root->lchild->data);

    LeftView(root->lchild, level+1);
    LeftView(root->rchild, level+1);
}

void LeftViewIterative(Tree *root)
{
    Queue *q = NULL;
    int level = 0;

    EnQueue(&q, root);
    EnQueue(&q, NULL);

    while (q->front != NULL) {
        t_node *node = DeQueue(&q);

        if (node != NULL) {
            if (level == 0)
                printf("%d ", node->data);
            if (!IS_L_LEAF(node) || !IS_LEAF(node))
                printf("%d ", node->lchild->data);

            EnQueue(&q, node->lchild);
            EnQueue(&q, node->rchild);
        }
        level++;
    }

    free(q);
    q = NULL;
}
