#include "smsh.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *next_cmd(char *prompt, FILE *fp) {
    char *buf = NULL;
    int capacity = 0;
    int len = 0;
    int c = EOF;
    printf("%s", prompt);
    fflush(stdout);

    while ((c = getc(fp)) != EOF) {
        if (len + 1 >= capacity) {
            if (capacity == 0) {
                buf = emalloc(BUFSIZ);
            } else {
                buf = erealloc(buf, capacity + BUFSIZ);
            }
            capacity += BUFSIZ;
        }
        if (c == '\n') {
            break;
        }
        buf[len] = c;
        len++;
    }

    if (c == EOF && len == 0) {
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}

char **splitline(char *line) {
    if (line == NULL) {
        return NULL;
    }
    char **args = emalloc(BUFSIZ);
    int slot_cap = BUFSIZ / sizeof(char *);
    int slot_used = 0;
    int buf_size = BUFSIZ;
    char *cp = line;
    char *delim = " ";
    char *token = strtok(cp, delim);
    while (token != NULL) {
        if (slot_used + 1 >= slot_cap) {
            args = erealloc(args, buf_size + BUFSIZ);
            buf_size += BUFSIZ;
            slot_cap += BUFSIZ / sizeof(char *);
        }
        args[slot_used] = newstr(token, strlen(token));
        slot_used++;
        token = strtok(NULL, delim);
    }
    args[slot_used] = NULL;
    return args;
}

char *newstr(char *s, int len) {
    assert(s != NULL);
    char *rv = emalloc(len + 1);
    rv[len] = '\0';
    strncpy(rv, s, len);
    return rv;
}

void freelist(char **list) {
    if (NULL == list) {
        return;
    }

    char **cp = list;
    while (*cp) {
        free(*cp);
        *cp = NULL;
        cp += 1;
    }

    free(list);
}

void *emalloc(size_t n) {
    void *rv = NULL;
    if ((rv = malloc(n)) == NULL) {
        fatal("out of memory", "", 1);
    }

    return rv;
}

void *erealloc(void *p, size_t n) {
    void *rv = NULL;
    if ((rv = realloc(p, n)) == NULL) {
        fatal("realloc() failed", "", 1);
    }

    return rv;
}