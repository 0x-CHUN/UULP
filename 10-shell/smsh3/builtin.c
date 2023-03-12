#include "smsh.h"
#include "varlib.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool okname(char *str) {
    assert(str != NULL);
    char *c;
    for (c = str; *c != 0; c++) {
        if ((isdigit((unsigned char)*c) && c == str) ||
            !(isalnum((unsigned char)*c) || *c == '_')) {
            return false;
        }
    }
    return (str != c);
}

int assign(char *str) {
    assert(str != NULL);

    char *equal_sign = "=";
    char *equal_sign_idx = strchr(str, '=');
    assert(equal_sign_idx != NULL);

    char *var = strtok(str, equal_sign);
    assert(var != NULL);
    if (okname(var)) {
        return VLstore(var, equal_sign_idx + 1);
    } else {
        return -1;
    }
}

bool is_built_in_command(char *cmd) {
    return (0 == strcmp(cmd, "set") || 0 == strcmp(cmd, "export") ||
            strchr(cmd, '=') != NULL);
}

int builtin_command(char **args) {
    if (strcmp(args[0], "set") == 0) {
        VLlist();
        return 0;
    }

    if (strcmp(args[0], "export") == 0) {
        if (args[1] != NULL && okname(args[1])) {
            return VLexport(args[1]);
        } else {
            return 1;
        }
    }

    if (strchr(args[0], '=') != NULL) {
        return assign(args[0]);
    }

    return 0;
}