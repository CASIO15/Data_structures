#include "Doubly_linked_list.h"

static DList *temp;

DList *init_list()
{
    return malloc(sizeof(DList));
}

void insert_list(DList **list, t_node *node)
{
    if (*list == NULL) {
        *list = init_list();
        temp = init_list();
        (*list)->blink = NULL;
        (*list)->flink = NULL;
        (*list)->node = node;
        temp = *list;
        return;
    }

    DList *new = init_list();
    new->node = node;
    new->flink = NULL;
    temp->flink = new;
    new->blink = temp;
    temp = new;
}

void free_list(DList **list)
{
    DList *current;

    while ((*list) != NULL) {
        current = *list;
        *list = (*list)->flink;
        free(current);
        current = NULL;
    }
    free(list);
    list = NULL;
}
