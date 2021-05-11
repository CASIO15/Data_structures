#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Basic conversion between infix to postfix */

typedef struct Node {
    char *data;
    struct Node *next;
} Stack;

typedef struct flag {
     int open: 8;
     int close: 8;
} FLAGS;

enum {FALSE, TRUE};

Stack *top=NULL;

Stack *alloc(void );
void push(char);
int empty(void);
int full(void);
char pop(void);
int isOperand(char);
int pre(char);
int pre_in(char);
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
    return ((c >= '*' && c <= '/') || c == '^') ? TRUE : FALSE;
}

char stackTop(void)
{
    if (top)
        return *top->data;
    else
        return -1;
}
// Precedence outside the brackets
int pre(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
}

// Precedence of operators within the brackets (greater than those outside the brackets).
int pre_in(char c)
{
    if (c == '+' || c == '-')
        return 4;
    else if (c == '*' || c == '/')
        return 5;
    else if (c == '^')
        return 6;
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
    FLAGS f = {0,0};
    int i, j;
    char *postfix = (char *) malloc(sizeof(char)*strlen(s)+1);

    for (i=0, j=0; s[i] != '\0'; i++) {
        if (s[i] == '(')
            f.open = 1;
        else if (s[i] == ')')
            f.close = 1;
        else if (!isOperand(s[i]))
            postfix[j++] = s[i];
        else {
            /*If one of the bit field flags is set (i.e equal to 1)
             * enter this branch, if the close flag is set && the precedence of the operator within the brackets, is greater
             * than the one outside of it, pop it in to the string, and set the close flags to 0.
             * else push it into the stack.
             * */
            if (f.open || f.close) {
                if (f.close && (pre_in(stackTop()) >= pre(s[i]))) {
                    while (!empty())
                        postfix[j++] = pop();
                    push(s[i]);
                    f.close = f.open = 0;
                } else
                    push(s[i]);
                /*
                 * If the operator is not inside the brackets, check the precedence and act as the program that we wrote 
                 * earlier (without the precedence), however, we also need to set the flags to zero.
                 * */
            } else {
                if (pre(s[i]) >= pre(stackTop()))
                    push(s[i]);
                else {
                    while (!empty())
                        postfix[j++] = pop();
                    push(s[i]);
                }
                f.open = f.close = 0;
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
    const char string[]="((a+b)*c)-d^e^f"; // ab+c*de^-f^
    const char string2[]= "x^y/(5*z)+10"; // xy^5z*/10+
    const char string3[]= "(A*(B+(C/D)))"; // ABCD/+*

    printf("%s\n", parseToPost(string));
    printf("%s\n", parseToPost(string2));
    printf("%s\n", parseToPost(string3));
    return 0;
}
