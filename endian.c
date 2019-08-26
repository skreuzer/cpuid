#include <stdio.h>

int main(int argc, char *argv[]) {
    union {
        unsigned long intval;
        struct {
            unsigned char b0;
            unsigned char b1;
            unsigned char b2;
            unsigned char b3;
        };
    } v;

    v.intval = 0xDEADBEEF;

    if(v.b0 == 0xEF) {
        printf("+little_endian\n");
    }

    if(v.b0 == 0xDE) {
        printf("+big_endian\n");
    }

    return 0;
}
