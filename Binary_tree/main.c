#include <stdio.h>
#include "tree.h"

void PrintMenu()
{
    printf("Tree Methods:\n"
           "-------------\n"
           "1.Check if the tree is balanced.\n"
           "2.Check if the sum of the children is equal to parent.\n"
           "3.Print left-view (recursive).\n"
           "4.Print left-view (iterative).\n"
           "5.Print level-order traversal (recursive).\n"
           "6.Print level-order traversal (iterative).\n"
           "7.Print the size of the tree.\n"
           "8.Print the max key.\n"
           "9.Print the min key.\n"
           "10.To exit.\n");
}

int main()
{
    Tree *root = init_node(10);
    int user_choice;
    int exit = 0;

    root->lchild = init_node(8);
    root->lchild->lchild = init_node(4);
    root->lchild->rchild = init_node(4);
    root->lchild->rchild->lchild = init_node(4);

    root->rchild = init_node(2);

    PrintMenu();

    for (;exit != 1;) {
        printf("\nENTER YOUR CHOICE: ");
        if (scanf("%d", &user_choice) != 1) {
            fprintf(stderr, "Error ! Invalid choice\n");
            return EXIT_FAILURE;
        }
        switch (user_choice) {
            case 1:
                if (CheckHeightBalance(root))
                    puts("Tree is balanced.");
                else
                    puts("Tree is not balanced.");
                break;
            case 2:
                if (isCSum(root))
                    puts("True.");
                else
                    puts("False.");
                break;
            case 3:
                LeftView(root, 0);
                break;
            case 4:
                LeftViewIterative(root);
                break;
            case 5:
                for (int i = 0; i < FindHeight(root); i++)
                    PrintKLevel(root, i);
                break;
            case 6:
                PrintKLevelIterative(root);
                break;
            case 7:
                printf("%d\n", SizeOfTree(root));
                break;
            case 8:
                printf("MAX key is: %d\n", FindMax(root));
                break;
            case 9:
                printf("MIN key is: %d\n", FindMin(root));
                break;
            case 10:
                exit = 1;
                break;
            default:
                fprintf(stderr, "Invalid choice !");
#ifdef WIN32
#define CLEAR "cls"
#elif
#define CLEAR "clear"
#endif
                system(CLEAR);
                PrintMenu();
#undef CLEAR
                break;
        }
    }

    return 0;
}
