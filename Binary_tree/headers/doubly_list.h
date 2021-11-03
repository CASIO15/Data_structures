#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "tree.h"

typedef struct double_list {
    t_node node;
    struct double_list *flink;
    struct double_list *blink;
} DList;

DList *init_list();
void insert_list(DList **list, t_node *node);
void free_list(DList **list);
void print_list(DList *list);
void *ConvertTreeToDLL(Tree *root, DList **list);
void print_list_reverse(DList *list);

#endif
