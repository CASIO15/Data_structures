#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "queue.h"


int main()
{
    Tree *root = NULL;

    int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,1500,14,15,16,17,18,19,-20,-21,20,21,22,23,24,25,26,27,28,29,30,100 };
    int size = sizeof(arr)/sizeof(int);

    root = CreateTree(root, arr, 0, size);

    // O(n^2) solution
    for (int i = 0, height = FindHeight(root); i < height; i++)
        PrintKLevel(root, i);

    puts("");

    PrintKLevelIterative(root);
    printf("The size of the tree is: %d\n", SizeOfTree(root));
    printf("The max element is: %d\n", FindMax(root));
    printf("The min element is: %d\n", FindMin(root));

    return 0;
}
