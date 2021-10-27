#include <stdio.h>
#include "tree.h"


int main()
{
    Tree *root = init_node(4);

    root->lchild = init_node(5);

    root->rchild = init_node(2);
    root->rchild->lchild = init_node(3);
    root->rchild->rchild = init_node(1);
    root->rchild->lchild->lchild = init_node(6);
    root->rchild->lchild->rchild = init_node(7);



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
