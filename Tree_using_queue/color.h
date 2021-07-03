#ifndef UNTITLED4_COLOR_H
#define UNTITLED4_COLOR_H

#include "stdio.h"

#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define RESET "\e[0m"



extern void red(char *s, int newLine);
extern void blue(char *s, int newLine);
extern void yellow(char *s, int newLine);
extern void green(char *s, int newLine);

void red(char *s, int newLine)
{
    printf(BHRED);
    printf("%s", s);
    printf(RESET);
    (newLine) ? printf("\n") : 0;
}

void blue(char *s, int newLine)
{
    printf(BHBLU);
    printf("%s", s);
    printf(RESET);
    (newLine) ? printf("\n") : 0;
}

void yellow(char *s, int newLine)
{
    printf(BHYEL);
    printf("%s", s);
    printf(RESET);
    (newLine) ? printf("\n") : 0;
}

void green(char *s, int newLine)
{
    printf(BHGRN);
    printf("%s", s);
    printf(RESET);
    (newLine) ? printf("\n") : 0;
}


#endif
