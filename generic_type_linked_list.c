#include <stdio.h>
#include "stdlib.h"

typedef struct list_ {
    void *data;
    char type;
    int cnt;
    struct list_ *next;
} List;

List *init_list(void);
void insert_list(List *list, void *data, char type);
void display(List *list);
void insertChar(List *list, char *data);
void insertInt(List *list, int *data);

void insertChar(List *list, char *data)
{
    insert_list(list, (void *) data, 'c');
}

void insertInt(List *list, int *data)
{
    insert_list(list, (void *) data, 'i');
}


List *init_list(void)
{
    return malloc(sizeof(List));
}

void insert_list(List *list, void *data, char type)
{
    /*
        The types are:
        c - for char.
        i - for int.
     */

    if (list->cnt == 0) {
        list->next = NULL;
        list->type = type;
        list->data = data;
        list->cnt++;
    } else {
        List *ptr;

        if ((ptr = init_list()) != NULL) {
            ptr->type = type;
            ptr->data = data;
            list->cnt++;
            while (list->next != NULL) {
                list = list->next;
            }
            list->next = ptr;
            ptr->next = NULL;
        }
    }
}

void display(List *list)
{
    while (list != NULL) {
        switch (list->type) {
            case 'c': {
                char data = *(char *) list->data;
                printf("%c", data);
                break;
            } case 'i': {
                int data = *(int *) list->data;
                printf("%d", data);
                break;
            }
        }
        list = list->next;
    }
    puts("");
}

void freeList(List *list)
{
    List *prev = NULL;

    while (list != NULL) {
        prev = list;
        list = list->next;
        free(prev);
    }
}


int main()
{
    List list;
    list.cnt = 0;

    char name[] = "CASIO";
    int identifier[] = {1,5};
    int i, j;
    size_t id_size = sizeof(identifier)/sizeof(int);

    for (i = 0; name[i] != '\0'; i++)
        insertChar(&list, &name[i]);

    for (j = 0; j < id_size; j++)
        insertInt(&list, &identifier[j]);

    display(&list);
    freeList(&list);

    return 0;
}
