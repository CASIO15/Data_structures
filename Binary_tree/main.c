#include <stdio.h>
#include <string.h>
#include "tree.h"

#ifdef WIN32
    #define CLEAR "cls"
#elif
    #define CLEAR "clear"
#endif

void PrintMenu();

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
           "10.Exit.\n");
}

int main(int argc, char **argv)
{
    Tree *root = NULL;
    int root_data = 0;
    int user_choice;
    int exit_loop = 0;

    if (argc == 1) {
        printf("Create tree:\n"
               "************\n\n"
               "Enter root data: ");

        if (scanf("%d", &root_data) == 1) {
            root = init_node(root_data);
            root = CreateTreeFromUserInput(root);
            system(CLEAR);
        } else {
            fprintf(stderr, "Error ! Invalid input !\n");
            exit_loop = 1;
        }
    } else {
        // Creating tree based on the argv arguments passed.
        int i;
        int *arr = NULL;
        int alloc_size = argc - 1;

        if ((arr = malloc(sizeof(int) * alloc_size)) == NULL) {
            fprintf(stderr, "Not enough memory !\n");
            exit(EXIT_FAILURE);
        }
        for (i = 1; argv[i] != NULL; i++)
            arr[i-1] = atoi(argv[i]);

        root = CreateTree(root, arr, 0, i-1);
    }

    PrintMenu();

    for (;exit_loop != 1;) {
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
                exit_loop = 1;
                break;
            default:
                fprintf(stderr, "Invalid choice !\n");
                system(CLEAR);
                PrintMenu();
                break;
        }
    }
#undef CLEAR
    return 0;
}
