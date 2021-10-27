#include <stdio.h>
#include "tree.h"

int main()
{

    Tree *root = init_node(1000);

    root->lchild = init_node(590);
    root->rchild = init_node(410);

    root->lchild->lchild = init_node(500);
    root->lchild->rchild = init_node(90);

    root->rchild->rchild = init_node(410);


    if (isCSum(root) == root->data)
        printf("True\n");
    else
        printf("False\n");


    printf("Left view: ");
    LeftView(&root, 0);
    puts("");

    printf("Left view iterative: ");
    LeftViewIterative(&root);


    printf("\nLevel order traversal: ");
    PrintKLevelIterative(&root);
    printf("The size of the tree is: %d\n", SizeOfTree(&root));
    printf("The max element is: %d\n", FindMax(&root));
    printf("The min element is: %d\n", FindMin(&root));

    return 0;
}
