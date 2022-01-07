#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TYPE_INT 0
#define TYPE_STR 1
#define TYPE_FLOAT 2
#define TYPE_DOUBLE 3
#define TYPE_CHAR 4

#define INIT_PHY_SIZE 4
#define INIT_LOG_SIZE 0

#define allocList(cast, type, size) (cast *) malloc(sizeof(type) * (size));
#define insertList(data, type) insert(&list, data, type);
#define GROW_ARR(size) (size) * 2

typedef struct list {
    void** list;
    int phySize;
    int logSize;
    int* typeMapping;
} List;

void print(List* list);
List* initList();
void* reallocate(void* data, int newSize);
void insert(List** list, void* type, int keyType);
void deleteList(List** list);

List* initList()
{
    List *list = allocList(List, List, 1);
    list->phySize = INIT_PHY_SIZE;
    list->logSize = INIT_LOG_SIZE;

    list->list = allocList(void, void *, list->phySize);
    list->typeMapping = allocList(int, int, list->phySize);

    return list;
}

void* reallocate(void* data, int newSize)
{
    void* new = NULL;

    if ((new = realloc(data, sizeof(data) * newSize)) == NULL) {
        printf("Error !\n");
        exit(1);
    }

    return new;
}

void insert(List** list, void* type, int keyType)
{
    int size = (*list)->logSize, phySize = (*list)->phySize;

    if (size + 1 >= phySize) {
        (*list)->list = reallocate((void **) (*list)->list,GROW_ARR(phySize));
        (*list)->typeMapping = reallocate((void *) (*list)->typeMapping,GROW_ARR(phySize));
        (*list)->phySize = GROW_ARR(phySize);
    }

    (*list)->list[size] = (void *) type;
    (*list)->typeMapping[size] = keyType;
    (*list)->logSize++;
}

void print(List* list)
{
    printf("[");
    for (int i = 0; i < list->logSize; i++) {
        switch (list->typeMapping[i]) {
            case TYPE_STR:
                printf("\"%s\", ", (char *) list->list[i]);
                break;
            case TYPE_INT:
                printf("%d, ", *(int *) list->list[i]);
                break;
            case TYPE_DOUBLE:
                printf("%.3lf, ", *(double *) list->list[i]);
                break;
            case TYPE_FLOAT:
                printf("%.3f, ", *(float *) list->list[i]);
                break;
            case TYPE_CHAR:
                printf("\'%c\', ", *(char *) list->list[i]);
                break;
            default:
                printf("\b\b]\n");
                printf("Error ! Invalid Type !");
                deleteList(&list);
                exit(1);
        }
    }
    printf("\b\b]\n");
}

void deleteList(List** list)
{
    for (int i = 0; i < (*list)->logSize; i++) {
        free((*list)->list);
        free((*list)->typeMapping);

        (*list)->list = NULL;
        (*list)->typeMapping = NULL;
    }
    free(*list);
    (*list) = NULL;
}


int main()
{
    List *list = initList();

    char* str = "Hello world !";
    int var1 = 1, var2 = 2;
    float f1 = 1.3f;
    double d1 = 0.5133;
    char c1 = '$';

    insertList(str, TYPE_STR);
    insertList(&var1, TYPE_INT);
    insertList(&var2, TYPE_INT);
    insertList(&f1, TYPE_FLOAT);
    insertList(&d1, TYPE_DOUBLE);
    insertList(&c1, TYPE_CHAR);

    print(list);
    deleteList(&list);

    return 0;
}
