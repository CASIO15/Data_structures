#include "tree.h"
#include "queue.h"

t_node* init_node(int data)
{
    t_node* new = malloc(sizeof(t_node));
    new->data = data;
    new->left = new->right = NULL;

    return new;
}

void InOrder(Tree* root)
{
    if (root) {
        printf("%d ", root->data);
        InOrder(root->left);
        InOrder(root->right);
    }
}

int FindHeight(Tree* root)
{
    if (root == NULL)
        return 0;
    return max(FindHeight(root->left) + 1, FindHeight(root->right) + 1);
}

void PrintKLevel(Tree* root, int k)
{
    if (root == NULL)
        return;

    if (k == 0)
        printf("%d ", root->data);
    else {
        PrintKLevel(root->left, k - 1);
        PrintKLevel(root->right, k - 1);
    }
}

t_node* CreateTree(Tree* root, int* arr, int idx, int size)
{
    if (idx < size) {
        root = init_node(arr[idx]);

        root->left = CreateTree(root->left, arr, idx * 2 + 1, size);
        root->right = CreateTree(root->right, arr, idx * 2 + 2, size);
    }
    return root;
}

int SizeOfTree(Tree* root)
{
    if (root == NULL)
        return 0;
    return SizeOfTree(root->left) + 1 + SizeOfTree(root->right);
}

int FindMax(Tree* root)
{
    if (root == NULL)
        return INT_MIN;

    int max_left, max_right, current = root->data;

    max_left = FindMax(root->left);
    max_right = FindMax(root->right);

    if (max_left > current)
        current = max_left;
    if (max_right > current)
        current = max_right;

    return current;
}

void PrintKLevelIterative(Tree* root)
{
    Queue* queue = NULL;

    EnQueue(&queue, root);
    EnQueue(&queue, NULL);
    t_node* temp = NULL;

    if (queue != NULL) {
        while (queue->front != NULL) {
            temp = DeQueue(&queue);

            if (temp != NULL) {
                printf("%d ", temp->data);
                EnQueue(&queue, temp->left);
                EnQueue(&queue, temp->right);
            }
        }
        puts("");
        free(queue);
        queue = NULL;
    }
}

int FindMin(Tree* root)
{
    if (root == NULL)
        return INT_MAX;

    int min_left, min_right, current = root->data;

    min_left = FindMin(root->left);
    min_right = FindMin(root->right);

    if (min_left < current)
        current = min_left;
    if (min_right < current)
        current = min_right;

    return current;
}

void insert(Tree* root, int key)
{
    if (root != NULL) {
        t_node* new = init_node(key);

        if (root->right == NULL && root->left == NULL)
            return;
        if (root->right == NULL)
            root->right = new;
        else if (root->left == NULL)
            root->left = new;

        insert(root->left, key);
        insert(root->right, key);
    }
}

t_node* FindDeepestNode(Tree* root)
{
    if (root) {
        int is_right_leaf = IS_R_LEAF(root), is_left_leaf = IS_L_LEAF(root);

        if (!is_left_leaf && is_right_leaf)
            return root->left;
        else if (is_left_leaf && !is_right_leaf)
            return root->right;
        else if (IS_LEAF(root->right) && IS_LEAF(root->left))
            return root->right;
        FindDeepestNode(root->right);
    }
    else
        return NULL;
}

t_node* delete(Tree* root, t_node* head_ref, t_node* deepest, int key)
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
        root->left = delete(root->left, head_ref, deepest, key);
        root->right = delete(root->right, head_ref, deepest, key);
    }
}

void LeftView(Tree* root, int level)
{
    if (root == NULL)
        return;

    // If the level is zero, it means that we are at root level, print it
    if (level == 0)
        printf("%d ", root->data);

    // If the left node of hte node is a leaf, and the node itself is not a leaf, print its left child
    if (!IS_L_LEAF(root) && !IS_LEAF(root))
        printf("%d ", root->left->data);

    LeftView(root->left, level + 1);
    LeftView(root->right, level + 1);
}

void LeftViewIterative(Tree* root)
{
    Queue* q = NULL;
    int level = 0;

    EnQueue(&q, root);
    EnQueue(&q, NULL);

    while (q->front != NULL) {
        t_node* node = DeQueue(&q);

        if (node != NULL) {
            if (level == 0)
                printf("%d ", node->data);
            if (!IS_L_LEAF(node) && !IS_LEAF(node))
                printf("%d ", node->left->data);

            EnQueue(&q, node->left);
            EnQueue(&q, node->right);
        }
        level++;
    }
    free(q);
    q = NULL;
}

/*
        1000  <-- ROOT
       /    \
    590      410
   /   \    /   \
500    90  NULL  410

*/

int isCSum(Tree* node)
{
    if (node == NULL)
        return 1;

    if (node->left && node->right && (node->left->data + node->right->data != node->data)) {
        return 0;
    } else if (node->left && !node->right && (node->left->data != node->data)) {
        return 0;
    } else if (node->right && !node->left && (node->right->data != node->data)) {
        return 0;
    } else {
        return isCSum(node->left) && isCSum(node->right);
    }
}

int CheckHeightBalance(Tree *node)
{
    int left_height, right_height;
    int diff;

    if (node == NULL)
        return 1;

    left_height = FindHeight(node->left);
    right_height = FindHeight(node->right);

    diff = abs(left_height - right_height);

    if (diff >= 2)
        return 0;

    return CheckHeightBalance(node->left) && CheckHeightBalance(node->right);
}

t_node *CreateTreeFromUserInput(Tree *node)
{
    if (node != NULL) {
        int data = 0;

        printf("Enter %d left child: ", node->data);
        if (scanf("%d", &data) != 1)
            exit(EXIT_FAILURE);

        if (data != -1) {
            node->left = init_node(data);
        }

        printf("Enter %d right child: ", node->data);
        if (scanf("%d", &data) != 1)
            exit(EXIT_FAILURE);

        if (data != -1) {
            node->right = init_node(data);
        }

        node->left = CreateTreeFromUserInput(node->left);
        node->right = CreateTreeFromUserInput(node->right);

        return node;
    }

    return NULL;
}

int GetLevelCount(Tree *root, int level, int depth)
{
    if (root == NULL)
        return 0;

    root->space_cnt = 0;
    if (level == depth) {
        return 1;
    }
    return GetLevelCount(root->left, level, depth-1) + GetLevelCount(root->right, level, depth-1);
}

int FindWidth(Tree *root)
{
    int depth = FindHeight(root);
    int max = 0, current;

    for (int i = 0; i < depth; i++) {
        current = GetLevelCount(root, i, depth);
        if (current > max)
            max = current;
    }
    return max;
}

void FreeTree(Tree *root)
{
    if (root) {
        FreeTree(root->left);
        FreeTree(root->right);
        free(root);
    }
}

void SetSpaceByLevel(Tree *root, int level, int depth)
{
    if (root == NULL)
        return;
    if (level == 0) {
        root->space_cnt = 0;
    }
    if (level < depth) {
        // Setting the space for the level
        root->space_cnt = 7 * level;
    }
    SetSpaceByLevel(root->left, level + 1, depth);
    SetSpaceByLevel(root->right, level + 1, depth);
}

void LoopEachLevel(Tree *root)
{
    int height = FindHeight(root);
    SetSpaceByLevel(root, 0, height);
}

void PrettyPrint(Tree *root)
{
    int i;
    if (root) {
        PrettyPrint(root->left);
        for (i=0; i < root->space_cnt; i++)
            printf(" ");
        if (root->space_cnt == 0) {
            printf("{ROOT} ");
            printf("[%d]\n", root->data);
        } else {
            printf(" ---[");
            printf("%d\n", root->data);
        }
        PrettyPrint(root->right);
    }
}
