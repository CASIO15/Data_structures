#include <stdio.h>
#include "tree.h"


int main()
{
    Tree *root = init_node(13);

    root->lchild = init_node(12);
    root->lchild->lchild = init_node(4);
    root->lchild->rchild = init_node(19);

    root->rchild = init_node(10);
    root->rchild->lchild = init_node(16);

    insert(root, 100);
    printf("Inorder traversal after insertion: ");
    InOrder(root);
    puts("");

    delete(root, root, FindDeepestNode(root), 12);
    delete(root, root, FindDeepestNode(root), 13);

    printf("Inorder traversal after deletion:  ");
    InOrder(root);
    puts("");

    printf("Level order traversal: ");
    PrintKLevelIterative(root);
    
    printf("The size of the tree is: %d\n", SizeOfTree(root));
    printf("The max element is: %d\n", FindMax(root));
    printf("The min element is: %d\n", FindMin(root));


    return 0;
}
