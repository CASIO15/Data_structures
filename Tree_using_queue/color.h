#ifndef UNTITLED_COLORS_H
#define UNTITLED_COLORS_H

#include "stdio.h"

#define BHRED "\x1b[1;91m"
#define BHGRN "\x1b[1;92m"
#define BHYEL "\x1b[1;93m"
#define BHBLU "\x1b[1;94m"

#define RESET "\x1b[0m"


extern void red(char *s, int newLine);
extern void blue(char *s, int newLine);
extern void yellow(char *s, int newLine);
extern void green(char *s, int newLine);

void red(char *s, int newLine)
{
    printf(BHRED);
    printf("%s", s);
    printf(RESET);
    (newLine) ? puts("") : 0;
}

void blue(char *s, int newLine)
{
    printf(BHBLU);
    printf("%s", s);
    printf(RESET);
    (newLine) ? puts("") : 0;
}

void yellow(char *s, int newLine)
{
    printf(BHYEL);
    printf("%s", s);
    printf(RESET);
    (newLine) ? puts("") : 0;
}

void green(char *s, int newLine)
{
    printf(BHGRN);
    printf("%s", s);
    printf(RESET);
    (newLine) ? puts("\n") : 0;
}

#endif
