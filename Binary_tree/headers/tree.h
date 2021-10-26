#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
} t_node;

typedef t_node Tree;

#define IS_LEAF(root) ((root)->lchild == NULL && (root)->rchild == NULL) ? 1 : 0
#define IS_R_LEAF(root) ((root)->rchild == NULL) ? 1 : 0
#define IS_L_LEAF(root) ((root)->lchild == NULL) ? 1 : 0

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
void insert(Tree *root, int key);
t_node *FindDeepestNode(Tree *root);
t_node *delete(Tree *root, t_node *head_ref, t_node *deepest, int key);

#endif
