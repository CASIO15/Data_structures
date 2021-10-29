#include <stdio.h>
#include "tree.h"

int main()
{
    Tree *root = init_node(10);

    root->lchild = init_node(8);
    root->lchild->lchild = init_node(4);
    root->lchild->rchild = init_node(4);
    root->lchild->rchild->lchild = init_node(4);

    root->rchild = init_node(2);

    if (CheckHeightBalance(root))
        printf("Tree is balanced !\n");
    else
        printf("The tree is not balanced !\n");

    if (isCSum(root) == 1)
        printf("True\n");
    else
        printf("False\n");


    printf("Left view: ");
    LeftView(root, 0);
    puts("");

    printf("Left view iterative: ");
    LeftViewIterative(root);


    printf("\nLevel order traversal: ");
    PrintKLevelIterative(root);
    printf("The size of the tree is: %d\n", SizeOfTree(root));
    printf("The max element is: %d\n", FindMax(root));
    printf("The min element is: %d\n", FindMin(root));

    return 0;
}
