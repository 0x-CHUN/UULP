#include <ctype.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int c;
    while ((c = getchar() ) != EOF) {
        if (c == 'z') {
            c = 'a';
        } else if (islower(c)) {
            c++;
        }
        putchar(c);
    }

    return 0;
}
