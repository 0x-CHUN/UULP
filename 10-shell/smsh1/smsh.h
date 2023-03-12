#ifndef smsh
#define smsh

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *next_cmd(char *, FILE *);
char *newstr(char *, int);
char **splitline(char *);
void freelist(char **);
void *emalloc(size_t);
void *erealloc(void *, size_t);
int execute(char **);
void fatal(char *, char *, int);

#endif