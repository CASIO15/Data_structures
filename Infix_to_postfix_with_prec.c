#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Basic conversion between infix to postfix including precedence */

typedef struct Node {
    char *data;
    struct Node *next;
} Stack;

enum {FALSE, TRUE};

Stack *top=NULL;

Stack *alloc(void );
void push(char);
int empty(void);
int full(void);
char pop(void);
int isOperand(char);
int pre(char);
char *parseToPost(const char *s);
char stackTop(void);

Stack *alloc(void)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->data = (char *)malloc(sizeof(char)*100);
    return p;
}

int full(void)
{
    int state;
    Stack *t=alloc();
    (state=(t == NULL)) ? TRUE : FALSE;
    free((Stack *) t);
    return state;
}

int isOperand(char c)
{
    return ((c >= '*' && c <= '/') || c == ')' || c == '^') ? TRUE : FALSE;
}

char stackTop(void)
{
    if (top)
        return *top->data;
    else
        return -1;
}

int pre(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else if (c == '(')
        return 4;
    else if (c == ')')
        return 5;
}

void push(char n)
{
    Stack *q=alloc();

    if (!full()) {
        if (top == NULL) {
            top = q;
            *(q->data) = n;
            q->data[1] = '\0';
            q->next = NULL;
        } else {
            q->next = top;
            top = q;
            *(q->data) = n;
            q->data[1] = '\0';
        }
    } else
        printf("Stack overflow !\n");
}

int empty(void)
{
    if (top == NULL)
        return TRUE;
    return FALSE;
}

char pop(void)
{
    Stack *new_top;
    char x;

    if (!empty()) {
        x = top->data[0];
        new_top = top->next;
        free((Stack *) top);
        top = new_top;
        return x;
    }
    return -1;
}

char *parseToPost(const char *s)
{
    int i, j;
    char *postfix = (char *) malloc(sizeof(char)*strlen(s)+1), x;

    for (i=0, j=0; s[i] != '\0'; i++) {
        if (!isOperand(s[i]))
            postfix[j++] = s[i];
        else {
            if (!empty() && pre(stackTop()) <= pre(s[i]))
                push(s[i]);
            else {
                while (!empty())
                    postfix[j++] = pop();
                push(s[i]);
            }
        }
    }

    while (!empty())
        postfix[j++] = pop();

    postfix[j] = '\0';
    return postfix;
}

int main(void)
{
    const char string[]="(a+b)*c-d^e^f"; // (ab)+c*def^^-
    printf("%s\n", parseToPost(string));
    return 0;
}
