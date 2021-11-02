#ifndef TREE_H
#define TREE_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int data;
    int space_cnt;
    struct node* left;
    struct node* right;
} t_node;

typedef t_node Tree;

#define IS_LEAF(root) ((root)->left == NULL && (root)->right == NULL) ? 1 : 0
#define IS_R_LEAF(root) ((root)->right == NULL) ? 1 : 0
#define IS_L_LEAF(root) ((root)->left == NULL) ? 1 : 0

#define max(a,b) ((a) > (b)) ? (a) : (b)
#define abs(a)   ((a) < 0) ? (-(a)) : (a)

t_node* init_node(int data);
void InOrder(Tree* root);
int FindHeight(Tree* root);
void PrintKLevel(Tree* root, int k);
t_node* CreateTree(Tree* root, int* arr, int idx, int size);
int SizeOfTree(Tree* root);
int FindMax(Tree* root);
int FindMin(Tree* root);
void PrintKLevelIterative(Tree* root);
void insert(Tree* root, int key);
t_node* FindDeepestNode(Tree* root);
t_node* delete(Tree* root, t_node* head, int key);
void LeftView(Tree* root, int level);
void LeftViewIterative(Tree* root);
int isCSum(Tree* root);
int CheckHeightBalance(Tree* node);
t_node* CreateTreeFromUserInput(Tree* node);
int FindWidth(Tree* root);
int GetLevelCount(Tree* root, int level, int depth);
void FreeTree(Tree* root);

void SetSpaceByLevel(Tree* root, int level, int depth);
void LoopEachLevel(Tree* root);
void PrettyPrint(Tree* root);

#endif
