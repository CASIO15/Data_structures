/* Parentheses matching, it won't check for syntax error, only if the parentheses are balanced */

#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
    char *data;
    struct Node *next;
} Stack;

enum BOOL {FALSE, TRUE};

Stack *top=NULL;

Stack *alloc(void );
void push(char n);
int empty(void);
int full(void);
char pop(void);
int validate(void);

Stack *alloc(void)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->data = (char *)malloc(sizeof(char)*100);
    return p;
}

void push(char n)
{
    Stack *q=alloc();

    if (!full()) {
        if (top == NULL) {
            top = q;
            *(q->data) = n;
            *(++q->data) = '\0';
            q->next = NULL;
        } else {
            q->next = top;
            top = q;
            *(q->data) = n;
            *(++q->data) = '\0';
        }
    } else
        printf("Stack overflow !\n");
}

int empty(void)
{
    return (top == NULL) ? TRUE : FALSE;
}

int full(void)
{
    int state;
    Stack *t=alloc();
    (state=(t == NULL)) ? TRUE : FALSE;
    free((Stack *) t);
    return state;
}

char pop(void)
{
    Stack *new_top;
    char x;

    if (empty())
        ;
    x = *(--top->data);
    new_top = top->next;
    free((Stack *) top);
    top = new_top;
    return x;
}

int validate(void)
{
    Stack *q=alloc();
    char x;

    puts("Enter a string: ");
    fgets(q->data, 100, stdin);

    while (*(q->data)) {
        if (*(q->data) == '(' || *(q->data) == '[' || *(q->data) =='{')
            push(*(q->data));
        if (*(q->data) == ')' || *(q->data) == ']' || *(q->data) =='}') {
            if (empty())
                return FALSE;
            x = pop();
            if (x > *(q->data) || *(q->data)-x > 2)
                return FALSE;
        }
        (q->data)++;
    }
    return (empty()) ? TRUE : FALSE;
}

int main(void)
{
    (validate() == TRUE) ? puts("Parentheses are balanced") : puts("Parentheses are not balanced");
    return 0;
}
