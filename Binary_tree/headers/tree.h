#ifndef GEEKSFORGEEKS_TREE_H
#define GEEKSFORGEEKS_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    struct node *lchild;
    int data;
    struct node *rchild;
} t_node;

typedef t_node Tree;


t_node *init_node(int data);
void InOrder(Tree *root);
int FindHeight(Tree *root);
int max(int n1, int n2);
void PrintKLevel(Tree *root, int k);
t_node *CreateTree(Tree *root, int *arr, int idx, int size);
int SizeOfTree(Tree *root);
int FindMax(Tree *root);
int FindMin(Tree *root);
void PrintKLevelIterative(Tree *root);

#endif
