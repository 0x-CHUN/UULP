#include "smsh.h"
#include <stdio.h>
#include <string.h>

enum states {
    NEUTRAL,
    WANT_THEN,
    THEN_BLOCK,
};

enum results {
    SUCCESS,
    FAIL,
};

static int if_state = NEUTRAL;
static int if_result = SUCCESS;
static int last_stat = 0;

int syn_err(char *msg) {
    if_state = NEUTRAL;
    fprintf(stderr, "syntax error: %s\n", msg);
    return -1;
}

bool ok_to_execute() {
    bool rv;
    switch (if_state) {
    case NEUTRAL:
        rv = true;
        break;
    case WANT_THEN:
        rv = false;
        break;
    case THEN_BLOCK:
        if (if_result == SUCCESS) {
            rv = true;
        } else {
            rv = false;
        }
        break;
    default:
        rv = false;
    }

    return rv;
}

bool is_control_command(char *cmd) {
    return (strncmp(cmd, "if", 2) == 0 || strncmp(cmd, "then", 4) == 0 ||
            strncmp(cmd, "fi", 2) == 0);
}

int do_control_command(char **args) {
    char *cmd = args[0];
    int rv = -1;
    
    if (strncmp(cmd, "if", 2) == 0) {
        if (if_state != NEUTRAL) {
            rv = syn_err("if unexpected");
        } else {
            last_stat = process(args + 1);
            if_result = last_stat == 0 ? SUCCESS : FAIL;
            if_state = WANT_THEN;
            rv = 0;
        }
    } else if (strncmp(cmd, "then", 4) == 0) {
        if (if_state != WANT_THEN) {
            rv = syn_err("then unexpected");
        } else {
            if_state = THEN_BLOCK;
            rv = 0;
        }
    } else if (strncmp(cmd, "fi", 2) == 0) {
        if (if_state != THEN_BLOCK) {
            rv = syn_err("fi unexpected");
        } else {
            if_state = NEUTRAL;
            rv = 0;
        }
    } else {
        fatal("internal error message", cmd, 2);
    }

    return rv;
}