#include <stdio.h>

int main(int argc, char *argv[]) {
    union {
        unsigned long intval;
        struct {
            unsigned char b[4];
        };
    } v = { 0xDEADBEEF };

    if(v.b[0] == 0xEF) {
        printf("+little_endian\n");
    }

    if(v.b[0] == 0xDE) {
        printf("+big_endian\n");
    }

    return 0;
}
