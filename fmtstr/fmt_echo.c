#include <stdio.h>
#include <stdlib.h>

int main() {
    char buf[0x100];
    while (1) {
        fgets(buf, 0x100 - 1, stdin);
        printf(buf);
    }
}

// enable fortify_source
// gcc -o fmt_echo ./fmt_echo.c -O2 -D_FORTIFY_SOURCE=2