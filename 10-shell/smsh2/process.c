#include "smsh.h"
#include <stdio.h>

int process(char **args) {
    int rv = 0;
    if (args[0] == NULL) {
        rv = 0;
    } else if (is_control_command(args[0])) {
        rv = do_control_command(args);
    } else if ((ok_to_execute())) {
        rv = execute(args);
    }

    return rv;
}